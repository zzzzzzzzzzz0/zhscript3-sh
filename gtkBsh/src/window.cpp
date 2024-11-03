#include "pub2.h"
#include "xianchang.h"
#include "screenshot.h"
#include "pub3.h"

/*
	if(l4_.dbg_bp2_("-o-")) {
	}
*/

int window___::for__(args___ p, size_t& from, bool restart, rust_add___ add, void* env) {
	bool dunhao = false;
	auto add_i = [&](int i) {
		pub_->add__(std::to_string(i).c_str(), dunhao, add, env);
	};
	auto add_i2 = [&](int i, int i2) {
		add_i(i); add_i(i2);
	};
	int ret = pub_->clpars__({
		{"-移动", "m", 2},
		{"-标题", "t", 1},
		{"-副标题", "ts", 1},
		{"-置顶", "T1", 0},
		{"-撤置顶", "T", 0},
		{"-置底", "B1", 0},
		{"-撤置底", "B", 0},
		{"-总可见", "D1", 0},
		{"-撤总可见", "D", 0},
		{"-宽高", "s", 2},
		{"-预宽高", "sd", 2},
		{"-定宽高", "sr", 2},
		{"-居中", "c", 0},
		{"-最大化", "A1", 0},
		{"-撤最大化", "A", 0},
		{"-最小化", "I1", 0},
		{"-撤最小化", "I", 0},
		{"-全屏", "F1", 0},
		{"-撤全屏", "F", 0},
		{"-激活", "P", 0},
		{"-得移动", "=m", 0},
		{"-得宽高", "=s", 0},
		{"-得修饰宽高", "=sd", 0},
		{"-是最大化", "=a", 0},
		{"-是最小化", "=i", 0},
		{"-是激活", "=A", 0},
		{"-是全屏", "=f", 0},
		{"-截图", "S", 1},
		{"-图标", "i", 1},
		{"-不在任务栏", "!t1", 0},
		{"-无修饰", "!d", 0},
		{"-有修饰", "!d1", 0},
		{"-有无修饰", "!d@", 0},
		{"-换修饰", "!d@", 0},
		{"-标题栏1", "!b", 1},
		{"-标题栏2测", "!b2", 5},
		{"-修饰1", "(", 0},
		{"-修饰2", "(", 0},
		{"-修饰3", "(", 0},
		{"-修饰4", "(", 0},
		{"-无焦", "!f", 0},
		{"-类名", "C", 2},
		{"-自绘", "a", 0},
		{"-按键", "ek", 1},
		{"-状态", "es", 1},
		{"-移动变", "em", 1},
		{"-宽高变", "eS", 1},
		{"-主", "M", 0},
		{"-名2", "n", 1},
	}, p, from, [&](const std::string& tag, size_t i, size_t argc, int& fn2_ret2) {
		if(restart)
			switch(tag[0]) {
			case '=': break;
			default: return;
			};
		switch(tag[0]) {
		case 'm': {
			int x2 = std::stoi(p[i]), y2 = std::stoi(p[i + 1]);
			gtk_window_move(hr2__(), x2, y2);
			break; }
		case 't': {
			const std::string &s = p[i];
			switch(tag[1]) {
			case 's':
				if(titlebar_) {
					GtkHeaderBar *hb = GTK_HEADER_BAR(titlebar_);
					gtk_header_bar_set_subtitle(hb, s.c_str());
				}
				break;
			default:
				gtk_window_set_title (hr2__(), s.c_str());
				break;
			}
			break; }
		case 'T': gtk_window_set_keep_above (hr2__(), tag[1]); break;
		case 'B': gtk_window_set_keep_below (hr2__(), tag[1]); break;
		case 'D':
			if(tag[1]) gtk_window_stick(hr2__());
			else     gtk_window_unstick(hr2__());
			break;
		case 's': {
			const std::string &w1 = p[i], &h1 = p[i + 1];
			int w = w1.empty() || w1[0] == '=' ? 0 : std::stoi(w1);
			int h = h1.empty() || h1[0] == '=' ? 0 : std::stoi(h1);
			if(w < 0 || h < 0) {
				int sw, sh;
				scrn_w_h__(sw, sh);
				if(w < 0)
					w += sw;
				if(h < 0)
					h += sh;
			}
			if(w == 0) {
				w = h;
				if(!w1.empty()) {
					std::string w2 = w1.substr(1);
					if(!w2.empty())
						w += std::stoi(w2);
				}
			}
			if(h == 0) {
				h = w;
				if(!h1.empty()) {
					std::string h2 = h1.substr(1);
					if(!h2.empty())
						h += std::stoi(h2);
				}
			}
			if(w <= 0 || h <= 0)
				break;
			switch(tag[1]) {
			default:  gtk_window_resize(hr2__(), w, h); break;
			case 'd': gtk_window_set_default_size(hr2__(), w, h); break;
			case 'r': gtk_widget_set_size_request(hr_, w, h); break;
			}
			break; }
		case 'c': gtk_window_set_position(hr2__(), GTK_WIN_POS_CENTER); break;
		case 'A':
			if(tag[1]) gtk_window_maximize (hr2__());
			else     gtk_window_unmaximize (hr2__());
			break;
		case 'I':
			if(tag[1]) gtk_window_iconify (hr2__());
			else     gtk_window_deiconify (hr2__());
			break;
		case 'F':
			switch(tag[1]) {
			case '1':  gtk_window_fullscreen(hr2__()); break;
			default: gtk_window_unfullscreen(hr2__()); break;
			}
			break;
		case 'P': act__(); break;
		case '=':
			switch(tag[1]) {
				case 'm': {
					int x, y;
					gtk_window_get_position(hr2__(), &x, &y);
					add_i2(x, y);
					break; }
				case 's': {
					int w, h;
					switch(tag[2]) {
					case 'd': w = border_w_; h = border_h_; break;
					default: gtk_window_get_size(hr2__(), &w, &h); break;
					}
					add_i2(w, h);
					break; }
				case 'a': add_i(gtk_window_is_maximized(hr2__())); break;
				case 'i': add_i(is_icon_); break;
				case 'A': add_i(is_act__()); break;
				case 'f': {
					int sw, sh, w, h;
					scrn_w_h__(sw, sh);
					gtk_window_get_size(hr2__(), &w, &h);
					add_i(w >= sw && h >= sh);
					break; }
				default:  break;
			}
			break;
		case 'S': if(screenshot__(hr__(), p[i].c_str())) add_i(1); break;
		case 'i': {
			vec___ p2;
			pub_->eval__(p[i].c_str(), &p2);
			if(p2.size() > 0) {
				GdkPixbuf* pb = pixbuf__(p2, 0);
				gtk_window_set_icon(hr2__(), pb);
				g_object_unref(pb);
			}
			break; }
		case '!':
			switch(tag[1]) {
			case 't':
				gtk_window_set_skip_taskbar_hint(hr2__(), tag[2] == '@' ? !gtk_window_get_skip_taskbar_hint(hr2__()) : tag[2]);
				break;
			case 'd':
				gtk_window_set_decorated(hr2__(), tag[2] == '@' ? !gtk_window_get_decorated(hr2__()) : tag[2]);
				break;
			case 'f':
				gtk_window_set_accept_focus(hr2__(), false);
				break;
			case 'b': {
				titlebar_ = gtk_header_bar_new();
				GtkHeaderBar *hb = GTK_HEADER_BAR(titlebar_);
				gtk_header_bar_set_has_subtitle (hb, true);
				gtk_header_bar_set_show_close_button (hb, true);

				int h = -1;
				switch(tag[2]) {
					case '2': {
					h = std::stoi(p[i + 2]);
					titlebar_w_1_ = std::stoi(p[i + 3]);
					titlebar_w_2_ = std::stoi(p[i + 4]);

					GtkWidget* box = gtk_scrolled_window_new(nullptr, nullptr);
					titlebar_b_ = box;

					vec___ p3;
					size_t from3 = 0;
					pub_->eval__(p[i + 1].c_str(), &p3);
					view___* v = nullptr;
					ret = buju2_->for__(this, GTK_CONTAINER(box), nullptr, v, p3, from3, false, true, false, nullptr, nullptr);

					//gtk_header_bar_set_title_widget(hb, box);
					gtk_header_bar_set_custom_title(hb, box);
					gtk_widget_show_all(box);
					break; }
				}

				GtkWidget *left1 = nullptr, *right1 = nullptr;
				std::string code_;
				char pos_ = '>';

				vec___ p3;
				size_t from3 = 0;
				pub_->eval__(p[i].c_str(), &p3);
				pub_->clpars__({
					{"-加钮", "b", 1},
					{"-加字钮", "bT", 1},
				}, p3, from3, [&](const std::string& tag, size_t i, size_t argc, int& fn2_ret2) {
					switch(tag[0]) {
					case 'b': {
						vec___ p2;
						size_t from2 = 0;
						button___* btn = new button___(nullptr, pub_);
						pub_->eval__(p3[i].c_str(), &p2);
						pub_->clpars__({
							{"-左", "P<", 0},
							{"-右", "P>", 0},
							{"-代码", "c", 1},
							{"-名", "n", 1},
						}, p2, from2, [&](const std::string& tag, size_t i, size_t argc, int& fn2_ret2) {
							switch(tag[0]) {
							case 'P': pos_ = tag[1]; break;
							case 'c': code_ = p2[i]; break;
							case 'n': btn->name_ = p2[i]; break;
							}
						}); //图标是漏下
						GtkWidget *box;
						switch(pos_) {
						case '<':
							if(!left1) {
								left1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
								gtk_header_bar_pack_start (hb, left1);
							}
							box = left1;
							break;
						case '>':
							if(!right1) {
								right1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
								gtk_header_bar_pack_end (hb, right1);
							}
							box = right1;
							break;
						}
						if(btn->name_[0] != '-')
							btn->code_ = code_;
						btn->with__(tag[1], GTK_BOX(box), p2, from2);
						break; }
					case 'h': h = std::stoi(p3[i]); break;
					}
				});

				if(from3 < p3.size()) {
					if(from3 != p3.size() - 1) {
						throw "未竟 " + std::to_string(i) + "-" + std::to_string(from3);
					}
					gtk_header_bar_set_decoration_layout(hb, p3[from3].c_str());
				} else
					gtk_header_bar_set_decoration_layout(hb, "");
				if(h != -1)
					gtk_widget_set_size_request(titlebar_, -1, h);
				gtk_widget_show(titlebar_);
				if(left1) gtk_widget_show_all(left1);
				if(right1) gtk_widget_show_all(right1);
				gtk_window_set_titlebar(hr2__(), titlebar_);
				break; }
			}
			break;
		case '(':
			switch(p[i][7]) {
			case '1':
				//取消关闭按钮
				gtk_window_set_deletable(hr2__(),FALSE);
				//取消最大化按钮
				gtk_window_set_resizable(hr2__(),FALSE);
				break;
			case '2':
				gdk_window_set_decorations(hr3__(),/*GDK_DECOR_ALL*/(GdkWMDecoration)0);
				break;
			case '3':
				break;
			case '4':
				break;
			}
			break;
		case 'C': {
			const std::string &s = p[i], &s2 = p[i + 1];
			/*if(!s.empty())
				gtk_window_set_role(hr2__(), s == "NULL" ? nullptr : s.c_str());
			if(!s2.empty())
				gtk_window_set_startup_id(hr2__(), s2 == "NULL" ? nullptr : s2.c_str());*/
			gtk_window_set_wmclass(hr2__(),
				s  == "NULL" ? nullptr : s.c_str(),
				s2 == "NULL" ? nullptr : s2.c_str());
			break; }
		case 'a': {
			gtk_widget_set_app_paintable(hr_, TRUE);
			GdkScreen *screen = gtk_widget_get_screen(hr_);
			GdkVisual *visual = gdk_screen_get_rgba_visual(screen);
			if (!visual)
				visual = gdk_screen_get_system_visual(screen);
			gtk_widget_set_visual(hr_, visual);
			break; }
		case 'e':
			switch(tag[1]) {
				case 'k': {
					event___* e = new event___(pub_, nullptr);
					e->conn__(hr__(), p[i - 1], p[i]);
					break; }
				case 's': window_state_event_ = p[i]; break;
				case 'm': state_xy_ = p[i]; break;
				case 'S': state_wh_ = p[i]; break;
			}
			break;
		case 'M': main_ = true; break;
		case 'n': {
			const std::string& name = p[i];
			if(pub_->find__(name)) {
				throw name + " 重名";
			}
			name__(name.c_str());
			break; }
		}
	});
	if(ret != 0) return ret;
	if(tuodong___::for__(p, from, this, this) != std::string::npos)
		return 1;
	return 0;
}

