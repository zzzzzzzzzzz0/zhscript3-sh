#include "fanqiechaodan.h"
#include <gdk/gdkx.h>

template<typename T>
T try__(std::function<T()> f1, T f2, std::function<void(const std::string&)> f3) {
	try {return f1();} 
	catch(std::exception& e) {
		f3(e.what());
	}
	catch(const char* s) {
		f3(s);
	}
	catch(const std::string& s) {
		f3(s);
	}
	return f2;
}

class plugin___ : public dl___ {
	private:
	using pub___ = void (*)(plugin::pub___*);
	using pub2___ = plugin::base___* (*)();

	public:
	plugin::base___* hr_ = nullptr;

	int init__(plugin::pub___* pub) {
		plugin___::pub___ pp = (plugin___::pub___)sym__("pub__");
		if(err__()) return 254;
		pp(pub);
		plugin___::pub2___ pp2 = (plugin___::pub2___)sym__("pub2__");
		if(err__()) return 254;
		hr_ = pp2();
		return 0;
	}

	bool err__() {
		if(dl___::err__()) {
			perr__();
			return true;
		}
		return false;
	}
	void perr__() {
		std::cerr << err_ << '\n';
	}
};

class main___ : public main_plugin___ {
	private:
	code___ code_;

	public:
	void pr__(rets2___ v, const std::string& s = "", const std::string& s2 = "", size_t end = SIZE_MAX) {
		if(!code_.coderr_.empty()) {
			std::string coderr = code_.coderr_;
			code_.coderr_.clear();
			vec___ v2;
			if(!s.empty())
				v2.push_back(s);
			if(v)
				v2.insert(v2.end(), v->begin(), v->end());
			if(!s2.empty())
				v2.push_back(s2);
			fanqiechaodan2__((view___*)nullptr, coderr, v2);
			code_.coderr_ = coderr;
			return;
		}
		if(!s.empty()) {
			std::cerr << s;
			if(!ends__(s, "\n")) std::cerr << std::endl;
		}
		//for(size_t idx = 0; auto &i : v) //g++-11
		size_t idx = 0;
		if(v)
		for(auto &i : *v)
		{
			if(idx > end) break;
			std::string s2;
			for(unsigned char c : i) {
				if(c < ' ') {
					switch (c) {
					case '\n':
					case '\r':
					case '\t':
						break;
					default:
						s2 += '\\';
						s2 += std::to_string(c);
						continue;
					}
				}
				s2 += c;
			}
			std::cerr << idx++ << ") " << s2 << std::endl;
		}
		if(!s2.empty())
			std::cerr << s2 << std::endl;
	}

	int clpars1__(pub::tags___& tags, args___ v, size_t& from, pub::clpars_fn___ fn, pub::clpars_fn2___ fn2) {
		if(v.empty())
			return 1;

		return try__<int>([&]() {
			return pub::clpars__(tags, v, from, fn, [&]() -> int {
				const std::string& s = v[from];
				if(s.empty() || starts_with(s, "-zhscript-"))
					return pub::clpars_skip_;
				if(s == "-help") throw "";
				return fn2();
			}) > 0 ? 1 : 0;
		}, -1, [&](const std::string& s) {
			clpars_pr__(tags, v, s);
		});
	}
	void clpars_pr__(pub::tags___& tags, args___ v, const std::string& s) {
		std::string s2;
		s2 += "\n支持选项以下：\n";
		for(pub::tag___& i : tags.a_) {
			s2 += i.flag_;
			if(i.argc_)
				s2 += " (" + std::to_string(i.argc_) + ")";
			if(i.rem_) {
				s2 += ' ';
				s2 += i.rem_;
			}
			s2 += '\n';
		}
		s2 += "以上";
		pr__(&v, s, s2);
	}

	void clpars2_sou__(const std::string& s, fn__s___ fn) {
		std::string a[][2] = {{"-反向", "f"}, {"-大小写", "i"}};
		std::string opt = s;
		for(auto& i : a) {
			auto i2 = opt.find(i[0]);
			if(i2 != std::string::npos) {
				opt.replace(i2, i[0].length(), "");
				fn(i[1]);
			}
		}
		if(!opt.empty()) {
			opt += " 不支持，仅支持 ";
			for(auto& i : a) {
				opt += i[0];
			}
			throw opt;
		}
	}

