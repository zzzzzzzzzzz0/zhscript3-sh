#include <webkit2/webkit2.h>
#include <JavaScriptCore/JavaScript.h>
#include <webkitdom/webkitdom.h>
#include "../../../pub.h"
static plugin::pub___* pub_ = nullptr;

static std::string zs_("zhscript");

#include "../../../../../zhscript2-rust-sh/webkitx/src/Chan.cpp"
class Chanx_ : public Chan_ {
	std::string h_ = "cb_send_request__";
	void get__(std::string& line) {
		if(!code_.empty() && pub_->starts_with(line.c_str(), h_)) {
			vec___ args, ret;
			{
				std::string url = line.substr(h_.size(), line.size() - h_.size() - 1);
				line.clear();
				args.push_back(url);
			}
			pub_->eval__(code_.c_str(), args, &ret);
			switch(ret.size()) {
			case 1:
				line += ret[0];
				break;
			}
		} else {
			line.clear();
		}
		line += "\n";
		write__(line.c_str(), line.size());
	}

	public:
	std::string code_;
};
static Chanx_ chan_;

class view___ : public plugin::view___ {
	private:
	static void add__(JSValueRef& value, JSGlobalContextRef& context, vec___& p) {
		if(JSValueIsArray(context, value)) {
			JSObjectRef o = JSValueToObject(context, value, NULL);
			JSPropertyNameArrayRef properties = JSObjectCopyPropertyNames(context, o);
			size_t count =  JSPropertyNameArrayGetCount(properties);
			JSPropertyNameArrayRelease(properties);

			for (size_t i = 0; i < count; i++) {
				JSValueRef propertyValue = JSObjectGetPropertyAtIndex(context, o, i, NULL);
				add__(propertyValue, context, p);
			}
			return;
		}

		JSStringRef js_str_value;
		gchar      *str_value;
		gsize       str_length;

		js_str_value = JSValueToStringCopy (context, value, NULL);
		str_length = JSStringGetMaximumUTF8CStringSize (js_str_value);
		str_value = (gchar *)g_malloc (str_length);
		JSStringGetUTF8CString (js_str_value, str_value, str_length);
		JSStringRelease (js_str_value);
		p.push_back(str_value);
		g_free (str_value);
	}

	class Data1_ {
	public:
		view___* v_;
		bool free_ = false;
		std::string s_;
		vec___ p_;
		bool over_ = false;
		void wait__(const std::string& s) {
			run_js__(v_->hr2__(), s.c_str(), this);
			for(; !over_;)
				pub_->not_block__();
		}
		void wait__(const std::string& s, bool& dunhao, rust_add___ add, void* env) {
			wait__(s);
			for(auto& i : p_)
				pub_->add__(i.c_str(), dunhao, add, env);
		}
	};

	static void finished__(GObject *object, GAsyncResult *result, gpointer user_data) {
		WebKitJavascriptResult *js_result;
		GError                 *error = NULL;
		Data1_* d1 = (Data1_*)user_data;

		js_result = webkit_web_view_run_javascript_finish (WEBKIT_WEB_VIEW (object), result, &error);
		if (error) {
			pub_->pr__(nullptr, error->message);
			g_error_free (error);
		} else {
			JSGlobalContextRef context = webkit_javascript_result_get_global_context (js_result);
			JSValueRef value = webkit_javascript_result_get_value (js_result);
			if(!d1->free_) {
				if(!JSValueIsUndefined(context, value))
					add__(value, context, d1->p_);
			} else {
				vec___ p;
				add__(value, context, p);
				pub_->fanqiechaodan2__(d1->v_, d1->s_, p);
			}
			d1->over_ = true;
			webkit_javascript_result_unref (js_result);
		}
		if(d1->free_)
			delete d1;
	}

	static void run_js__(WebKitWebView *wv, const char* s, Data1_* ud) {
		if(ud)
			webkit_web_view_run_javascript (wv, s, NULL, finished__, ud);
		else
			webkit_web_view_run_javascript (wv, s, NULL, nullptr, NULL);
	}

	static void cb_title__(WebKitWebView *webView, GParamSpec *pspec, view___* thiz) {
#ifdef _debug_
		printf("cb_title__ %s %s %s\n", pspec->_nick, pspec->_blurb, pspec->name);
#endif
		vec___ p {"标题", webkit_web_view_get_title(webView)};
		pub_->fanqiechaodan3_ic__(thiz, p);
	}

