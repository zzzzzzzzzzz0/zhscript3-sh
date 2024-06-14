#include "slave.h"
#include <unistd.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <fcntl.h>

namespace pub {

static gboolean cb__(gpointer data) {
	GIOChannel *ioc = (GIOChannel *)data;
	slave___* thiz = (slave___*)ioc->reserved2;
	for(;;) {
		gchar *s = NULL;
		gsize l = 0;
		if(thiz->is_stop__())
			return FALSE;
		g_io_channel_read_line(ioc, &s, &l, NULL, NULL);
		if(!s)
			return TRUE;
		while(l > 0) {
			gchar c = s[--l];
			if(c == '\r' || c == '\n') {
				s[l] = '\0';
			} else
				break;
		}
		thiz->z__(s);
		g_free(s);
	}
}

int slave___::init__(const std::vector<std::string>& args, size_t from, const std::vector<std::string>& envs, GMainContext *mc) {
	if(socketpair(AF_UNIX, SOCK_STREAM, 0, sv_) == -1)
		return 1;
	ioc_ = g_io_channel_unix_new(sv_[0]);
	ios_ = g_io_create_watch(ioc_, G_IO_IN);
	ioc_->reserved2 = this;
	g_source_set_callback(ios_, cb__, ioc_, NULL);
	g_source_attach(ios_, mc);

	pid_t pid = fork();
	if (pid == -1)
		return 2;
	if (pid == 0) {
		struct sigaction act;
		memset(&act, 0, sizeof(act));
		sigfillset(&act.sa_mask);
		act.sa_handler = SIG_IGN;
		sigaction(SIGHUP, &act, NULL);
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
		sigaction(SIGPIPE, &act, NULL);
		sigaction(SIGTERM, &act, NULL);
		sigaction(SIGBUS, &act, NULL);
		sigaction(SIGFPE, &act, NULL);
		sigaction(SIGILL, &act, NULL);
		sigaction(SIGSEGV, &act, NULL);
		sigaction(SIGSYS, &act, NULL);
		sigaction(SIGXCPU, &act, NULL);
		sigaction(SIGXFSZ, &act, NULL);
		sigaction(SIGHUP, &act, NULL);

		sigset_t set;
		if(sigfillset(&set) == -1)
			return 3;
		if(sigprocmask(SIG_SETMASK, &set, NULL) == -1)
			return 4;
		sigemptyset(&set);
		sigprocmask(SIG_SETMASK, &set, NULL);

		close(sv_[0]);
		if(dup2(sv_[1], STDIN_FILENO) == -1)
			return 5;
		if(dup2(sv_[1], STDOUT_FILENO) == -1)
			return 6;
		if(dup2(sv_[1], STDERR_FILENO) == -1)
			return 7;
		close(sv_[1]);
		if(setpgid(0, 0) == -1)
			return 9;

		const char* argv[1024];
		size_t i = 0, max = args.size() - from;
		for(; i < max;)
			argv[i++] = args[from + i].c_str();
		argv[i++] = NULL;
		if(!envs.empty()) {
			const char* envv[32];
			for(size_t i = 0; i < envs.size();)
				envv[i++] = envs[i].c_str();
			envv[i++] = NULL;
			if(execvpe(argv[0], (char* const*)argv, (char* const*)envv) == -1)
				return 10;
		} else {
			if(execvp(argv[0], (char* const*)argv) == -1)
				return 10;
		}
	}
	pid_ = pid;
	stop_ = false;

	close(sv_[1]);
	sv_[1] = -1;
	fd_set set;
	FD_ZERO(&set);
	FD_SET(sv_[0], &set);
	if(select(sv_[0] + 1, NULL, &set, NULL, NULL) == -1)
		return 11;
	fcntl(sv_[0], F_SETFL, fcntl(sv_[0], F_GETFL, 0) | O_NONBLOCK);

	return 0;
}

void slave___::stop__() {
	if(is_stop__())
		return;
	stop_ = true;
	if(ioc_) {
		g_source_unref(ios_);
		g_io_channel_shutdown(ioc_, TRUE, NULL);
		g_io_channel_unref(ioc_);
	}
	for(;;) {
		kill(-pid_, SIGKILL);
		if(waitpid(-pid_, NULL, WNOHANG) == -1)
			break;
	}
	pid_ = -1;	
}

void slave___::send__(const std::string& s) {
	if(is_stop__())
		return;
	if(write(sv_[0], s.c_str(), s.size()) == -1)
		return;
}

static gpointer cb2__(gpointer data) {
	GMainContext *mc = (GMainContext *)data;

	g_main_context_push_thread_default (mc);

	GMainLoop *ml = g_main_loop_new (mc, FALSE);
	g_main_loop_run (ml);
	g_main_loop_unref (ml);

	g_main_context_pop_thread_default (mc);
	g_main_context_unref (mc);

	return NULL;
}

GMainContext *thread__(const char *name) {
	GMainContext *mc = g_main_context_new ();
	g_thread_new (name, cb2__, g_main_context_ref (mc));
	return mc;
}

}