	int eval__(const char* s, rets___ ret = nullptr, argc___ argc = 0, argv___ argv = nullptr, void* env = nullptr) {
		int ret3 = l4___::eval_ok_;
		vec___ ret2;
		if(!l4_.eval__(s, false, argc, argv, 0, env, &ret2)) {
			switch(l4_.erret_.is_quit_) {
				case l4___::eval_quit_:
				if(!l4_.erret_.s_.empty())
					ret2.push_back(l4_.erret_.s_);
				pr__(&ret2);
				quit__();
				case l4___::eval_continue_: case l4___::eval_break_:
				ret3 = l4_.erret_.is_quit_;
				break;
			}
			if(ret3 == l4___::eval_ok_) {
				ret2.push_back(l4_.erret_.s_);
				ret2.push_back(l4_.erret_.s2_);
				pr__(&ret2);
				return 0;
			}
		}
		if(ret) {
			ret->insert(ret->end(), ret2.begin(), ret2.end());
		}
		return ret3;
	}
	int eval__(const char* s, args___ p, rets___ ret = nullptr, void* env = nullptr) {
		std::vector<const char*> p2;
		for (std::string const& i : p)
			p2.push_back(i.data());
		return eval__(s, ret, p2.size(), p2.data(), env);
	}

	int fanqiechaodan__(plugin::view___* view, const std::string& s, rets___ ret = nullptr, argc___ argc = 0, argv___ argv = nullptr, void* env = nullptr) {
		return fanqiechaodan__(view ? (view___*)view->p_ : nullptr, s, ret, argc, argv, env);
	}
	int fanqiechaodan__(view___* view, const std::string& s, rets___ ret = nullptr, argc___ argc = 0, argv___ argv = nullptr, void* env = nullptr) {
		return try__<int>([&]() {
			return fanqiechaodan1__(view, (jiekou__(view) + s).c_str(), ret, nullptr, env, argc, argv, nullptr);
		}, 0, [&](const std::string& s) {
			pr__(nullptr, s);
		});
	}
	std::string jiekou__(view___* view, const char* name = "") {
		return "函数“壳”、“口”、“接口”" + std::string(name) + "以“*" + std::to_string((unsigned long)fanqiechaodan9__) + "”、“-u:" + std::to_string((unsigned long)view) + "-c*-$:A-Z”。";
	}
	int fanqiechaodan2__(plugin::view___* view, const std::string& s, args___ p, rets___ ret = nullptr, void* env = nullptr) {
		return fanqiechaodan2__(view ? (view___*)view->p_ : nullptr, s, p, ret, env);
	}
	int fanqiechaodan2__(view___* view, const std::string& s, args___ p, rets___ ret = nullptr, void* env = nullptr) {
		std::vector<const char*> p2;
		for (std::string const& i : p)
			p2.push_back(i.data());
		return fanqiechaodan__(view, s, ret, p2.size(), p2.data(), env);
	}
	int fanqiechaodan3__(plugin::view___* view, vec___& a, rets___ ret = nullptr, void* env = nullptr) {
		return fanqiechaodan3__(view ? (view___*)view->p_ : nullptr, a, ret, env);
	}
	int fanqiechaodan3__(view___* v, vec___& a, rets___ ret = nullptr, void* env = nullptr) {
		if(v) std__(v, a);
		return fanqiechaodan2__(v, code_.code_, a, ret, env);
	}
	int fanqiechaodan3_ic__(plugin::view___* v, vec___& a, rets___ ret = nullptr, void* env = nullptr) {
		a.push_back(((view___*)v->p_)->is_curr__() ? "1" : "");
		return fanqiechaodan3__(v, a, ret, env);
	}
	void std__(view___* v, vec___& a) {
		a.push_back(v->name__());
		a.push_back(std::to_string(v->id_));
		a.push_back(v->plugin_id__());
	}

	GtkWidget *pack__(plugin::view___* view, plugin::view___* by, int posi) {return window___::pack__(view, by, posi);}
	int main_eval__(args___ p, rets___ ret = nullptr, void* env = nullptr) {return eval__(code_.code_.c_str(), p, ret, env);}
	bool is_focus__(plugin::view___* v) {
		if(gtk_widget_is_focus(v->hr__())) {
			window___* w = (window___*)((view___*)v->p_)->window_;
			//gtk_window_has_toplevel_focus
			if(w->is_act__())
				return true;
		}
		return false;
	}
	void not_block__() {
		while (gtk_events_pending ())
			gtk_main_iteration ();
	}
	bool is_quit__() {return is_quit_;}
	void quit__() {
		if(is_quit_)
			return;
		is_quit_ = true;
		for(auto& w : windows_)
			w->on_destroy__();
		g_application_quit(app__());
	}

