#include <vte/vte.h>
#include "../../../pub.h"
static plugin::pub___* pub_ = nullptr;

class view___ : public plugin::view___ {
	private:
	GPid pid_ = 0;
	std::string ps1_, wd_;

	static void cb_spawn__(VteTerminal *terminal, GPid pid, GError *error, gpointer user_data) {
		view___* thiz = (view___*)user_data;
		thiz->pid_ = pid;
		if(thiz->nok__())
			return;
		if(thiz->need_focus_) thiz->focus__();
		if(!thiz->ps1_.empty()) {
			//setenv("PS1", "z", true);
			thiz->ins__(" PS1='" + thiz->ps1_ + "';reset\n");
			thiz->ps1_.clear();
		}
		if(!thiz->ins_.empty()) {
			thiz->ins__(thiz->ins_);
			thiz->ins_.clear();
		}
		vec___ p {"页初始", std::to_string(pid)};
		pub_->fanqiechaodan3__(thiz, p);
	}
	static void window_title_changed__(VteTerminal* vte, view___* thiz) {
		std::string s = vte_terminal_get_window_title(vte), tag = ": ";
		size_t i = s.find(tag);
		if(i != std::string::npos)
			s = s.substr(i + tag.length());
		vec___ p {"标题", s};
		pub_->fanqiechaodan3_ic__(thiz, p);
	}

	bool exited_ = false;
	gulong child_exited_ = 0;
	static void child_exited__(VteTerminal* vte, int code, view___* thiz) {
		if(thiz->nok__())
			return;
		vec___ p {"内退",
			std::to_string(code),
			std::to_string(code / 256),
			std::to_string(code % 256)};
		pub_->fanqiechaodan3__(thiz, p);
	}

	bool contents_changed_ = false;
	std::string contents_changed_1_, contents_changed_2_, text_old_;
	glong col_old_ = 0, row_old_ = 0;
	static void contents_changed__(VteTerminal *vte, view___* thiz) {
		if(!thiz->contents_changed_1_.empty()) {
			vec___ p;
			pub_->fanqiechaodan2__(thiz, thiz->contents_changed_1_, p);
		}
		if(!thiz->contents_changed_2_.empty()) {
			glong col, row;
			vte_terminal_get_cursor_position(thiz->hr2__(), &col, &row);
			gchar *vte_text = vte_terminal_get_text_range(thiz->hr2__(),
					thiz->row_old_,
					thiz->col_old_,
					row,
					col,
					NULL,
					NULL,
					NULL);
			thiz->row_old_ = row;
			thiz->col_old_ = col;
			thiz->text_old_ += vte_text;
			g_free (vte_text);

			vec___ p {thiz->text_old_};
			thiz->text_old_.clear();
			pub_->fanqiechaodan2__(thiz, thiz->contents_changed_2_, p);

		}
	}

	bool ok1__() {return pid_ > 0;}
	bool nok__() {
		return !ok1__() || exited_ || pub_->is_quit__();
	}

	std::string ins_;
	void ins__(const std::string &cmd1) {
		vte_terminal_feed_child(hr2__(), cmd1.c_str(), cmd1.length());
	}

	std::string arg2_, arg1_;
	int for1__(vec___& args, size_t& from) {
		pub_->eval__(arg2_.c_str(), &args);
		return pub_->clpars__({
			{"-目录", "w", 1}, 
		}, args, from, [&](const std::string& tag, size_t i, size_t argc, int& ret2) {
			switch(tag[0]) {
			case 'w': wd_ = args[i]; break;
			}
		});
	}
	int for2__(args___ args, size_t& from, int fn2_ret2) {
		return pub_->clpars__({
			{"-行数", "l", 1},
			{"-背景色", "Cb", 1},
			{"-前景色", "Cf", 1},
		}, args, from, [&](const std::string& tag, size_t i, size_t argc, int& ret2) {
			switch(tag[0]) {
				case 'l':
				vte_terminal_set_scrollback_lines(hr2__(), std::stoi(args[i]));
				break;
				case 'C': {
				GdkRGBA bc;
				const std::string& s = args[i];
				if(!gdk_rgba_parse (&bc, s.c_str()))
					throw s + " 格式错误";
				switch(tag[1]) {
					case 'f': vte_terminal_set_color_foreground(hr2__(), &bc); break;
					default:  vte_terminal_set_color_background(hr2__(), &bc); break;
				}
				break; }
			}
		}, [&]() {return fn2_ret2;});
	}

