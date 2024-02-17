#include <gtksourceview/gtksource.h>
#include "../../../pub.h"
static plugin::pub___* pub_ = nullptr;

class view___ : public plugin::view___ {
	private:
	GtkSourceBuffer *buf_;

	std::string modified_changed_;
	static void cb_modified_changed__ (GtkTextBuffer *textbuffer, view___* thiz) {
		vec___ p {gtk_text_buffer_get_modified(textbuffer) ? "*" : ""};
		pub_->fanqiechaodan2__(thiz, thiz->modified_changed_, p);
	}

	static const int no_set_ = -1000000;
	int line_ = no_set_, line_oft_ = no_set_;
	static gboolean idle_oft__(gpointer p) {
		view___* v = (view___*)p;
		GtkTextIter ti;
		gtk_text_buffer_get_iter_at_mark (v->buf2__(), &ti, gtk_text_buffer_get_insert (v->buf2__()));
		if(v->line_ > no_set_) {
			gtk_text_iter_set_line (&ti, v->line_);
			gtk_text_iter_set_line_offset (&ti, v->line_oft_);
			v->line_ = v->line_oft_ = no_set_;
		}
		else if(v->line_oft_ > no_set_) {
			if(v->line_oft_ < 0) {
				gtk_text_buffer_get_end_iter(v->buf2__(), &ti);
				int i = gtk_text_iter_get_offset (&ti);
				v->line_oft_ += i + 1;
			}
			gtk_text_iter_set_offset (&ti, v->line_oft_);
			v->line_oft_ = no_set_;
		}
		v->scroll2__(&ti);
		return G_SOURCE_REMOVE;
	}

	GtkSourceView* hr4__() {return GTK_SOURCE_VIEW (hr_);}
	GtkTextView* hr2__() {return GTK_TEXT_VIEW (hr_);}
	GtkTextBuffer* buf2__() {return GTK_TEXT_BUFFER (buf_);}

	char* text__(bool is_sel) {
		GtkTextIter start, end;
		if(is_sel)
			gtk_text_buffer_get_selection_bounds (buf2__(), &start, &end);
		else {
			gtk_text_buffer_get_start_iter (buf2__(), &start);
			gtk_text_buffer_get_end_iter (buf2__(), &end);
		}
		return gtk_text_buffer_get_text (buf2__(), &start, &end, FALSE);
	}

	void scroll2__(GtkTextIter* ti, bool place = true) {
		if(place)
			gtk_text_buffer_place_cursor(buf2__(), ti);
		gtk_text_view_scroll_to_iter (hr2__(), ti, 0, false, 0, 0);
	}

	std::string path_;
	void openfile__(const std::string& path, bool no_undo = true) {
		path_ = path;

		gchar *contents;
		gsize length;
		GError *error=NULL;
		if(g_file_get_contents(path.c_str(),&contents,&length,&error)){
			if(no_undo)
				gtk_source_buffer_begin_not_undoable_action(buf_);
			gtk_text_buffer_set_text(buf2__(), contents, length);
			if(no_undo) {
				GtkTextIter ti;
				gtk_text_buffer_get_iter_at_offset(buf2__(), &ti, 0);
				gtk_text_buffer_place_cursor(buf2__(), &ti);

				gtk_source_buffer_end_not_undoable_action(buf_);
			}
			gtk_text_buffer_set_modified(buf2__(), false);

			g_free(contents);
		}else{
			if (error != NULL) {
				pub_->pr__(nullptr, error->message);
				g_clear_error(&error);
			}
		}
	}
	void savefile__(const std::string& filename) {
		GError *error = NULL;
		char* text = text__(false);
		pub_->perms__(filename, [&]() {
			g_file_set_contents (filename.c_str(), text, -1, &error);
			if (error != NULL) {
				pub_->pr__(nullptr, error->message);
				g_clear_error(&error);
				return false;
			} else {
				gtk_text_buffer_set_modified(buf2__(), false);
				return true;
			}
		});
		g_free (text);
	}