	private:
	GtkApplication *app_ = nullptr;
	GApplication *app__() {return G_APPLICATION (app_);}
	std::vector<plugin___*> plugins_;
	bool is_quit_ = false;

	static void fanqiechaodan9__(view___* v, const char* s, rust_add___ add, void* env, argc___ argc, ...) {
		const char** args = new const char* [argc];
		{
			va_list argv;
			va_start(argv, argc);
			for (size_t i = 0; i < argc; i++) {
				args[i] = va_arg(argv, const char*);
			}
			va_end(argv);
		}
		fanqiechaodan1__(v, s, nullptr, add, env, argc, args, nullptr);
		delete args;
	}

	static void destroyWindowCb(GtkWidget* widget, main___* thiz) {
		window___* window = (window___*)window___::this__(widget);
		if(window->on_destroy__()) return;
		thiz->windows_.erase(std::find(thiz->windows_.begin(), thiz->windows_.end(), window));
		delete window;
	}

	static gboolean idle_close__(gpointer p) {
		view___* v = (view___*)p;
		window___::close__(v, true);
		return G_SOURCE_REMOVE;
	}

	public:
	vec___ ret_;
	size_t ret_from_;
	~main___() {
		if(app_)
			g_object_unref (app_);
	}

	GtkWidget *window_new__() {return gtk_application_window_new (app_);}
	window___* find__(const std::string& name) {
		if(!name.empty()) {
			auto ret = std::find_if(windows_.begin(), windows_.end(), [&](auto i) {
				return i->name__() == name;
			});
			if(ret != windows_.end()) return *ret;
		}
		return nullptr;
	}