	public:
	const char* path__() {
		if(ok1__()) {
			pub_->read_symlink("/proc/" + std::to_string(pid_) + "/cwd", wd_);
		}
		return wd_.c_str();
	}
	int for__(args___ args, size_t& from, rust_add___ add, void* env) {
		bool dunhao = false;
		int ret2 = pub_->clpars__({
			{"-工作目录", "w", 0},
			{"-得选择", "X", 0},
			{"-插入", "i", 1},
			{"-文字", "f", 1},
			{"-复制", "c", 0},
			{"-粘贴", "v", 0},
			{"-清除", "R", 0},
			{"-搜", "S", 2},
			{"-内容变", "$c", 1},
			{"-内容变2", "$c2", 1},
			{"-刷新", "r", 0},
		}, args, from, [&](const std::string& tag, size_t i, size_t argc, int& ret2) {
			switch(tag[0]) {
			case 'w': pub_->add__(path__(), dunhao, add, env); break;
			case 'X':
				if(vte_terminal_get_has_selection(hr2__())) {
					/*char* s = vte_terminal_get_text(hr2__(), select__, nullptr, nullptr);
					if(s) {
						add2(s);
						free(s);
					}*/
					pub_->get_sel__([&] {
						vte_terminal_copy_clipboard(hr2__());
					}, dunhao, add, env);
				}
				break;
			case 'i':
				if(!nok__())
					ins__(args[i]);
				else
					ins_ += args[i];
				break;
			case 'f': {
				const std::string& s = args[i];
				vte_terminal_feed(hr2__(), s.c_str(), s.length());
				break; }
			case 'c':
				if(vte_terminal_get_has_selection(hr2__())) {
					vte_terminal_copy_clipboard(hr2__());
					if(add)
						pub_->add__("1", dunhao, add, env);
				}
				break;
			case 'v': vte_terminal_paste_clipboard(hr2__()); break;
			case 'R': vte_terminal_reset(hr2__(), true, true); break;
			case 'S': {
				const std::string &s = args[i];
				if(s.empty()) {
					//vte_terminal_search_set_gregex(hr2__(), NULL, G_REGEX_MATCH_ANCHORED);
					if(add)
						pub_->add__("2", dunhao, add, env);
					break;
				}
				bool next = true;
				pub_->clpars2_sou__(args[i + 1], [&](const std::string& tag) {
					switch(tag[0]) {
						case 'f':
						next = false;
						break;
						case 'i':
						break;
					}
				});

				/*GRegex* r = vte_terminal_search_get_gregex(hr2__());
				if (!r || strcmp(s.c_str(), g_regex_get_pattern(r)) != 0) {
					GError* err = NULL;
					GRegex* r2 = g_regex_new(s.c_str(), G_REGEX_CASELESS, G_REGEX_MATCH_ANCHORED, &err);
					if (err) {
						pub_->pr__(nullptr, err->message);
						g_clear_error(&err);
						break;
					}
					vte_terminal_search_set_gregex(hr2__(), r2, G_REGEX_MATCH_ANCHORED);
				}
				vte_terminal_search_find_next(hr2__());*/

				GError* err = NULL;
				VteRegex* r2 = vte_regex_new_for_search(s.c_str(), -1, VTE_REGEX_FLAGS_DEFAULT, &err);
				if (err) {
					pub_->pr__(nullptr, err->message);
					g_clear_error(&err);
					break;
				}
				vte_terminal_search_set_regex(hr2__(), r2, 0);
				bool b;
				if(next) {
					b = vte_terminal_search_find_next(hr2__());
				} else {
					b = vte_terminal_search_find_previous(hr2__());
				}
				if(add)
					pub_->add__(b ? "1" : "0", dunhao, add, env);
				break; }
			case '$':
				switch(tag[1]) {
					case 'c':
					switch(tag[2]) {
						case '2': contents_changed_2_ = args[i]; break;
						default:  contents_changed_1_ = args[i]; break;
					}
					if(!contents_changed_) {
						contents_changed_ = true;
						g_signal_connect(hr_, "contents_changed", G_CALLBACK(contents_changed__), this);
					}
					break;
				}
				break;
			case 'r': open__(arg1_, arg2_); break;
			}
		});
		if(ret2 != 0) return ret2;
		return for2__(args, from, pub::clpars_ret_no_);
	}
	static gboolean select__(VteTerminal *terminal, glong column, glong row, gpointer data) {
#ifdef _debug_
		printf("%ld %ld %p\n",column, row, data);
#endif
		return TRUE;
	}

	view___(const std::string& arg2) {
		hr_ = vte_terminal_new();
		arg2_ = arg2;
		vec___ args;
		size_t from = 0;
		for1__(args, from);
	}
	void open__(const std::string& arg1, const std::string& arg2);
	VteTerminal* hr2__() {return VTE_TERMINAL(hr_);}
 	int scroll__() {return 1;}
	bool focus2__() {return true;}
	void on_close__();
	//bool can_close__() {return ok1__();}
	bool yuxiangrousi__() {return true;}
	const char* plugin_id__();
};

