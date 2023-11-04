#include "pub2.h"
#include "xianchang.h"
#include "event.h"
#include "window.h"

/*
	if(l4_.dbg_bp2_("-o-")) {
	}
*/
#ifdef _debug_
void _1__(const char* c1, GtkWidget *b) {
	GdkColor c;
	gdk_color_parse (c1, &c);
	gtk_widget_modify_bg (b, GTK_STATE_NORMAL, &c);
}
void _2__(GtkBox *b) {
	guint padd = 20;
	gtk_box_set_spacing(b, padd);
}
void _4__(window___::buju___* buju_) {
	GtkWidget *box_tp1, *box_bm1, *box_lt1, *box_rt1;
	box_tp1=GTK_WIDGET(buju_->box_tp_);
	box_bm1=GTK_WIDGET(buju_->box_bm_);
	box_lt1=GTK_WIDGET(buju_->box_lt_);
	box_rt1=GTK_WIDGET(buju_->box_rt_);
	const char *c1, *c2, *c3, *c4;
	static int _4_i_ = 0;
	switch(_4_i_++ % 4) {
		case 0:
		c1 = "#00f";
		c2 = "#0f0";
		c3 = "#ff0";
		c4 = "#0ff";
		break;
		case 1:
		c1 = "#009";
		c2 = "#090";
		c3 = "#990";
		c4 = "#099";
		break;
		case 2:
		c1 = "#006";
		c2 = "#060";
		c3 = "#660";
		c4 = "#066";
		break;
		default:
		c1 = "#00c";
		c2 = "#0c0";
		c3 = "#cc0";
		c4 = "#0cc";
		break;
	}
	printf("_4_i_%d %s %s %s %s\n", _4_i_, c1, c2, c3, c4);
	_1__(c1, box_tp1);
	_1__(c2, box_bm1);
	_1__(c3, box_lt1);
	_1__(c4, box_rt1);
	_2__(buju_->box_tp_);
	_2__(buju_->box_tp_);
	_2__(buju_->box_lt_);
	_2__(buju_->box_lt_);
}
#endif

class event___ : public pub::event___ {
	gboolean jieshi__(const std::vector<std::string>* p, gboolean ret1) {
		vec___ arg, ret;
		if(p)
			arg = *p; //arg.assign(p->begin(), p->end())
		pub_->fanqiechaodan2__(v_, code_, arg, &ret);
		if(ret.size() == 1) {
			if(ret[0] == "1") return TRUE;
			if(ret[0] == "0") return FALSE;
		}
		if(!ret.empty())
			pub_->goodbye__(ret, 0);
		return ret1;
	}
	main_plugin___* pub_ = nullptr;
	plugin::view___* v_ = nullptr;
	public:
	event___(main_plugin___* pub, plugin::view___* v) : pub_(pub), v_(v) {}
};
class tuodong___ : public pub::tuodong___ {
	GtkWindow* hr2__() {return w_->hr2__();}
	GdkWindow *hr3__() {return w_->hr3__();}
	window___* w_ = nullptr;
	public:
	tuodong___(window___* w) : w_(w) {}

    static size_t for__(const std::vector<std::string>& args, size_t& from, window___* w, widget___* p) {
        const char* ss[] = {"-鼠标拖动", "-鼠标拖动-停", "-鼠标拖动-启", "-鼠标拖动-切停"};
        size_t ret = std::string::npos;
        for(size_t i2 = from; i2 < args.size(); i2++) {
			auto& s = args[i2];
			if(s.empty()) continue;
			bool b = true;
            for(size_t i = 0; i <= 3; i++) {
                if(s == ss[i]) {
                    switch(i) {
                        case 0:
						if(!p->tuodong_) {
							tuodong___* td = new tuodong___(w);
							td->conn__(p->hr__());
							p->tuodong_ = td;
						}
                        break;
						default:
						if(p->tuodong_) {
							tuodong___* td = (tuodong___*)p->tuodong_;
							td->pause_ = i == 3 ? !td->pause_ : i == 2;
						} else
							return ret;
						break;
                    }
					from = i2;
                    ret = i;
					b = false;
					break;
                }
            }
			if(b) break;
        }
        return ret;
    }
};