	void init__() {
		fanqiechaodan1__(nullptr, nullptr, nullptr, nullptr, nullptr, 0, nullptr, this);
		{
			std::string s = R"(
解释下代码
	模块“外壳”。
	赋予“外壳名”、“外壳版本”以“乙壳”、“4.7.10”。
	)" + jiekou__(nullptr, "、“番茄炒蛋”") + R"(
上代码)";
			l4_.eval__(s.c_str());
		}
	}
	void init__(const std::string& appid) {
		app_ = gtk_application_new (appid.empty() ? nullptr : appid.c_str(), G_APPLICATION_HANDLES_COMMAND_LINE);
		g_signal_connect (app_, "command-line", G_CALLBACK (activate__), this);
	}
	int run__(int argc2, char **argv2) {
		{
			fs::path path = l4_.path_;
			path.replace_filename("plugin/gtkBsh");
			fs::directory_entry d {path};
			if(exists__(d))
			for(auto& i: fs::directory_iterator(path)) {
				plugin___* p = new plugin___();
				if(p->open__(i.path())) {
					int err = p->init__(this);
					if(err)
						return err;
				} else {
					p->perr__();
					return 254;
				}
				plugins_.push_back(p); 
			}
		}
		return g_application_run (app__(), argc2, argv2);
	}
	bool starts_with(const std::string& s, const std::string& s2) {return starts__(s, s2);}
	bool ends_with(const std::string& s, const std::string& s2) {return ends__(s, s2);}
	void op__(const std::string &s2, char c, std::string& s) {return code___::op__(s2, c, s);}
	void read_symlink(const std::string& path, std::string& ret) {
		fs::path path2 = fs::read_symlink(path);
		ret = path2.string();
	}
	void replace_filename(const std::string& path, const char* name, std::string& ret) {
		fs::path p = path;
		p.replace_filename(name);
		ret = p;
	}
	bool exist_d__(const std::string& path) {
		return exists__(fs::directory_entry(path));
	}
	bool exist_f__(const std::string& path) {return fs::exists(path);}
	void perms__(const std::string& filename, fn_b___ f1) {
		fs::perms p = fs::status(filename).permissions();
		if (f1()) {
			if((p & fs::perms::owner_exec) != fs::perms::none)
				fs::permissions(filename, p);
		}
	}
	void name__(GtkNotebook *nb1, std::string& ret) {
		const char* name1 = gtk_widget_get_name(GTK_WIDGET(nb1));
		if(name1) {
			ret = name1;
			if(ret == "GtkNotebook") {} else return;
		}
		ret.clear();
	}

	private:
	unsigned act_ = 0;
	void act__() {
		vec___ ret;
		if(act_ < 9999)
			++act_;
		if(act_ > 1) {
			vec___ args = {"壳激活", std::to_string(act_)};
			args.insert(args.end(),
				std::make_move_iterator(ret_.begin()),
				std::make_move_iterator(ret_.end()));
			ret_.clear();
			main_eval__(args, &ret);
			if(!window___::bool__(ret))
				windows_[0]->act__();
			return;
		}
		ret_from_ = 0;
		for__(ret_, ret_from_);
		main_eval__({"壳初始"}, &ret);
		ret_.insert(ret_.begin() + ret_from_, ret.begin(), ret.end());
		if(!ret_.empty()) {
			add__(ret_, ret_from_, "");
			ret_.clear();
		}
	}
	static void activate__(GtkApplication* app, GApplicationCommandLine *cmdline, main___* m) {
		if(m->act_) {
			gint argc;
			gchar **argv = g_application_command_line_get_arguments (cmdline, &argc);
			for (int i = 1; i < argc; i++)
				m->ret_.push_back(argv[i]);
			g_strfreev (argv);
		}
		m->act__();
	}

	void add__(args___ p, size_t& from, const std::string& wname) {
		window___* window = find__(wname);
		if(window) {
			if(gtk_window_get_accept_focus(window->hr2__()))
				window->act__();
			for__(window, nullptr, nullptr, p, from, 1, true, false, false, nullptr, nullptr);
		} else {
			window = new window___(this, &code_);
			windows_.push_back(window);
			window->this__();
			if(!wname.empty())
				window->name__(wname.c_str());
			g_signal_connect(window->hr__(), "destroy", G_CALLBACK(destroyWindowCb), this);
			for__(window, nullptr, nullptr, p, from, 1, false, true, false, nullptr, nullptr);
			window->show__();

			main_eval__({"窗初始", window->name__(), std::to_string(GDK_WINDOW_XID(window->hr3__()))});
		}
	}
	int for__(args___ p, size_t& from) {
		return clpars__({
			{"-回调", "c", 1},
			{"-错回调", "ce", 1},
			{"-开回调", "cn", 1},
			{"-关回调", "cd", 1},
			{"-回调+" , "c", 1},
			{"-错回调+", "ce", 1},
			{"-开回调+", "cn", 1},
			{"-关回调+", "cd", 1},
			{"-回调-" , "c", 1},
			{"-错回调-", "ce", 1},
			{"-开回调-", "cn", 1},
			{"-关回调-", "cd", 1},
		}, p, from, [&](const std::string& tag, size_t i, size_t argc, int& fn2_ret2) {
			switch(tag[0]) {
			case 'c': {
				auto op = [&](size_t i3, std::string& s) {
					code___::op__(p[i], p[i - 1], i3 + 10, tag, s);
				};
				switch(tag[1]) {
					case 'e': op(0, code_.coderr_  ); break;
					case 'n': op(0, code_.code_new_); break;
					case 'd': op(0, code_.code_del_); break;
					default: op(-3, code_.code_    ); break;
				}
				break; }
			}
		});
	}
	int for__(args___ p, size_t& from, rust_add___ add, void* env) {
		for(auto& i : plugins_) {
			int ret2 = i->hr_->for__(p, from, add, env);
			if(ret2 != 0)
				return ret2;
		}
		return 0;
	}
	int for__(window___* window, GtkWidget *nb1, view___* view, args___ p, size_t& from, int fn2_ret,
			bool no_newindow, bool nb1_need_new, bool is1, rust_add___ add, void* env) {
		std::string wname;
		int ret2;
		ret2 = for__(p, from);
		if(ret2 != 0) return ret2;
		ret2 = clpars__({
			{"-名", "n", 1},
			{"-新窗", "w", 0},
			{"-help", "?", 0},
		}, p, from, [&](const std::string& tag, size_t i, size_t argc, int& fn2_ret2) {
			switch(tag[0]) {
			case 'n': wname = p[i]; break;
			case 'w': add__(p, from, wname); break;
			case '?':
				if(window) {
					from -= 1;
					ret2 = window->for__(p, from, no_newindow, add, env);
				}
				throw "";
			}
		});
		if(ret2 != 0) return ret2;
		for(auto& i : plugins_) {
			ret2 = i->hr_->for__(p, from, add, env); if(ret2 != 0) return ret2;
		}
		if(window) {
			ret2 = window->for__(p, from, no_newindow, add, env); if(ret2 != 0) return ret2;
			ret2 = window->for__(nb1, view, p, from, no_newindow, nb1_need_new, is1, add, env);
			if(ret2 != 0) return ret2;
		}
		if(fn2_ret == 1)
			return goodbye__(p, from);
		return 0;
	}
	plugin::view___* new_view__(const std::string& pname, const std::string& arg, const std::string& arg2) {
		plugin___* pi = nullptr;
		for(auto& pii : plugins_) {
			if(pii->hr_->id__() == pname) {
				pi = pii;
				break;
			}
		}
		if(!pi)
			throw "不支持" + pname + "插件";
		return pi->hr_->new__(arg, arg2);
	}
	int goodbye__(args___ p, size_t from) {
		if(from < p.size()) {
			switch(l4_.erret_.i_) {
				default:
				pr__(&p, "未竟 " + std::to_string(from));
				case 250: case 251: case 252:
				break;
			}
			return 0;
		}
		return 1;
	}
	void add__(const char* s, bool& dunhao, rust_add___ add, void* env) {
		if(!add)
			throw "无法返回值";
		add(s, dunhao, env);
		dunhao = true;
	}
	void get_sel__(fn___ f1, bool& dunhao, rust_add___ add, void* env) {
		GtkClipboard *cb = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
		if(cb) {
			const char* s1 = gtk_clipboard_wait_for_text(cb);
			if(f1) {
				f1();
				const char* s  = gtk_clipboard_wait_for_text(cb);
				bool b = s1 ? strcmp(s, s1) != 0 : true;
				add__(s, dunhao, add, env);
				g_free((void*)s);
				if(b) {
					if(s1)
						gtk_clipboard_set_text(cb, s1, strlen(s1));
					else
						gtk_clipboard_clear(cb);
				}
				add__(b ? "1" : "0", dunhao, add, env);
			} else {
				add__(s1, dunhao, add, env);
			}
			g_free((void*)s1);
		}
	}
	int for__(view___* view, args___ p, size_t& from, view___* by, rust_add___ add, void* env) {
		bool dunhao = false;
		auto add_u = [&](size_t i) {
			add__(std::to_string(i).c_str(), dunhao, add, env);
		};
		auto add_i = [&](int i) {
			add__(std::to_string(i).c_str(), dunhao, add, env);
		};
		auto add_i2 = [&](int i, int i2) {
			add_i(i); add_i(i2);
		};
		int ret2 = clpars__({
			{"-切", "T", 0},
			{"-焦点", "f", 0},
			{"-无签", "N", 0},
			{"-有签", "N1", 0},
			{"-得插件", "=p", 0},
			{"-得id", "=i", 0},
			{"-得上id", "=u", 0},
			{"-始数", "i", 0},
			{"-得名", "=n", 0},
			{"-得参1", "=1", 0},
			{"-得参2", "=2", 0},
			{"-得附", "=4", 0},
			{"-路径", "=3", 0},
			{"-得签", "=l", 0},
			{"-得签前", "=l2", 0},
			{"-得签后", "=l3", 0},
			{"-得签副", "=l4", 0},
			{"-得签提示" , "=l t", 0},
			{"-得签前提示", "=l2t", 0},
			{"-得签后提示", "=l3t", 0},
			{"-得签副提示", "=l4t", 0},
			{"-得页宽高", "=S", 0},
			{"-在簿", "=b", 0},
			{"-得可关闭", "=x", 0},
			{"-得开", "=o", 0},
			{"-在窗", "=w", 0},
			{"-屏宽高", "=s", 0},
			{"-上id", "u", 1},
			{"-页移", "m", 1},
			{"-页组移", "mg", 3},
			{"-得页移", "=m", 0},
			{"-页换簿", "M", 2},
			{"-得叠", "=+", 0},
			{"-得贴板", "=X", 0},
			{"-隐", "h1", 0},
			{"-显", "h", 0},
			{"-遍历", "F", 2, "簿"},
			{"-遍历转", "F ", 2},
			{"-遍历2", "F2", 1, "所有"},
			{"-遍历3", "Fe", 1},
			{"-遍历4", "F4", 1, "只比2除所在"},
			{"-顿号", ",", 0},
			{"-关闭", "x", 0},
			{"-关闭2", "x2", 0},
		}, p, from, [&](const std::string& tag, size_t i, size_t argc, int& fn2_ret2) {
			switch(tag[0]) {
			case '=': {
				bool b = false;
				switch(tag[1]) {
					case 's': {
					int sw, sh;
					scrn_w_h__(sw, sh);
					add_i2(sw, sh);
					break; }
					default:
					b = true;
					break;
				}
				if(b) {
					if(view) {
						switch(tag[1]) {
							case 'p': add__(view->plugin_id__(), dunhao, add, env); break;
							case 'i': add_u(view->id_); break;
							case 'u': add_u(view->upid_); break;
							case 'n': add__(view->name__(), dunhao, add, env); break;
							case '1': add__(view->arg1_.c_str(), dunhao, add, env); break;
							case '2': add__(view->arg2_.c_str(), dunhao, add, env); break;
							case '4': add__(view->attach_.c_str(), dunhao, add, env); break;
							case '3': add__(view->path__(), dunhao, add, env); break;
							case 'b': {
								std::string bname;
								name__(view->nb__(), bname);
								add__(bname.c_str(), dunhao, add, env);
								break; }
							case 'x': add_i(view->has_close_); break;
							case 'o': add_i(view->is_open__()); break;
							case 'm': add_i(view->page_num__()); break;
							case 'l': {
								label_box___* label_box = (label_box___*)view->label_box_;
								if(label_box) {
									GtkLabel* l;
									switch(tag[2]) {
										case '2': l = label_box->label2_; break;
										case '3': l = label_box->label3_; break;
										case '4': l = label_box->label4_; break;
										default: l = label_box->label_; break;
									}
									switch(tag[3]) {
										case 't':
										add__(gtk_widget_get_tooltip_markup(GTK_WIDGET(l)), dunhao, add, env);
										break;
										default:
										add__(gtk_label_get_label(l), dunhao, add, env);
										break;
									}
								}
								break; }
							case 'S':
							add_i2(gtk_widget_get_allocated_width(view->hr__()), gtk_widget_get_allocated_height(view->hr__()));
							break;
							case 'w': {
								window___* wi = (window___*)view->window_;
								add__(wi->name__(), dunhao, add, env);
								break; }
							case '+': add_i(view->is_die_); break;
							case 'X': get_sel__(nullptr, dunhao, add, env); break;
						}
					} else {
						add__("", dunhao, add, env);
					}
				}
				break; }
			case 'i': add_u(code_.start_i_); break;
			case 'M': {
				const std::string& name = p[i], bname = p[i + 1];
				view___* v;
				for(auto& w : windows_)
					if((v = w->views_.find__([&](auto v) {return v->name__() == name;})))
						break;
				if(!v)
					throw name + " 页无觅";
				GtkWidget* nb1;
				for(auto& w : windows_)
					if((nb1 = w->nbfind__([&](auto nb1) {return gtk_widget_get_name(nb1) == bname;})))
						break;
				if(!nb1)
					throw bname + " 簿无觅";
				gtk_widget_reparent(v->box1_, nb1);
				break; }
			case 'F': foreach__(tag, p, i, add, env, dunhao, view, this); break;
			case ',': dunhao = true; break;
			default:
				if(!view) {
					//throw p[i] + " 无法实现";
					return;
				}
				switch(tag[0]) {
				case 'T': {
					window___* w = (window___*)view->window_;
					if(!w->is_act__()) w->act__();
					view->curr__();
					break; }
				case 'f': view->focus__(); break;
				case 'N': show_tabs__(view->nb__(), tag[1]); break;
				case 'u': view->upid_ = std::stoul(p[i]); break;
				case 'm':
					switch(tag[1]) {
						case 'g':
						move__(view, p[i], tag[1], std::stoul(p[i + 1]), p[i + 2][0]);
						break;
						default:
						move__(view, p[i], 0, 0, 0);
						break;
					}
					break;
				case 'h':
					if(tag[1])
						gtk_widget_hide(view->hr__());
					else
						gtk_widget_show(view->hr__());
					break;
				case 'x':
					if(tag[1] == '2' /*|| view == by*/)
						g_idle_add(idle_close__, view);
					else
						idle_close__(view);
					break;
				}
				break;
			}
		});
		if(ret2 != 0) return ret2;
		if(view) {
			view->for__(p, from, add, env); if(ret2 != 0) return ret2;
		}
		return 0;
	}
};