class plugin___ : public plugin::base___ {
	private:
	GtkWidget* menu_ = nullptr;
	std::string menu_item_;
	static void menu_item_acti__(GtkWidget *item, plugin___* thiz) {
		thiz->menu_item_ = gtk_menu_item_get_label(GTK_MENU_ITEM(item));
		g_idle_add(idle_menu_item__, thiz);
	}
	static gint menu_popup__ (GtkWidget *widget, GdkEvent *event) {
		if (event->type == GDK_BUTTON_PRESS) {
			GdkEventButton *eb = (GdkEventButton *) event;
			if (eb->button == GDK_BUTTON_SECONDARY) {
				gtk_menu_popup (GTK_MENU (widget), NULL, NULL, NULL, NULL, eb->button, eb->time);
				return TRUE;
			}
		}
		return FALSE;
	}
	static gboolean idle_menu_item__(gpointer p) {
		plugin___* thiz = (plugin___*)p;
		for(auto& v : thiz->views_) {
			if(pub_->is_focus__(v)) {
				size_t from = 0;
				vec___ args;
				args.push_back(thiz->menu_item_);
				v->for__(args, from, nullptr, nullptr);
				break;
			}
		}
		return G_SOURCE_REMOVE;
	}

	public:
	plugin::view___* new__(const std::string& arg1, const std::string& arg2);
	const char* id__() {return "终端";}

	int for__(args___ args, size_t& from, rust_add___ add, void* env) {
		return 0;
	}

	std::vector<view___*> views_;
	void menu__(view___* v) {
		if(!menu_) {
			menu_ = gtk_menu_new();
			GtkMenuShell* menu = GTK_MENU_SHELL(menu_);
			//gtk_style_context_add_class (gtk_widget_get_style_context (menu_), GTK_STYLE_CLASS_CONTEXT_MENU);
			auto add = [&](auto label) {
				GtkWidget *item = gtk_menu_item_new_with_label(label);
				g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK (menu_item_acti__), this);
				gtk_menu_shell_append(menu, item);
			};
			add("-复制");
			add("-粘贴");
			gtk_menu_shell_append(menu, gtk_separator_menu_item_new());
			add("-清除");
			gtk_widget_show_all(menu_);
		}
		g_signal_connect_swapped (v->hr__(), "button_press_event", G_CALLBACK (menu_popup__), menu_);
		views_.push_back(v);
	}
};
static plugin___ pub2_;

void view___::open__(const std::string& arg1, const std::string& arg2) {
	arg1_ = arg1;
	arg2_ = arg2;

	vec___ args;
	size_t from = 0;

	std::string cmd = arg1, env;
	bool title = true;
	if(for1__(args, from) == 0) {
		if(pub_->clpars__({
			{"-不标", "t", 0}, 
			{"-环境", "e", 1},
			{"-指示符", "p", 1},
		}, args, from, [&](const std::string& tag, size_t i, size_t argc, int& ret2) {
			switch(tag[0]) {
			case 't': title = false; break;
			case 'e':
				if(!env.empty())
					env += "\n";
				env += args[i];
				break;
			case 'p': ps1_ = args[i]; break;
			}
		}) == 0) {
			for2__(args, from, pub::clpars_throw_);
		}
	}

	if(!wd_.empty() && !pub_->exist_d__(wd_)) {
		return;
	}
	if(cmd.empty())
		cmd = "bash";
	switch(cmd[0]) {
		case '/': case '.':
			break;
		default: {
			do {
				size_t i = cmd.find(' ');
				std::string cmd1 = "/bin/" + (i == std::string::npos ? cmd : cmd.substr(0, i));
				auto exist = [&]() {
					if(pub_->exist_f__(cmd1)) {
						cmd = cmd1;
						return true;
					}
					return false;
				};
				if(exist()) break;
				cmd1 = "/usr" + cmd1;
				if(exist()) break;
			} while(false);
		break; }
	}
	if(title)
		g_signal_connect(hr_, "window-title-changed", G_CALLBACK(window_title_changed__), this);
	child_exited_ = g_signal_connect(hr_, "child-exited", G_CALLBACK(child_exited__), this);

	GError *error = NULL;
	char **argv = NULL, **envv = NULL;
	int argc = 0;
	g_shell_parse_argv(cmd.c_str(), &argc, &argv, &error);
	if(!error) {
		if(!env.empty())
			g_shell_parse_argv(env.c_str(), NULL, &envv, &error);
		if(!error) {
			//g_spawn_async
			vte_terminal_spawn_async(hr2__(),
				VTE_PTY_DEFAULT,
				!wd_.empty() ? wd_.c_str() : NULL,
				argv,
				envv,
				(GSpawnFlags)0,
				NULL, NULL, NULL,
				-1,
				NULL,
				cb_spawn__, this);
		}
	}
	g_strfreev(envv);
	g_strfreev(argv);
	if(error) {
		pub_->pr__(&args, error->message);
		g_error_free (error);
		return;
	}
	pub2_.menu__(this);
}
void view___::on_close__() {
	exited_ = true;
	std::vector<view___*> & vs = pub2_.views_;
	if(vs.size() > 0)
		vs.erase(std::find(vs.begin(), vs.end(), this));
}
const char* view___::plugin_id__() {return pub2_.id__();}

plugin::view___* plugin___::new__(const std::string& arg1, const std::string& arg2) {
	view___* v = new view___(arg2);
	v->open__(arg1, arg2);
	return v;
}

extern "C" {

void pub__(plugin::pub___* pub) {pub_ = pub;}
plugin::base___* pub2__() {return &pub2_;}

}