	static void std__(std::string& s) {
		std::string s2 = "<meta charset=";
		if(s.find(s2) == std::string::npos)
			s = s2 + "utf-8 />" + s;
		s2 = "function z$(";
		if(s.find(s2) == std::string::npos)
			s = "<script>" + s2 + "s){prompt('zhscript-v',s);}function z$1(s){return eval(prompt('zhscript',s));}</script>" + s;
	}

	std::string code_mouse_target_changed_;
	static void cb_mouse_target_changed__(WebKitWebView *webView, WebKitHitTestResult *hitTestResult, guint mouseModifiers, view___* thiz) {
		//auto s = [](const char* s) {return s ? s : "NULL";};
		if (webkit_hit_test_result_context_is_link(hitTestResult)) {
			vec___ p {"链接",
					(webkit_hit_test_result_get_link_uri(hitTestResult))};
			const char* s;
			s = webkit_hit_test_result_get_link_label(hitTestResult);
			if(s)
				p.push_back(s);
			s = webkit_hit_test_result_get_link_title(hitTestResult);
			if(s)
				p.push_back(s);
			pub_->fanqiechaodan2__(thiz, thiz->code_mouse_target_changed_, p);
		}
		if (webkit_hit_test_result_context_is_image(hitTestResult)) {
			vec___ p {"图片", (webkit_hit_test_result_get_image_uri (hitTestResult))};
			pub_->fanqiechaodan2__(thiz, thiz->code_mouse_target_changed_, p);
		}
		if (webkit_hit_test_result_context_is_media(hitTestResult)) {
			vec___ p {"媒体", (webkit_hit_test_result_get_media_uri (hitTestResult))};
			pub_->fanqiechaodan2__(thiz, thiz->code_mouse_target_changed_, p);
		}
	}
	void ins_mouse_target_changed__(const std::string& code) {
		bool ins = code_mouse_target_changed_.empty();
		code_mouse_target_changed_ = code;
		if(ins)
			g_signal_connect(hr_, "mouse-target-changed", G_CALLBACK(cb_mouse_target_changed__), this);
	}

	static const int no_set_ = -1;
	int line_ = no_set_, line_oft_ = no_set_;

	std::string code_load_changed_;
	static void cb_load_changed__(WebKitWebView  *web_view, WebKitLoadEvent load_event, view___* thiz) {
		const char* s = nullptr;
		switch (load_event) {
		case WEBKIT_LOAD_STARTED:    s = "始"; break;
		case WEBKIT_LOAD_FINISHED:   s = "终";
			if(thiz->line_ > no_set_) {
				run_js__(thiz->hr2__(), ("window.scrollTo(" + std::to_string(thiz->line_oft_) + "," +
					std::to_string(thiz->line_) + ")").c_str(), nullptr);
				thiz->line_ = thiz->line_oft_ = no_set_;
			}
			break;
		case WEBKIT_LOAD_REDIRECTED: s = "重定向"; break;
		case WEBKIT_LOAD_COMMITTED:  s = "确定";
			if(thiz->need_focus_) thiz->focus__();
			break;
		}
		if(s) {
			vec___ p;
			if(thiz->code_load_changed_.empty())
				p.push_back("装载");
			p.push_back(s);
			const char* url = webkit_web_view_get_uri(web_view);
			p.push_back(url ? url : "");
			if(!thiz->code_load_changed_.empty())
				pub_->fanqiechaodan2__(thiz, thiz->code_load_changed_, p);
			else
				pub_->fanqiechaodan3__(thiz, p);
		}
	}

	static GtkWidget* cb_create__ (WebKitWebView *web_view, WebKitNavigationAction *navigation_action, view___* by) {
		view___* view = new view___(web_view, nullptr);
		if(!by->code_mouse_target_changed_.empty())
			view->ins_mouse_target_changed__(by->code_mouse_target_changed_);
		return pub_->pack__(view, by, after_curr_page_);
	}
	static gboolean cb_close__(WebKitWebView* webView, view___* thiz) {
		pub_->close__(thiz);
		return TRUE;
	}

