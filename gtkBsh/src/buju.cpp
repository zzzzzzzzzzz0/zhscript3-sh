#include "xianchang.h"
#include "window.h"
#include "pub3.h"

buju___*buju__(view___*v) {return (buju___*)v->buju_;}
page_vs2___ page_vs2__(view___* v) {
    return (page_vs2___)((label_box___*)v->label_box_)->views_;
}

static void cb_close__(GtkButton *button, view___* v) {window___::close__(v, true);}
void buju2___::pack__(void* window, view___* view, GtkWidget *box1, label_box___ *label_box, GtkWidget *nb1, size_t id, view___* by,
        char can_close, bool can_close2, bool page_curr2, bool expand, int padding) {
    views_->a_.push_back(view);
    view->nb1_ = nb1;
    view->box1_ = box1;
    view->label_box_ = label_box;
    view->window_ = window;
    view->id_ = id;
    if(!view->id_) {
        static size_t id = 0;
        size_t id2 = time(nullptr);
        if(id < id2)
            id = id2;
        else
            ++id;
        view->id_ = id;
    }
    if(by) {
        view->upid_ = by->id_;
    }

    page_vs2___ views = page_vs2__(view);
    if(!views) {
        views = new page_vs___();
        ((label_box___*)view->label_box_)->views_ = views;
    }
    if(can_close) {
        if(++label_box->has_close_ == 1) {
            view->has_close_ = can_close;
            if(can_close2) {
                GtkBox *box;
                switch(can_close) {
                    case '^': box = label_box->top_; break;
                    case 'v': box = label_box->bottom_; break;
                    case '<': box = label_box->left_; break;
                    default: box = label_box->right2_; break;
                }
                button_new__(G_CALLBACK(cb_close__), view, box,
                    {"gtk-close", std::to_string(GTK_ICON_SIZE_MENU)}, 0, true);
            }
        }
    }
    views->push_back(view);

    view->expand_ = expand;
    view->padding_ = padding;
    if(view->p__())
        pack_box__(view);
    else
        gtk_widget_show_all (view->box1_);
    if(page_curr2) view->curr__();
}
void pack_box__(view___* view) {
    GtkBox* box = view->box__();
    switch(view->p__()->scroll__()) {
        case 1: {
        GtkWidget *box2_1;
        GtkBox* box2;
        box_new__(GTK_ORIENTATION_HORIZONTAL, box2_1, box2);
        gtk_box_set_homogeneous(box2, FALSE);
        gtk_box_pack_start(box2, view->hr__(), TRUE, TRUE, paddi3_);
        GtkWidget *sb = gtk_scrollbar_new(GTK_ORIENTATION_VERTICAL, gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(view->hr__())));
        gtk_box_pack_end(box2, sb, FALSE, FALSE, paddi3_);
        gtk_box_pack_start(box, box2_1, view->expand_, true, view->padding_);
        view->set_wh__();
        break; }

        case 2: {
        GtkWidget *sw1 = gtk_scrolled_window_new (NULL, NULL);
        GtkScrolledWindow *sw = GTK_SCROLLED_WINDOW(sw1);
        gtk_scrolled_window_set_policy (sw, GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
        gtk_container_add (GTK_CONTAINER(sw1), view->hr__());
        gtk_box_pack_start(box, sw1, view->expand_, true, view->padding_);
        view->set_wh__(sw1);
        break; }

        default:
        gtk_box_pack_start(box, view->hr__(), view->expand_, true, view->padding_);
        view->set_wh__();
        break;
    }
    gtk_widget_show_all (view->box1_);
}

class switch_page___ {
    public:
    window___* w; view___* v; GtkNotebook* nb; guint page_num;
};
static gboolean idle_switch_page__(gpointer p) {
    switch_page___* sp = (switch_page___*)p;
    sp->w->switch_page2__(sp->v, sp->nb, sp->page_num);
    delete sp;
    return G_SOURCE_REMOVE;
}
static void switch_page__ (GtkNotebook* self, GtkWidget* page, guint page_num, window___* w) {
    for(auto& v : w->views_.a_)
        if(v->box1_ == page) {
            if(v->hulve1qie_) {
                v->hulve1qie_ = false;
                continue;
            }
            if(v->lazy_) {
                v->lazy_ = false;
                g_idle_add(idle_switch_page__, new switch_page___{w, v, self, page_num});
            } else
                w->switch_page2__(v, self, page_num);
        }
}

void new_page__(bool vert, int posi, bool reord, bool padding2, bool vert2, GtkAlign top_align, GtkAlign bottom_align,
GtkNotebook *nb, GtkWidget *&box1, GtkBox *&box, label_box___ *&label_box) {
	box_new__(vert ? GTK_ORIENTATION_VERTICAL : GTK_ORIENTATION_HORIZONTAL, box1, box);

	label_box = new label_box___(padding2, vert2, top_align, bottom_align);
	gtk_widget_show_all (label_box->box1_);

	add__(nb, box1, label_box->box1_, posi, reord);
}