int
main (int    argc,
      char **argv)
{
	main___ m;
	std::vector<char *> argv2, argv1;
	std::string src;
	{
		argv1.push_back(argv[0]);
		std::string soname = "l4.so";
		{
			std::vector<char *> argv3;
			for(int i = 1; i < argc; i++) {
				char *s = argv[i];
				if(m.ends_with(s, "--。")) {
					clpars2__(s, argv3);
					continue;
				}
				if(m.starts_with(s, "-shell-help")) {
					argv1.push_back("-zhscript-src-is-code");
					src = "-help";
					argv1.push_back("-help");
					continue;
				}
				argv1.push_back(s);
			}
			for(size_t i = 0; i < argv3.size(); i++)
				argv1.push_back(argv3[i]);
		}
		for(size_t i = 1; i < argv1.size(); i++) {
			char *s = argv1[i];
			if(m.starts_with(s, "-zhscript-l4")) {
				soname = s + 10;
				argv1.erase(argv1.begin() + i);
				break;
			}
		}
		vec___ paths;
		if(!l4_.open__(argv1[0], soname.c_str(), paths)) {
			std::cerr << l4_.err_ << std::endl;
			return 254;
		}
		if(src.empty()) {
			std::string s2;
			bool b = false;
			for(auto& s : paths) {
				auto e__ = [&](const char* x) {
					s2 = x;
					std::string s3 = s + s2;
					if(m.exist_f__(s3)) {
						src = s3;
						return true;
					}
					return false;
				};
				if(e__(".zhscript")) break;
				if(e__(".zs")) break;
				s2[0] = '_';
				for(int i = 0; i < 4; i++) {
					if(m.ends_with(s, s2)) {
						b = true;

						s = s.substr(0, s.size() - s2.size());
						fs::path p = s;
						p.replace_extension(".zhscript");
						if(!m.exist_f__(p))
							p.replace_extension(".zs");
						src = p;

						argv1.insert(argv1.begin() + 1, new__(src));
						break;
					}
					s2 += '-';
				}
				if(b) break;
			}
		}
		if(src.empty())
		for(size_t i = 1; i < argv1.size(); i++) {
			char *s = argv1[i];
			if(s[0] != '-') {
				src = s;
				break;
			}
		}
	}
	l4_.path2_(src.c_str());
	{
		std::string s;
		s += "赋予“l4.so”【顶】以“";
		s += l4_.path_;
		s += "”。";
		l4_.eval__(s.c_str());
	}
	m.init__();
#ifdef _debug_
	for(int i = 0; i < argc; i++)
		printf("%d) %s\n", i, argv[i]);
	for(size_t i = 0; i < argv1.size(); i++)
		printf("%lu) %s\n", i, argv1[i]);
#endif
	if(!l4_.eval__(src.c_str(), true, argv1.size(), argv1.data(), 1, nullptr, &m.ret_)) {
		if(l4_.erret_.is_quit_)
			m.pr__(nullptr, l4_.erret_.s_);
		else
			m.pr__(&m.ret_, l4_.erret_.s_ + l4_.erret_.s2_);
		return l4_.erret_.i_;
	}
	{
		vec___ ret;
		m.eval__("循环【‘参数数目【顶】’】【号】、‘参数‘号’【顶】’", &ret);
		argv2.push_back(argv[0]);
		for(size_t i2 = 1; i2 < ret.size(); i2++) {
			const std::string& s2 = ret[i2];
			bool has = false;
			for(size_t i = 1; i < argv1.size(); i++) {
				char *s = argv1[i];
				if(s2 == s) {
					has = true;
					argv2.push_back(s);
					break;
				}
			}
			if(!has)
				argv2.push_back(new__(s2));
		}
	}
	std::string appid;
	{
		vec___ ret;
		m.eval__("如果存在“appid”【顶】那么‘appid【顶】’", &ret);
		if(ret.size())
			appid = ret[0];
	}
	m.init__(appid);
	int err = m.run__(argv2.size(), argv2.data());
	return err ? err : l4_.erret_.i_;
}