	std::string code_, cookie_;
	vec___ args_;
	static void cb_uri_scheme_request__ (WebKitURISchemeRequest *request, gpointer user_data) {
		auto out = [&](std::string &contents, bool is_file, const char* contype) {
			GInputStream *stream;
			if(is_file) {
				GFile *file = g_file_new_for_path(contents.c_str());
				stream = (GInputStream *)g_file_read(file, NULL, NULL);
				webkit_uri_scheme_request_finish(request, stream, -1, contype);
				g_object_unref(file);
				g_object_unref (stream);
			} else {
				gsize stream_length = contents.length();
				GString *result = g_string_new(contents.c_str());
				contents.clear();
				//stream_length = result->len;
				//stream = g_memory_input_stream_new_from_data (contents.c_str(), stream_length, (GDestroyNotify) g_free);
				stream = g_memory_input_stream_new_from_data(g_string_free(result, FALSE), stream_length, g_free);
				webkit_uri_scheme_request_finish (request, stream, stream_length, contype);
			}
		};
		vec___ ret;
		do {
			{
				gchar *code = g_uri_unescape_string(webkit_uri_scheme_request_get_path (request), NULL);
				view___* thiz = (view___*)user_data;
				pub_->fanqiechaodan2__(thiz, thiz->code_ + code, thiz->args_, &ret);
				if(ret.size() > 3) {
					GError *error = g_error_new (1, 0, "ret.size%lu<hr>%s", ret.size(), code);
					g_free(code);
					webkit_uri_scheme_request_finish_error (request, error);
					g_error_free (error);
					break;
				}
				g_free(code);
			}
			if(ret.size() == 0) {
				std::string s;
				out(s, false, "text/html");
				break;
			}
			if(ret.size() > 1 && ret[1] == "本地") {
				out(ret[0], true, ret.size() > 2 ? ret[2].c_str() : nullptr);
				break;
			}
			std__(ret[0]);
			out(ret[0], false, ret.size() > 1 && !ret[1].empty() ? ret[1].c_str() : "text/html");
		} while(false);
	}
	static gboolean cb_script_dialog__ (WebKitWebView *web_view, WebKitScriptDialog *dialog, view___* user_data) {
		switch (webkit_script_dialog_get_dialog_type(dialog)) {
		case WEBKIT_SCRIPT_DIALOG_PROMPT: {
			const char* s = webkit_script_dialog_get_message(dialog);
			if(s == zs_ || s == zs_ + "-v") {
				vec___ ret;
				if(pub_->fanqiechaodan__(user_data, webkit_script_dialog_prompt_get_default_text(dialog), &ret) < 0)
					return true;
				if(ret.size() == 0)
					return true;
				bool good;
				if(s == zs_)
					good = true;
				else {
					if(ret.size() == 1 && ret[0].empty())
						return true;
					good = false;
				}
				if(good) {
					std::string s1;
					auto add = [&](std::string &s2) {
						if(s2 == "undefined" || s2 == "null" || s2 == "true" || s2 == "false")
							s1 += s2;
						else {
							s1 += '"';
							for(size_t i = 0; i < s2.length(); i++) {
								char c = s2[i];
								switch(c) {
									case '"': case '\\': case '\n': case '\r':
									s1 += '\\';
									switch(c) {
										case '\n': c = 'n'; break;
										case '\r': c = 'r'; break;
									}
									break;
								}
								s1 += c;
							}
							s1 += '"';
						}
					};
					if(ret.size() == 1)
						add(ret[0]);
					else {
						s1 += '[';
						for(size_t i = 0; i < ret.size(); i++) {
							if(i > 0)
								s1 += ',';
							add(ret[i]);
						}
						s1 += ']';
					}
					webkit_script_dialog_prompt_set_text(dialog, s1.c_str());
				} else
					pub_->pr__(&ret, "不能处理：");
				return true;
			}
			break; }
		default: break;
		}
		return false;
	}

	WebKitWebContext* ctt_ = nullptr;