int buju2___::for__(void* window, GtkContainer* cntr_, GtkWidget *nb1_, view___*& view_, args___ p, size_t& from,
		bool no_new, bool nb1_need_new, bool is1, rust_add___ add, void* env) {
	if(is1 && !view_ && !views_->a_.empty())
		view_ = views_->a_[0];
	if(no_new && !nb1_) {
		if(view_)
			nb1_ = view_->nb1_;
		else if(notebooks_->size()) {
			nb1_ = (*notebooks_)[0];
		}
	}
	GtkNotebook *nb_ = GTK_NOTEBOOK(nb1_);
	auto new_nb1 = [&](bool b) {
		if(b) {
			nb1_ = gtk_notebook_new ();
			notebooks_->push_back(nb1_);
		}
		nb_ = GTK_NOTEBOOK(nb1_);
		gtk_notebook_set_scrollable (nb_, true);
		gtk_notebook_popup_enable (nb_);
		gtk_widget_set_can_focus(nb1_, false);
		g_signal_connect(nb_, "switch-page", G_CALLBACK(switch_page__), window);
	};
	buju___* buju_ = nullptr;
	if(view_)
		buju_ = buju__(view_);
	else if(nb1_)
		for(auto* i : *bujus_) {
			if(i->nb1_ == nb1_) {
				buju_ = i;
				break;
			}
		};
	auto new_buju = [&](GtkContainer* cntr) {
		buju_ = new buju___();
		bujus_->push_back(buju_);
		GtkWidget *box_tp1, *box_bm1, *box_lt1, *box_rt1;
		box_new__(GTK_ORIENTATION_VERTICAL, box_tp1, buju_->box_tp_);
		box_new__(GTK_ORIENTATION_VERTICAL, box_bm1, buju_->box_bm_);
		box_new__(GTK_ORIENTATION_HORIZONTAL, box_lt1, buju_->box_lt_);
		box_new__(GTK_ORIENTATION_HORIZONTAL, box_rt1, buju_->box_rt_);
		new_nb1(true);
		buju_->nb1_ = nb1_;
		gtk_box_pack_end(buju_->box_tp_, box_bm1, false, false, paddi2_);
		gtk_box_pack_end(buju_->box_tp_, box_lt1, true, true, paddi_);
		gtk_box_pack_end(buju_->box_lt_, box_rt1, false, false, paddi_);
		gtk_box_pack_end(buju_->box_lt_, nb1_, true, true, paddi2_);
		gtk_container_add(cntr ? cntr : cntr_, box_tp1);
		gtk_widget_show_all (cntr ? GTK_WIDGET(cntr) : box_tp1);
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
	view___* by_ = view_;

	bool has_ = false, no_lazy_ = !no_new;

	xianchang::list___ xianchang_;

	int ret2 = pub_->clpars__({
		{"-新开", "n", 4},
		{"-新页", "np", 4},
		{"-存", "Ds", 0},
		{"-复", "Dr", 0},
	}, p, from, [&](const std::string& tag, size_t i, size_t argc, int& fn2_ret2) {
		switch(tag[0]) {
			case 'n': {
				int w = -1, h = -1, posi = append_page_, has_then_break = 1;
				guint padding = paddi4_;
				char in_nb2 = 0, nb_pos = 0;
				std::string name, nb_name, kou_name;
				char can_close = '\0';
				bool vert = true, can_close2 = true, padding2 = false, vert2 = false,
					page_curr2 = false, curr2_lazy = false,
					no_lazy = false, no_focus = false, hulve1qie = false,
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
					{"-缓切", "Ti", 0},
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
					{"-忽略一切", "1", 0},
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
							case '0': padding = 0;
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
					case 'T':
						switch(tag[1]) {
							case 'i': curr2_lazy = true; break;
							default: no_lazy_ = true; break;
						}
						page_curr2 = true;
						break;
					case 'F': no_focus = true; break;
					case 'z': no_lazy_ = no_lazy = !tag[1]; break;
					case 'j':
						buju_ = nullptr;
						for(auto& v : views_->a_) {
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
						by_ = views_->find__([&](auto v) {return v->id_ == id;});
						break; }
					case '1': hulve1qie = true; break;
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
					for(auto& v : views_->a_) {
						const char* name2 = v->name__();
						if(name2 && name2 == name) {
							view_ = v;
							has_ = has = true;
							break;
						}
					}
				}
				if(id) {
					for(auto& v : views_->a_) {
						if(v->id_ == id) {
							view_ = v;
							has_ = has = true;
							break;
						}
					}
				}
				if(!nb_name.empty()) {
					for(auto& nb1 : *notebooks_) {
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
					} else if(in_nb2) {
						if(nb1_need_new) {
							new_nb1(true);
							gtk_widget_show_all (nb1_);
						}
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
						if(!kou_name.empty())
							gtk_widget_set_name(nb1_, kou_name.c_str());
						gtk_box_pack_start(box_, nb1_, true, true, padding);
						gtk_widget_show_all(box1_);
						new_page(vert, posi, reord, padding2, vert2, top_align, bottom_align);

						gtk_widget_show_all(box1_);
						code_->on_new__([&](vec___& args) {
							args.push_back("");
							args.push_back(kou_name);
						}, view_, pub_);
					}
					if(!nb_name.empty())
						gtk_widget_set_name(nb1_, nb_name.c_str());
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
					if(!no_lazy && !hulve1qie) {
						gint n = gtk_notebook_get_n_pages(nb_);
						if(n == 1)
							no_lazy = true;
					}
					view_ = new view___(pluginame, viewopt, viewopt2, name, w, h, no_focus);
					view_->buju_ = buju_;
					view_->kou_nb1_ = kou_nb1;
					view_->kou_box1_ = kou_box1;
					if(!no_focus && (page_curr2 | no_lazy))
						view_->need_focus_ = true;
					view_->lazy_ = curr2_lazy;
					view_->hulve1qie_ = hulve1qie;
					if((page_curr2 && !curr2_lazy) | no_lazy)
						view_->mk_p__([&](const std::string& s, const std::string& s1, const std::string& s2) {
							return pub_->new_view__(s, s1, s2);
						},  [&](args___ a, size_t& l) {
							return for2_2__(view_, a, l);
						}, [&](args___ a, size_t l) {
							return pub_->goodbye__(a, l);
						});
					pack__(window, view_, box1_, label_box_, nb1_, id,
						posi != 0 ? by_ : nullptr, can_close, can_close2, page_curr2,
						w == -1 && h == -1
						|| (in_nb2 == '<' || in_nb2 == '>') && h == -1
						|| (in_nb2 == '^' || in_nb2 == 'v') && w == -1, padding);
				}
				ret2 = for2__(window, view_, p2, from2, pub::clpars_throw_);
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
				if(!has && !pack_2__(window, view_))
					break;
				break; }
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
	});
	if(ret2 != 0) return ret2;
	if(view_) {
		ret2 = for2__(window, view_, p, from); if(ret2 != 0) return ret2;
		ret2 = view_->for__(p, from, add, env); if(ret2 != 0) return ret2;
	}
	return 0;
}

int buju2___::for2__(void* window, view___* view, args___ p, size_t& from, int fn2_ret2) {
	label_box___* label_box_ = (label_box___*)view->label_box_;
	bool b_ = true, b2_ = false;
	std::string code_;
	char pos_ = 0;
	int ret = pub_->clpars__({
		{"-签", "l", 1},
		{"-签前", "l2", 1},
		{"-签后", "l3", 1},
		{"-签副", "l4", 1},
		{"-签提示", "T", 1},
		{"-签前提示", "T2", 1},
		{"-签后提示", "T3", 1},
		{"-签副提示", "T4", 1},
		{"-加钮", "b+", 1},
		{"-追钮", "b++", 1},
		{"-加钮-", "b|", 0},
		{"-叠", "+", 1},
		{"-附", "a", 1},
		{"-按键", "ek", 1},
	}, p, from, [&](const std::string& tag, size_t i, size_t argc, int& ret2) {
		switch(tag[0]) {
		case 'l': case 'T': {
			GtkLabel* l;
			const std::string& s = p[i];
			switch(tag[1]) {
				case '2': l = label_box_->label2_; break;
				case '3': l = label_box_->label3_; break;
				case '4': l = label_box_->label4_; break;
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
					gtk_box_pack_start (box(), btn1, false, false, label_box_->vert_ ? 0 : 7);
					gtk_widget_show (btn1);
					break; }
				default: {
					vec___ p2;
					size_t from2 = 0;
					std::string name;
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
					if(from2 == p2.size())
						break;
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
		case 'a': view->attach_ = p[i]; break;
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
	plugin::view___* v1 = (plugin::view___*)view->p__();
	if(v1) {
		ret = for2_2__(view, p, from); if(ret != 0) return ret;
		if(tuodong___::for__(p, from, (window___*)window, v1) != std::string::npos)
			return 1;
	}
	return pub::clpars_ret_1__(fn2_ret2, p, from);
}
int buju2___::for2_2__(view___* view, args___ p, size_t& from) {
	return pub_->clpars__({
		{"-字体", "f", 1},
	}, p, from, [&](const std::string& tag, size_t i, size_t argc, int& ret2) {
		switch(tag[0]) {
		case 'f': {
			PangoFontDescription *font_desc = pango_font_description_from_string (p[i].c_str());
			gtk_widget_modify_font (view->hr__(), font_desc);
			pango_font_description_free (font_desc);
			break; }
		}
	});
}