void new_page__(bool vert, int posi, bool reord, bool padding2, bool vert2, GtkAlign top_align, GtkAlign bottom_align,
GtkNotebook *nb, GtkWidget *&box1, GtkBox *&box, label_box___ *&label_box) {
	box_new__(vert ? GTK_ORIENTATION_VERTICAL : GTK_ORIENTATION_HORIZONTAL, box1, box);

	label_box = new label_box___(padding2, vert2, top_align, bottom_align);
	gtk_widget_show_all (label_box->box1_);

	add__(nb, box1, label_box->box1_, posi, reord);
}

int window___::for__(GtkWidget *nb1_, plugin::view___*& view_, args___ p, size_t& from,
		new_view___ new_view, bool no_new, bool nb1_need_new, bool is1, rust_add___ add, void* env) {
	if(is1 && !view_ && !views_.a_.empty())
		view_ = views_.a_[0];
	if(no_new && !nb1_ && view_)
		nb1_ = view_->nb1_;
	GtkNotebook *nb_ = GTK_NOTEBOOK(nb1_);
	auto new_nb1 = [&](bool b) {
		if(b)
			nb1_ = gtk_notebook_new ();
		nb_ = GTK_NOTEBOOK(nb1_);
		gtk_notebook_set_scrollable (nb_, true);
		gtk_notebook_popup_enable (nb_);
		gtk_widget_set_can_focus(nb1_, false);
		g_signal_connect(nb_, "switch-page", G_CALLBACK(switch_page__), this);
	};
	buju___* buju_ = view_ ? buju__(view_) : nullptr;
	auto new_buju = [&](GtkContainer* cntr) {
		buju_ = new buju___();
		bujus_.push_back(buju_);
		GtkWidget *box_tp1, *box_bm1, *box_lt1, *box_rt1;
		box_new__(GTK_ORIENTATION_VERTICAL, box_tp1, buju_->box_tp_);
		box_new__(GTK_ORIENTATION_VERTICAL, box_bm1, buju_->box_bm_);
		box_new__(GTK_ORIENTATION_HORIZONTAL, box_lt1, buju_->box_lt_);
		box_new__(GTK_ORIENTATION_HORIZONTAL, box_rt1, buju_->box_rt_);
		new_nb1(true);
		gtk_box_pack_end(buju_->box_tp_, box_bm1, false, false, paddi2_);
		gtk_box_pack_end(buju_->box_tp_, box_lt1, true, true, paddi_);
		gtk_box_pack_end(buju_->box_lt_, box_rt1, false, false, paddi_);
		gtk_box_pack_end(buju_->box_lt_, nb1_, true, true, paddi2_);
		gtk_container_add(cntr ? cntr : to_cntr__(), box_tp1);
	};
	GtkWidget *box1_ = nullptr;
	GtkBox *box_ = nullptr;
	label_box___ *label_box_ = nullptr;
	if(no_new && view_) {
		box1_ = view_->box1_;
		box_ = view_->box__();
		label_box_ = (label_box___*)view_->label_box_;
	}
	auto new_page = [&](bool vert, int posi, bool reord, bool padding2, bool vert2, GtkAlign top_align, GtkAlign bottom_align) {
		new_page__(vert, posi, reord, padding2, vert2, top_align, bottom_align, nb_, box1_, box_, label_box_);
	};
	plugin::view___* by_ = view_;

	bool has_ = false, no_lazy_ = !no_new;

	xianchang::list___ xianchang_;

	int ret2 = pub_->clpars__({
		{"-新开", "n", 4},
		{"-新页", "np", 4},
	}, p, from, [&](const std::string& tag, size_t i, size_t argc, int& fn2_ret2) {
		switch(tag[0]) {
			case 'n': {
				int w = -1, h = -1, posi = append_page_, has_then_break = 1;
				guint padding = paddi4_;
				char in_nb2 = 0, nb_pos = 0;
				std::string name, nb_name, kou_name, attach;
				char can_close = '\0';
				bool vert = true, can_close2 = true, padding2 = false, vert2 = false, page_curr2 = false,
					no_lazy = false, no_focus = false,
					in_new_buju = false, in_new_page = false, in_new_kou = false, reord = true;
				switch(tag[1]) {
					case 'p':
					in_new_page = true;
					no_lazy_ = false;
					break;
					default:
					if(no_lazy_)
						no_lazy = true;
					break;
				}
				size_t id = 0;
				GtkWidget *kou_nb1 = nullptr, *kou_box1 = nullptr;
				GtkAlign top_align = GTK_ALIGN_START, bottom_align = GTK_ALIGN_START;
				vec___ p2;
				pub_->eval__(p[i + 3].c_str(), &p2);
				size_t from2 = 0;
				pub::tags___ tags2 = {
					{"-宽", "w", 1},
					{"-高", "h", 1},
					{"-隔", "a", 1},
					{"-横", "-", 0},
					//{"-竖", "-1", 0},
					{"-前固", "L", 0},
					{"-之前", "Lb", 0},
					{"-之后", "La", 0},
					{"-位置", "L-", 1},
					{"-可关闭", "x1", 0},
					{"-可关闭-顶", "x^", 0},
					{"-可关闭-底", "xv", 0},
					{"-可关闭-左", "x<", 0},
					{"-不可关闭", "X", 0},
					{"-不动", "r", 0},
					{"-顶", "P^", 0},
					{"-底", "Pv", 0},
					{"-左", "P<", 0},
					{"-右", "P>", 0},
					{"-顶签", "Nt", 0},
					{"-底签", "Nb", 0},
					{"-左签", "Nl", 0},
					{"-右签", "Nr", 0},
					{"-无签", "N0", 0},
					{"-竖签", "N|", 0},
					{"-顶钮居中", "B^.", 0},
					{"-顶钮居右", "B^>", 0},
					{"-底钮居中", "Bv.", 0},
					{"-底钮居右", "Bv>", 0},
					{"-名", "n", 1},
					{"-簿名", "nb", 1},
					{"-新局", "#u", 0},
					{"-新页", "#p", 0},
					{"-新区", "#o", 1},
					{"-切", "T", 0},
					{"-无焦", "F", 0},
					{"-页", "j", 1},
					{"-替", "H", 0},
					{"-略旧", "Hn", 0},
					{"-直", "z", 0},
					{"-开", "z", 0},
					{"-不懒", "z", 0},
					{"-懒", "z ", 0},
					{"-id", "i", 1},
					{"-上id", "I", 1},
					{"-附", "+", 1},
					{"-存", "Ds", 0},
					{"-复", "Dr", 0},
				};
				ret2 = pub_->clpars1__(tags2, p2, from2, [&](const std::string& tag, size_t i, size_t argc, int& fn2_ret2) {
					switch(tag[0]) {
					case 'w': w = std::stoi(p2[i]); break;
					case 'h': h = std::stoi(p2[i]); break;
					case 'a': padding = std::stoi(p2[i]); break;
					case '-': vert = tag[1]; break;
					case 'L':
						switch(tag[1]) {
							case 'a': posi = after_curr_page_; break;
							case 'b': posi = before_curr_page_; break;
							case '-': posi = std::stoi(p2[i]); break;
							default:  posi = 0; break;
						}
						break;
					case 'x':
						can_close = tag[1];
						switch(can_close) {
							case '^': case 'v': break;
							default: padding2 = true; break;
						}
						break;
					case 'X': can_close2 = false; break;
					case 'r': reord = false; break;
					case 'P':
						in_nb2 = tag[1]; break;
					case 'N':
						switch(tag[1]) {
							case '|': vert2 = true; break;
							default: nb_pos = tag[1]; break;
						}
						break;
					case 'B': {
						GtkAlign *a;
						switch(tag[1]) {
							case '^': a = &top_align; break;
							case 'v': a = &bottom_align; break;
						}
						switch(tag[2]) {
							case '.': *a = GTK_ALIGN_CENTER; break;
							case '>': *a = GTK_ALIGN_END; break;
						}
						break; }
					case 'n':
						switch(tag[1]) {
							case 'b': nb_name = p2[i]; break;
							default: name = p2[i]; break;
						}
						break;
					case '#':
						switch(tag[1]) {
							case 'u': in_new_buju = true; break;
							case 'p': in_new_page = true; break;
							case 'o':
								in_new_kou = true;
								kou_name = p2[i];
								break;
						}
						break;
					case 'T': page_curr2 = no_lazy_ = true; break;
					case 'F': no_focus = true; break;
					case 'z': no_lazy_ = no_lazy = !tag[1]; break;
					case 'j':
						buju_ = nullptr;
						for(auto& v : views_.a_) {
							if(v->name__() == p2[i]) {
								buju_ = buju__(v);
								break;
							}
						}
						if(!buju_)
							throw "页无觅 " + p2[i];
						break;
					case 'H': has_then_break = tag[1]; break;
					case 'i': id = std::stoul(p2[i]); break;
					case 'I': {
						size_t id = std::stoul(p2[i]);
						by_ = views_.find__([&](auto v) {return v->id_ == id;});
						break; }
					case '+': attach = p2[i]; break;
					case 'D':
						switch(tag[1]) {
							case 's':
							xianchang_.push__(new xianchang::item___{nb1_, nb_, view_, by_});
							break;
							case 'r':
							xianchang_.pop__(nb1_, nb_, view_, by_);
							break;
						}
						break;
					}
				}, []() {return pub::clpars_ret_no_;});
				if(ret2 < 0) {
					fn2_ret2 = pub::clpars_ret_;
					return;
				}
				if(has_ && has_then_break == 1) {
					if(in_new_page)
						has_ = false;
					else
						break;
				}
				bool has = false;
				if(!name.empty()) {
					for(auto& v : views_.a_) {
						const char* name2 = v->name__();
						if(name2 && name2 == name) {
							view_ = v;
							has_ = has = true;
							break;
						}
					}
				}
				if(id) {
					for(auto& v : views_.a_) {
						if(v->id_ == id) {
							view_ = v;
							has_ = has = true;
							break;
						}
					}
				}
				if(!nb_name.empty()) {
					for(auto& nb1 : notebooks_) {
						if(nb_name == gtk_widget_get_name(nb1)) {
							nb_ = GTK_NOTEBOOK(nb1_ = nb1);
							break;
						}
					}
				}
				if(by_ && by_->nb1_ == nb1_ && (posi == after_curr_page_)) {
					posi = by_->page_num__() + 1;
				}
				const std::string& pluginame = p[i];
				if(!has) {
					if(!nb_)
						new_buju(nullptr);
					if(in_new_buju) {
						GtkBox* b;
						switch(in_nb2) {
							case '>': b = buju_->box_rt_; break;
							case '^': b = buju_->box_tp_; break;
							case 'v': b = buju_->box_bm_; break;
							default:  b = buju_->box_lt_; break;
						}
						GtkContainer* cntr = GTK_CONTAINER(b);
						new_buju(cntr);
						//gtk_widget_show_all(box1_);
					} else if(in_nb2) {
						if(nb1_need_new)
							new_nb1(true);
						switch(in_nb2) {
							case '<': gtk_box_pack_start(buju_->box_lt_, nb1_, false, false, padding); break;
							case '>': gtk_box_pack_start(buju_->box_rt_, nb1_, false, false, padding); break;
							case '^': gtk_box_pack_end(buju_->box_tp_, nb1_, false, false, padding); break;
							case 'v': gtk_box_pack_start(buju_->box_bm_, nb1_, false, false, padding); break;
						}
					}
					if((!box_ || in_nb2 || in_new_page) && !pluginame.empty())
						new_page(vert, posi, reord, padding2, vert2, top_align, bottom_align);
					if(in_new_kou) {
						gtk_widget_show_all(box1_);
						if(page_curr2)
							curr__(nb_, box1_);
						kou_nb1 = nb1_;
						kou_box1 = box1_;
						
						new_nb1(true);
						if(!kou_name.empty()) {
							gtk_widget_set_name(nb1_, kou_name.c_str());
							notebooks_.push_back(nb1_);
						}
						gtk_box_pack_start(box_, nb1_, true, true, padding);
						gtk_widget_show_all(box1_);
						new_page(vert, posi, reord, padding2, vert2, top_align, bottom_align);

						gtk_widget_show_all(box1_);
						code_->on_new__([&](vec___& args) {
							args.push_back("");
							args.push_back(kou_name);
						}, view_, pub_);
					}
					if(!nb_name.empty()) {
						gtk_widget_set_name(nb1_, nb_name.c_str());
						notebooks_.push_back(nb1_);
					}
					switch(nb_pos) {
						case 'l': gtk_notebook_set_tab_pos (nb_, GTK_POS_LEFT); break;
						case 'r': gtk_notebook_set_tab_pos (nb_, GTK_POS_RIGHT); break;
						case 'b': gtk_notebook_set_tab_pos (nb_, GTK_POS_BOTTOM); break;
						case 't': gtk_notebook_set_tab_pos (nb_, GTK_POS_TOP); break;
						case '0': show_tabs__(nb_, false); break;
					}
				}
				const std::string &viewopt = p[i + 1], &viewopt2 = p[i + 2];
				if(has) {
					if(page_curr2) {
						view_->curr__();
					}
					if(has_then_break) {
						//view_ = nullptr;
						switch(has_then_break) {
							case 'n': from = p.size(); break;
						}
					} else {
						view_->open__(viewopt, viewopt2);
					}
				} else {
					if(pluginame.empty())
						break;
					view_ = new_view(pluginame, viewopt, viewopt2, page_curr2 | no_lazy);
					view_->var__("buju_", buju_);
					if(w != -1 || h != -1) {
						gtk_widget_set_size_request (view_->hr__(), w, h);
					}
					if(!name.empty()) {
						view_->name__(name.c_str());
					}
					view_->kou_nb1_ = kou_nb1;
					view_->kou_box1_ = kou_box1;
					view_->attach_ = attach;
					if(!no_focus && (page_curr2 | no_lazy))
						view_->need_focus_ = true;
					pack__(view_, box1_, label_box_, nb1_, id,
						posi != 0 ? by_ : nullptr, can_close, can_close2, page_curr2,
						w == -1 && h == -1 || in_nb2, padding);
					if(no_focus)
						gtk_widget_set_can_focus(view_->hr__(), false);
				}
				ret2 = for2__(view_, p2, from2, pub::clpars_throw_);
				if(ret2 < 0) {
					vec___ p3;
					pub_->clpars_pr__(tags2, p3, "");
					break;
				}
				code_->on_new__([&](vec___& args) {
					args.push_back(std::to_string(view_->id_));
					args.push_back(name);
					if(has)
						args.push_back("1");
				}, view_, pub_);
				if(!has && !pack_2__(view_))
					break;
				break; }
		}
	});
	if(ret2 != 0) return ret2;
	if(view_) {
		ret2 = for2__(view_, p, from); if(ret2 != 0) return ret2;
		ret2 = view_->for__(p, from, add, env); if(ret2 != 0) return ret2;
	}
	return 0;
}

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
		{"-置顶", "T1", 0},
		{"-撤置顶", "T", 0},
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
		{"-激活", "P", 0},
		{"-撤全屏", "F", 0},
		{"-得移动", "=m", 0},
		{"-得宽高", "=s", 0},
		{"-是最大化", "=a", 0},
		{"-是激活", "=A", 0},
		{"-是全屏", "=f", 0},
		{"-图标", "i", 1},
		{"-无修饰", "!d", 0},
		{"-有修饰", "!d1", 0},
		{"-有无修饰", "!d@", 0},
		{"-切换修饰", "!d@", 0},
		{"-修饰1", "(", 0},
		{"-修饰2", "(", 0},
		{"-修饰3", "(", 0},
		{"-修饰4", "(", 0},
		{"-类名", "C", 2},
		{"-自绘", "a", 0},
		{"-按键", "ek", 1},
		{"-状态", "es", 1},
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
		case 't': gtk_window_set_title (hr2__(), p[i].c_str()); break;
		case 'T': gtk_window_set_keep_above (hr2__(), tag[1]); break;
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
		case 'P': gtk_window_present(hr2__()); break;
		case '=':
			switch(tag[1]) {
				case 'm': {
					int x, y;
					gtk_window_get_position(hr2__(), &x, &y);
					add_i2(x, y);
					break; }
				case 's': {
					int w2, h;
					gtk_window_get_size(hr2__(), &w2, &h);
					add_i2(w2, h);
					break; }
				case 'a': add_i(gtk_window_is_maximized(hr2__())); break;
				case 'A': add_i(gtk_window_is_active(hr2__())); break;
				case 'f': {
					int sw, sh, w, h;
					scrn_w_h__(sw, sh);
					gtk_window_get_size(hr2__(), &w, &h);
					add_i(w >= sw && h >= sh);
					break; }
				default:  break;
			}
			break;
		case 'i': {
			vec___ p2;
			pub_->eval__(p[i].c_str(), &p2);
			if(p2.size() > 0) {
				GdkPixbuf* pb = pixbuf__(p2, 0);
				gtk_window_set_icon_name(hr2__(), p2[0].c_str());
				gtk_window_set_icon(hr2__(), pb);
			}
			break; }
		case '!':
			switch(tag[1]) {
			case 'd':
				gtk_window_set_decorated(hr2__(), tag[2] == '@' ? !(gtk_window_get_decorated(hr2__())) : tag[2]);
				break;
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
				gtk_window_set_deletable(hr2__(),FALSE);
				break;
			case '4':
				gtk_window_set_resizable(hr2__(),FALSE);
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
				case 's': {
					bool ins = window_state_event_.empty();
					window_state_event_ = p[i];
					if(ins)
						g_signal_connect(hr_, "window-state-event", G_CALLBACK(window_state_event__), this);
					break; }
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

int window___::for2__(plugin::view___* view, args___ p, size_t& from, int fn2_ret2) {
	label_box___* label_box_ = (label_box___*)view->label_box_;
	bool b_ = true, b2_ = false;
	std::string code_;
	char pos_ = 0;
	int ret = pub_->clpars__({
		{"-签", "l", 1},
		{"-签前", "l2", 1},
		{"-签后", "l3", 1},
		{"-签提示", "T", 1},
		{"-签前提示", "T2", 1},
		{"-签后提示", "T3", 1},
		{"-加钮", "b+", 1},
		{"-追钮", "b++", 1},
		{"-加钮-", "b|", 0},
		{"-叠", "+", 1},
		{"-字体", "f", 1},
		{"-按键", "ek", 1},
	}, p, from, [&](const std::string& tag, size_t i, size_t argc, int& ret2) {
		switch(tag[0]) {
		case 'l': case 'T': {
			GtkLabel* l;
			const std::string& s = p[i];
			switch(tag[1]) {
				case '2': l = label_box_->label2_; break;
				case '3': l = label_box_->label3_; break;
				default:  l = label_box_->label_; break;
			}
			if(!tag[1]) {
				GtkWidget *w = gtk_notebook_get_menu_label (view->nb__(), view->box1_);
				if(!w) {
					w = gtk_label_new (nullptr);
					//gtk_widget_set_halign (w, GTK_ALIGN_START);
					gtk_notebook_set_menu_label (view->nb__(), view->box1_, w);
				}
				gtk_label_set_markup(GTK_LABEL(w), s.c_str());
			}
			switch(tag[0]) {
				case 'T':
				gtk_widget_set_tooltip_markup(GTK_WIDGET(l), s.c_str());
				break;
				default:
				gtk_label_set_markup(l, s.c_str());
				break;
			}
			break; }
		case 'b': {
			if(b_) {
				b_ = false;
				b2_ = !label_box_->buttons_.empty();
			}
			if(b2_ && tag[2] != '+')
				break;
			auto box = [&]() -> GtkBox * {
				switch(pos_) {
					case '^': return label_box_->top_;
					case 'v': return label_box_->bottom_;
					case '<': return label_box_->left_;
				}
				return label_box_->right_;
			};
			switch(tag[1]) {
				case '|': {
					GtkWidget *btn1=gtk_separator_new(label_box_->vert_ ?
						GTK_ORIENTATION_HORIZONTAL : GTK_ORIENTATION_VERTICAL);
					gtk_box_pack_start (box(), btn1, false, false, 7);
					gtk_widget_show (btn1);
					break; }
				default: {
					vec___ p2;
					size_t from2 = 0;
					std::string name;
					switch(tag[1]) {
					case '+': {
						pub_->eval__(p[i].c_str(), &p2);
						pub_->clpars__({
							{"-顶", "P^", 0},
							{"-底", "Pv", 0},
							{"-左", "P<", 0},
							{"-右", "P>", 0},
							{"-代码", "c", 1},
							{"-名", "n", 1},
						}, p2, from2, [&](const std::string& tag, size_t i, size_t argc, int& fn2_ret2) {
							switch(tag[0]) {
							case 'P': pos_ = tag[1]; break;
							case 'c': code_ = p2[i]; break;
							case 'n': name = p2[i]; break;
							}
						}); //图标是漏下
						if(!name.empty()) {
							bool has = false;
							for(auto i : label_box_->buttons_) {
								if(i->name_ == name) {
									has = true;
									break;
								}
							}
							if(has) break;
						}
						break; }
					}
					button___* btn = new button___(view, pub_);
					label_box_->buttons_.push_back(btn);
					btn->name_ = name;
					if(name[0] != '-')
						btn->code_ = code_;
					btn->with__(box(), p2, from2);
					break; }
			}
			break; }
		case '+':
			view->is_die_ = l4_.true_(p[i].c_str());
			break;
		case 'f': {
			PangoFontDescription *font_desc = pango_font_description_from_string (p[i].c_str());
			gtk_widget_modify_font (view->hr__(), font_desc);
			pango_font_description_free (font_desc);
			break; }
		case 'e':
			switch(tag[1]) {
				case 'k': {
					event___* e = new event___(pub_, view);
					e->conn__(view->hr__(), p[i - 1], p[i]);
					break; }
			}
			break;
		}
	});
	if(ret != 0) return ret; 
	if(tuodong___::for__(p, from, this, view) != std::string::npos)
		return 1;
	return pub::clpars_ret_1__(fn2_ret2, p, from);
}

GtkWidget *window___::pack__(plugin::view___* view, plugin::view___* by, int posi) {
	window___* thiz = (window___*)by->window_;
	GtkWidget *box1 /*= by->box1_*/;
	GtkBox *box;
	label_box___ *label_box;
	label_box___ *lb = (label_box___ *)by->label_box_;
	new_page__(true, posi, true, true, lb->vert_, lb->top_align_, lb->bottom_align_, by->nb__(), box1, box, label_box);
	thiz->pack__(view, box1, label_box, by->nb1_, 0, by, by->has_close_, true, true, true, 0);
	thiz->code_->on_new__(nullptr, view, thiz->pub_);
	thiz->pack_2__(view);
	return view->hr__();
}

void window___::on_close__(plugin::view___* v, int c) {
#ifdef _debug_
	printf("on_close__%p,%06b\n", v,c);
	printf("          %s %lu\n", v->plugin_id__(),v->id_);
#endif
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