	int for2__(args___ args, size_t& from) {
		return pub_->clpars__({
			{"-缩放", "z", 1},
			{"-背景色", "B", 1},
			{"-光标行列", "pl", 2},
		}, args, from, [&](const std::string& tag, size_t i, size_t argc, int& ret2) {
			switch(tag[0]) {
			case 'z':
				webkit_web_view_set_zoom_level(hr2__(), std::stod(args[i]));
				break;
			case 'B': {
				GdkRGBA bc;
				const std::string& s = args[i];
				if(!gdk_rgba_parse (&bc, s.c_str()))
					throw s + " 格式错误";
				webkit_web_view_set_background_color(hr2__(), &bc);
				break; }
			case 'p': {
				switch(tag[1]) {
				case 'l': {
					line_ = std::stoi(args[i]);
					line_oft_ = std::stoi(args[i + 1]);
					break; }
				}
				break; }
			}
		});
	}
	int for2__(args___ args, size_t& from, rust_add___ add, void* env, int fn2_ret2) {
		bool dunhao = false;
		return pub_->clpars__({
			{"-插脚", "j", 1},
			{"-插脚2", "j2", 2, "代码获取返回值"},
			{"-插脚3", "=3", 1},
			{"-得选择", "X", 0},
			{"-得行列", "=pl", 0},
			{"-页得id", "=i", 1},
			{"-辑令", "e", 1},
			{"-辑令2", "e2", 2, "有参数那种"},
			{"-剪切", "ex", 0},
			{"-复制", "ec", 0},
			{"-粘贴", "ev", 0},
			{"-撤销2", "eu", 0},
			{"-重做2", "er", 0},
			{"-撤销", "<", 0},
			{"-重做", ">", 0},
			{"-刷新", "r", 0},
			{"-网址", "u", 1},
			{"-搜", "S", 2},
			{"-调试器", "I", 0},
			{"-调试器在", "I?", 0},
			{"-探目标", "T", 1},
		}, args, from, [&](const std::string& tag, size_t i, size_t argc, int& ret2) {
			switch(tag[0]) {
			case 'j': {
				Data1_* d = nullptr;
				switch(tag[1]) {
					case '2':
					d = new Data1_ {this, true, args[i + 1]};
					break;
				}
				run_js__(hr2__(), args[i].c_str(), d);
				break; }
			case 'X': {
				Data1_ d {this};
				d.wait__("var s=window.getSelection();if(s.rangeCount>0)s.getRangeAt(0).toString();");
				/*pub_->get_sel__([&] {
					webkit_web_view_execute_editing_command(hr2__(), WEBKIT_EDITING_COMMAND_COPY);
				}, dunhao, add, env);*/
				/*WebKitDOMDocument* doc ;//= webkit_web_view_get_dom_document(hr2__())
				WebKitDOMDOMWindow* win = webkit_dom_document_get_default_view(WEBKIT_DOM_DOCUMENT(doc));
				WebKitDOMDOMSelection* sel = webkit_dom_dom_window_get_selection(WEBKIT_DOM_DOM_WINDOW(win));
				WebKitDOMRange* range = webkit_dom_dom_selection_get_range_at(WEBKIT_DOM_DOM_SELECTION(sel), 0, NULL);*/
				// wxString(webkit_dom_range_get_text(WEBKIT_DOM_RANGE(range)), wxConvUTF8);
				if(!d.p_.empty()) {
					pub_->add__(d.p_[0].c_str(), dunhao, add, env);
					pub_->add__("1", dunhao, add, env);
				} else {
					pub_->add__("", dunhao, add, env);
					pub_->add__("0", dunhao, add, env);
				}
				break; }
			case '=': {
				Data1_ d {this};
				std::string s;
				switch(tag[1]) {
					case 'p':
					s = "[document.documentElement.scrollTop||document.body.scrollTop,"
						"document.documentElement.scrollLeft||document.body.scrollLeft]";
					break;
					case 'i':
					s = "var a=document.querySelectorAll('" + args[i] + "');if(a.length>0)a[0].id;";
					break;
					case '3':
					s = args[i];
					break;
				}
				d.wait__(s, dunhao, add, env);
				break; }
			case 'e': {
				switch(tag[1]) {
					case 'x':
					webkit_web_view_execute_editing_command(hr2__(), WEBKIT_EDITING_COMMAND_CUT);
					break;
					case 'c':
					webkit_web_view_execute_editing_command(hr2__(), WEBKIT_EDITING_COMMAND_COPY);
					break;
					case 'v':
					webkit_web_view_execute_editing_command(hr2__(), WEBKIT_EDITING_COMMAND_PASTE_AS_PLAIN_TEXT);
					break;
					case 'u':
					webkit_web_view_execute_editing_command(hr2__(), WEBKIT_EDITING_COMMAND_UNDO);
					break;
					case 'r':
					webkit_web_view_execute_editing_command(hr2__(), WEBKIT_EDITING_COMMAND_REDO);
					break;
					case '2':
					webkit_web_view_execute_editing_command_with_argument(hr2__(), args[i].c_str(), args[i + 1].c_str());
					break;
					default:
					webkit_web_view_execute_editing_command(hr2__(), args[i].c_str());
					break;
				}
				break; }
			case '<': webkit_web_view_go_back(hr2__()); break;
			case '>': webkit_web_view_go_forward (hr2__()); break;
			case 'r': webkit_web_view_reload (hr2__()); break;
			case 'u': load__(args[i]); break;
			case 'S': {
				const std::string &s = args[i];
				if(s.empty()) {
					pub_->add__("2", dunhao, add, env);
					break;
				}
				WebKitFindOptions fo = WEBKIT_FIND_OPTIONS_CASE_INSENSITIVE;
				pub_->clpars2_sou__(args[i + 1], [&](const std::string& tag) {
					switch(tag[0]) {
						case 'f':
						fo = WebKitFindOptions(fo | WEBKIT_FIND_OPTIONS_BACKWARDS);
						break;
						case 'i':
						fo = WebKitFindOptions(fo & ~WEBKIT_FIND_OPTIONS_CASE_INSENSITIVE);
						break;
					}
				});

				WebKitFindController *fc = webkit_web_view_get_find_controller(hr2__());
				webkit_find_controller_search_finish(fc);
				webkit_find_controller_search (fc, s.c_str(), fo, G_MAXUINT);
				bool b = true;
				if(add)
					pub_->add__(b ? "1" : "0", dunhao, add, env);
				break; }
			case 'I': {
				WebKitWebInspector *wi = webkit_web_view_get_inspector (hr2__());
				switch(tag[1]) {
				case '?':
					if(webkit_web_inspector_is_attached(wi))
						pub_->add__("1", dunhao, add, env);
					break;
				default: webkit_web_inspector_show(wi); break;
				}
				break; }
			case 'T':
				ins_mouse_target_changed__(args[i]);
				break;
			}
		}, [&]() {return fn2_ret2;});
	}

