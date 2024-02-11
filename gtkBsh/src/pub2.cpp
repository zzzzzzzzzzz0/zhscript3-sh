#include "pub2.h"

void foreach__(const std::string& tag, args___ p, size_t i, rust_add___ add, void* env, bool& dunhao,
        view___* view, main_plugin___* mp) {
    char c = tag[1];
    const std::string& s = p[i + (c >= '0' ? 0 : 1)];
    auto fn = [&](auto& v) {
        vec___ args, ret;
        mp->std__(v, args);
        if(v->is_curr__())
            args.push_back("1");
        int ret2 = mp->fanqiechaodan2__(v, s, args, &ret, env);
        for(auto& i : ret) {
            switch(c) {
                case 'e': case ' ':
                mp->add__(i.c_str(), dunhao, add, env);
                break;
                default:
                add(i.c_str(), false, env);
                break;
            }
        }
        return ret2;
    };
    switch(c) {
        case '2': case 'e': case '4':
        for(auto& w : mp->windows_)
            for(auto& v : w->views_.a_) {
                if(v == view && c == '4')
                    continue;
                switch(fn(v)) {
                    case l4___::eval_break_:
                        goto b_f;
                }
            }
        break;
        default:
        for(auto& w : mp->windows_) {
            for(auto& nb1 : w->notebooks_) {
                if(p[i] == gtk_widget_get_name(nb1)) {
                    GtkNotebook *nb = GTK_NOTEBOOK(nb1);
                    for(int i2 = 0; i2 < gtk_notebook_get_n_pages(nb); i2++) {
                        for(auto& v : w->views_.a_) {
                            if(gtk_notebook_get_nth_page(nb, i2) == v->box1_) {
                                switch(fn(v)) {
                                    case l4___::eval_break_:
                                        goto b_f;
                                }
                            }
                        }
                    }
                    break;
                }
            }
        }
        break;
    }
    b_f:;
}

static void grp_move__(size_t id, int& i2, GtkNotebook *nb, const std::vector<GtkWidget*>& a, window___* wi, bool shangtuo) {
    for(int i3 = 0; i3 < a.size(); i3++) {
        GtkWidget* box1 = a[i3];
        for(auto& v : wi->views_.a_) {
            if(v->box1_ == box1) {
                if(v->upid_ == id) {
                    if(shangtuo) {
                        ++i2;
                    }
                    gtk_notebook_reorder_child(nb, box1, i2);
                    grp_move__(v->id_, i2, nb, a, wi, shangtuo);
                }
            }
        }
    }
}
void move__(view___* view, const std::string& s2, char grp, size_t gid, char op) {
	size_t id = view->id_;
	int i1 = view->page_num__();
	GtkNotebook *nb = view->nb__();
	window___* wi = (window___*)view->window_;
    int i2;
	if(grp) {
        size_t id2 = std::stoul(s2);
        i2 = gid; //-1
        for(auto& v : wi->views_.a_) {
            if(v->nb1_ == view->nb1_ && v->id_ == id2) {
                i2 = v->page_num__();
                break;
            }
        }
    } else {
        i2 = s2.empty() ? -1 : std::stoi(s2);
    }

	bool shangtuo = i2 >= 0 && i2 < i1;
	if(grp) {
        if(shangtuo)
            switch(op) {
                case 'p':
                case 'n':
                break;

                default:
                i2++;
                break;
            }
        else
            switch(op) {
                case 'p':
                case 'n':
                i2--;
                break;
            };
        switch(op) {
            case 'p':
            if(i2 < 0)
                i2 = 0;
            break;
        }
    }
    std::vector<GtkWidget*> a;
	if(grp) {
        for(int i3 = 0; i3 < gtk_notebook_get_n_pages(nb); i3++)
            a.push_back(gtk_notebook_get_nth_page(nb, i3));

		view->upid_ = gid;
    }
	gtk_notebook_reorder_child(nb, view->box1_, i2);
	if(grp) {
		grp_move__(id, i2, nb, a, wi, shangtuo);
	}
}