	int for2__(args___ args, size_t& from, int fn2_ret2) {
		return pub_->clpars__({
			{"-光标位置", "p", 1},
			{"-光标行列", "pl", 2},
			{"-语法高亮", "h", 1},
			{"-不可编辑", "E", 0},
			{"-可编辑", "E1", 0},
		}, args, from, [&](const std::string& tag, size_t i, size_t argc, int& ret2) {
			switch(tag[0]) {
				case 'p': {
					switch(tag[1]) {
					case 'l': {
						line_ = std::stoi(args[i]) - 1;
						line_oft_ = std::stoi(args[i + 1]) - 1;
						break; }
					default: {
						line_oft_ = std::stoi(args[i]);
						break; }
					}
					if(from == args.size() || args[from].empty()) {
						g_idle_add(idle_oft__, this);
					} else
						idle_oft__(this);
					break; }
				case'h': {
					const std::string &id = args[i];
					if(id.empty()) {
						gtk_source_buffer_set_highlight_syntax(buf_, false);
						break;
					}
					GtkSourceLanguageManager *slm = gtk_source_language_manager_get_default ();
					GtkSourceLanguage *sl = gtk_source_language_manager_get_language (slm, id.c_str());
					if(sl){
						gtk_source_buffer_set_language (buf_, sl);
						gtk_source_buffer_set_highlight_syntax(buf_, true);
						break;
					}
					break; }
				case 'E': gtk_text_view_set_editable(hr2__(), tag[1]); break;
			}
		}, [&]() {return fn2_ret2;});
	}

	public:
	const char* path__() {return path_.c_str();}
	int for__(args___ args, size_t& from, rust_add___ add, void* env) {
		int ret2 = for2__(args, from, pub::clpars_ret_no_);
		if(ret2 != 0) return ret2;
		bool dunhao = false;
		auto add_i = [&](int i) {
			pub_->add__(std::to_string(i).c_str(), dunhao, add, env);
		};
		return pub_->clpars__({
			{"-得选择", "X", 0},
			{"-插入", "i", 1},
			{"-头插", "ih", 1},
			{"-尾插", "if", 1},
			{"-剪切", "x", 0},
			{"-复制", "c", 0},
			{"-粘贴", "v", 0},
			{"-撤销", "u", 0},
			{"-重做", "r", 0},
			{"-得位置", "=p", 0},
			{"-得行列", "=pl", 0},
			{"-内容", " -", 1},
			{"-得内容", " =", 0},
			{"-清除", " ", 0},
			{"-搜", "S", 2},
			{"-缩进用空格", "I1", 0},
			{"-缩进甭空格", "I", 0},
			{"-刷新", "R", 0},
			{"-保存文件", "s", 0},
			{"-保存文件2", "s2", 1},
			{"-已修改", "m", 1},
		}, args, from, [&](const std::string& tag, size_t i, size_t argc, int& ret2) {
			switch(tag[0]) {
			case 'X': {
				if(gtk_text_buffer_get_has_selection(buf2__())) {
					char* text = text__(true);
					pub_->add__(text, dunhao, add, env);
					g_free (text);
					pub_->add__("1", dunhao, add, env);
				} else {
					pub_->add__("", dunhao, add, env);
					pub_->add__("0", dunhao, add, env);
				}
				break; }
			case 'i': {
				GtkTextIter i1;
				switch(tag[1]) {
				case 'h': gtk_text_buffer_get_start_iter (buf2__(), &i1); break;
				case 'f': gtk_text_buffer_get_end_iter (buf2__(), &i1); break;
				default: {
					GtkTextIter i2;
					gtk_text_buffer_get_selection_bounds (buf2__(), &i1, &i2);
					if(gtk_text_iter_get_offset (&i2) > gtk_text_iter_get_offset (&i1)) {
						gtk_text_buffer_delete(buf2__(), &i1,&i2);
					}
					break; }
				}
				const std::string& s = args[i];
				gtk_text_buffer_insert (buf2__(), &i1, s.c_str(), s.size());
				scroll2__(&i1);
				break; }
			case'x':
			case'c':
			case'v': {
				GtkClipboard *cb = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
				switch(tag[0]){
				case'x': gtk_text_buffer_cut_clipboard(buf2__(), cb, true); break;
				case'c': gtk_text_buffer_copy_clipboard(buf2__(), cb); break;
				case'v': gtk_text_buffer_paste_clipboard(buf2__(), cb, NULL, true); break;
				}
				break; }
			case 'u':
				if(gtk_source_buffer_can_undo(buf_))
					gtk_source_buffer_undo(buf_);
				break;
			case 'r':
				if(gtk_source_buffer_can_redo(buf_))
					gtk_source_buffer_redo(buf_);
				break;
			case '=':
				switch(tag[1]) {
					case 'p': {
					GtkTextIter ti;
					gtk_text_buffer_get_iter_at_mark (buf2__(), &ti, gtk_text_buffer_get_insert (buf2__()));
					switch(tag[2]) {
						case 'l':
						add_i(1 + gtk_text_iter_get_line (&ti));
						add_i(1 + gtk_text_iter_get_line_offset (&ti));
						break;
						default:
						add_i(gtk_text_iter_get_offset (&ti));
						break;
					}
					break; }
				}
				break;
			case ' ':
				switch(tag[1]) {
				case '=': {
					char* text = text__(false);
					pub_->add__(text, dunhao, add, env);
					g_free (text);
					break; }
				case '-':
					gtk_text_buffer_set_text(buf2__(), args[i].c_str(), args[i].size());
					break;
				default:
					gtk_text_buffer_set_text(buf2__(), "", 0);
					break;
				}
				break;
			case 'S': {
				const std::string &s = args[i];
				if(s.empty()) {
					if(add)
						pub_->add__("2", dunhao, add, env);
					break;
				}
				bool forward = true;
				GtkTextSearchFlags tsf = GtkTextSearchFlags(GTK_TEXT_SEARCH_TEXT_ONLY | GTK_TEXT_SEARCH_CASE_INSENSITIVE);
				pub_->clpars2_sou__(args[i + 1], [&](const std::string& tag) {
					switch(tag[0]) {
						case 'f':
						forward = false;
						break;
						case 'i':
						tsf = GTK_TEXT_SEARCH_TEXT_ONLY;
						break;
					}
				});

				GtkTextIter ti, ti2;
				GtkTextIter *ti3;
				gtk_text_buffer_get_selection_bounds (buf2__(), &ti, &ti2);
				ti3 = forward ? &ti2 : &ti;
				bool b;
				if (forward ?
						gtk_text_iter_forward_search (ti3, s.c_str(), tsf,  &ti, &ti2, nullptr)
						:
						gtk_text_iter_backward_search (ti3, s.c_str(), tsf,  &ti, &ti2, nullptr)) {
					ti3 = forward ? &ti2 : &ti;
					gtk_text_buffer_select_range (buf2__(), &ti, &ti2);
					scroll2__(ti3, false);
					b = true;
				} else
					b = false;
				if(add)
					pub_->add__(b ? "1" : "0", dunhao, add, env);
				break; }
			case 'I':
				gtk_source_view_set_insert_spaces_instead_of_tabs(hr4__(), tag[1]);
				break;
			case 'R': openfile__(path_, false); break;
			case 's': savefile__(tag[1] == '2' ? args[i] : path_); break;
			case 'm': {
				bool ins = modified_changed_.empty();
				modified_changed_ = args[i];
				if(ins)
					g_signal_connect(buf2__(), "modified-changed", G_CALLBACK(cb_modified_changed__), this);
				break; }
			}
		});
	}