	void cfg__() {
		{
			static std::string webkitx;
			if(webkitx.empty()) {
				vec___ ret;
				pub_->eval__("‘l4.so【顶】’", &ret);
				pub_->replace_filename(ret[0], "webkitx", webkitx);
				pub_->eval__(("赋予“webkitx”【外壳】以“" + webkitx + "”。").c_str());
			}
			webkit_web_context_set_web_extensions_directory(ctt_, webkitx.c_str());
		}
		chan_.init__();
		webkit_web_context_set_web_extensions_initialization_user_data(ctt_, chan_.gvar__());

		webkit_web_context_register_uri_scheme(ctt_, zs_.c_str(), cb_uri_scheme_request__, this, NULL);
		WebKitSecurityManager *wksm = webkit_web_context_get_security_manager(ctt_);
		webkit_security_manager_register_uri_scheme_as_local(wksm, zs_.c_str());
		webkit_security_manager_register_uri_scheme_as_cors_enabled(wksm, zs_.c_str());
	}

	public:
	const char* path__() {
		return webkit_web_view_get_uri(hr2__());
	}
	int for__(args___ args, size_t& from, rust_add___ add, void* env) {
		int ret2 = for2__(args, from, add, env, pub::clpars_ret_no_);
		if(ret2 != 0) return ret2;
		return for2__(args, from);
	}

	view___(WebKitWebView *rv, const char* cookie) {
		if(rv) {
			hr_ = webkit_web_view_new_with_related_view(rv);
		} else {
			if(cookie) {
				ctt_ = webkit_web_context_get_default();
				static bool cfg = false;
				if(!cfg) {
					cfg = true;
					cfg__();
				}
			} else {
				ctt_ = webkit_web_context_new_ephemeral();
				cfg__();
			}
			hr_ = webkit_web_view_new_with_context(ctt_);
		}

		WebKitSettings *wks = webkit_web_view_get_settings (hr2__());
		webkit_settings_set_allow_file_access_from_file_urls(wks, true);
		webkit_settings_set_allow_universal_access_from_file_urls(wks, true);
		webkit_settings_set_enable_developer_extras(wks, true);
		webkit_settings_set_enable_write_console_messages_to_stdout(wks, true);
		webkit_settings_set_enable_webgl(wks, true);

		g_signal_connect(hr_, "script_dialog", G_CALLBACK(cb_script_dialog__), this);
		g_signal_connect(hr_, "notify::title", G_CALLBACK(cb_title__), this);
		g_signal_connect(hr_, "create", G_CALLBACK(cb_create__), this);
		g_signal_connect(hr_, "close", G_CALLBACK(cb_close__), this);
		g_signal_connect(hr_, "load-changed", G_CALLBACK(cb_load_changed__), this);

		if(cookie) {
			cookie_ = cookie;
			WebKitCookieManager* cm = webkit_web_context_get_cookie_manager(ctt_);
			size_t i = cookie_.length();
			webkit_cookie_manager_set_persistent_storage(cm, cookie_.c_str(),
					i >= 3
					&& cookie_[i - 3] == '.'
					&& cookie_[i - 2] == 'd'
					&& cookie_[i - 1] == 'b'
					||
					i >= 7
					&& cookie_[i - 7] == '.'
					&& cookie_[i - 6] == 's'
					&& cookie_[i - 5] == 'q'
					&& cookie_[i - 4] == 'l'
					&& cookie_[i - 3] == 'i'
					&& cookie_[i - 2] == 't'
					&& cookie_[i - 1] == 'e'
					?
					WEBKIT_COOKIE_PERSISTENT_STORAGE_SQLITE :
					WEBKIT_COOKIE_PERSISTENT_STORAGE_TEXT);
			WebKitCookieAcceptPolicy cap = WEBKIT_COOKIE_POLICY_ACCEPT_ALWAYS;
			webkit_cookie_manager_set_accept_policy(cm, cap);
		}
	}
	WebKitWebView* hr2__() {return WEBKIT_WEB_VIEW(hr_);}