GtkWidget *window___::pack__(plugin::view___* view1, plugin::view___* by1, int posi) {
	view___* by = (view___*)by1->p_;

	view___* view = by->copy__(view1);
	window___* thiz = (window___*)by->window_;
	GtkWidget *box1 /*= by->box1_*/;
	GtkBox *box;
	label_box___ *label_box;
	label_box___ *lb = (label_box___ *)by->label_box_;
	new_page__(true, posi, true, true, lb->vert_, lb->top_align_, lb->bottom_align_, by->nb__(), box1, box, label_box);
	thiz->buju2_->pack__(thiz, view, box1, label_box, by->nb1_, 0, by, by->has_close_, true, true, by->expand_, by->padding_);
	thiz->code_->on_new__(nullptr, view, thiz->pub_);
	thiz->buju2_->pack_2__(thiz, view);
	return view1->hr__();
}

void window___::on_close__(view___* v, int c) {
	if(c & 1) {
		code_->on_del__(v, pub_);
		v->on_close__();
	}
	if(c & 16) {
		views_.del__(v);
	}
	if(c & (32 + 2)) {
		page_vs___ *vs2 = page_vs2__(v);
		if(vs2) {
			if(c & 2) {
				for(auto& v2 : *vs2) {
					if(v2 != v) {
						on_close__(v2, 32 + 16 + 8 + 1);
						v2->label_box_ = nullptr;
					}
				}
			}
			if(c & 32) {
				vs2->erase(std::find(vs2->begin(), vs2->end(), v));
			}
		}
	}
	if((c & 4) && v->label_box_) {
		delete (label_box___*)v->label_box_;
	}
	if(c & 8) {
		delete v;
	}
}