	view___(const std::string& arg1, const std::string& arg2) {
		buf_ = GTK_SOURCE_BUFFER (gtk_source_buffer_new (NULL));
		hr_ = gtk_source_view_new_with_buffer(buf_);

		GtkSourceView* sv = hr4__();
		gtk_source_view_set_show_line_numbers(sv, true);
		gtk_source_view_set_tab_width(sv, 4);
		gtk_source_view_set_auto_indent (sv, true);
		gtk_source_view_set_smart_home_end(sv, GTK_SOURCE_SMART_HOME_END_ALWAYS);
		GtkSourceSpaceDrawer *ssd = gtk_source_view_get_space_drawer (sv);
		gtk_source_space_drawer_set_enable_matrix (ssd, TRUE);
		gtk_source_view_set_smart_backspace (sv, true);
	}
 	int scroll__() {return 2;}
	const char* plugin_id__();

	void open__(const std::string& path, const std::string& arg2) {
		vec___ args;
		pub_->eval__(arg2.c_str(), &args);
		size_t from = 0;

		for2__(args, from, pub::clpars_throw_);

		if(!path.empty()) openfile__(path);
	}
};

class plugin___ : public plugin::base___ {
	public:
	plugin::view___* new__(const std::string& arg1, const std::string& arg2) {
		view___* v = new view___(arg1, arg2);
		v->open__(arg1, arg2);
		return v;
	}
	const char* id__() {return "源码";}

	int for__(args___ args, size_t& from, rust_add___ add, void* env) {
		bool dunhao = false;
		return pub_->clpars__({
			{"-列可语法高亮", "H", 1},
		}, args, from, [&](const std::string& tag, size_t i, size_t argc, int& ret2) {
			switch(tag[0]) {
				case 'H': {
					GtkSourceLanguageManager *slm = gtk_source_language_manager_get_default ();
					const gchar * const *ids = gtk_source_language_manager_get_language_ids (slm);
					if(ids) for (int i2 = 0; ids[i2] != NULL; i2++) {
						const gchar * id = ids[i2];
						GtkSourceLanguage *sl = gtk_source_language_manager_get_language (slm, id);
						vec___ p {id,
							gtk_source_language_get_name (sl),
							gtk_source_language_get_section (sl),
							gtk_source_language_get_hidden (sl) ? "0" : "1"}, ret;
						pub_->fanqiechaodan2__(nullptr, args[i], p, &ret);
						if(add) for(auto& i3 : ret) {
							add(i3.c_str(), 0, env);
						}
					}
					break; }
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