	void load__(const std::string& uri) {
		std::string th = "text|";
		if(pub_->starts_with(uri, th)) {
			gchar *buf = nullptr;
			g_file_get_contents(uri.substr(th.size()).c_str(), &buf, NULL, NULL);
			if(buf) {
				webkit_web_view_load_plain_text(hr2__(), buf);
				g_free(buf);
			}
			return;
		}
		th = "gbk|";
		if(pub_->starts_with(uri, th)) {
			GFile *f = g_file_new_for_path(uri.substr(th.size()).c_str());
			GBytes *buf = g_file_load_bytes (f, NULL, NULL, NULL);
			if(buf) {
				webkit_web_view_load_bytes(hr2__(), buf, "text/plain", "gb18030", NULL);
				g_bytes_unref(buf);
			}
			g_object_unref(f);
			return;
		}
		webkit_web_view_load_uri(hr2__(), uri.c_str());
	}
	void open__(const std::string& uri, const std::string& arg2) {
		vec___ args;
		pub_->eval__(arg2.c_str(), &args);
		args_.clear();
		size_t from = 0;

		if(pub_->clpars__({
			{"-代码", "c", 1},
			{"-参", "a", 0},
			{"-载回调", "cd", 1},
		}, args, from, [&](const std::string& tag, size_t i, size_t argc, int& ret2) {
			switch(tag[0]) {
			case 'c':
				switch(tag[1]) {
					case 'd': code_load_changed_ = args[i]; break;
					default: code_ = args[i]; break;
				}
				break;
			case 'a':
				for(;from < args.size();) {
					args_.push_back(args[from++]);
				}
				break;
			}
		}) == 0) {
			for2__(args, from);
		}

		load__(uri);

		for2__(args, from, nullptr, nullptr, pub::clpars_throw_);
	}
	const char* plugin_id__();
};

class plugin___ : public plugin::base___ {
	public:
	plugin::view___* new__(const std::string& arg1, const std::string& arg2) {
		vec___ args;
		pub_->eval__(arg2.c_str(), &args);
		size_t from = 0;
		std::string cookie;

		pub_->clpars__({
			{"-cookie", "c", 1},
		}, args, from, [&](const std::string& tag, size_t i, size_t argc, int& ret2) {
			switch(tag[0]) {
			case 'c': cookie = args[i]; break;
			}
		});
		std::string arg2a;
		if(from > 0 && from < args.size())
			arg2a = arg2.substr(arg2.rfind("、", arg2.find(args[from])) + 3);

		view___* v = new view___(nullptr, cookie.empty() ? nullptr : cookie.c_str());
		v->open__(arg1, from == 0 ? arg2 : arg2a);
		return v;
	}
	const char* id__() {return "网页";}

	int for__(args___ args, size_t& from, rust_add___ add, void* env) {
		return pub_->clpars__({
			{"-址滤", "c", 1},
			{"-址滤+" , "c+", 1},
			{"-址滤-" , "c-", 1},
		}, args, from, [&](const std::string& tag, size_t i, size_t argc, int& ret2) {
			switch(tag[0]) {
				case 'c': pub_->op__(args[i], tag[1], chan_.code_); break;
			}
		});
	}
};
static plugin___ pub2_;

const char* view___::plugin_id__() {return pub2_.id__();}

extern "C" {

void pub__(plugin::pub___* pub) {pub_ = pub;}
plugin::base___* pub2__() {return &pub2_;}

}
