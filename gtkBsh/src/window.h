#pragma once
#include "main_plugin.h"
#include "pub.h"
#include "label_box.h"
#include "views.h"

class window___ : public widget___ {
    private:
	code___* code_;
	bool main_ = false;

	static void cb_close__(GtkButton *button, view___* v) {close__(v, true);}
	void on_close__(view___* v, int c);

	void pack__(view___* view, GtkWidget *box1, label_box___ *label_box, GtkWidget *nb1, size_t id, view___* by,
			char can_close, bool can_close2, bool page_curr2, bool expand, int padding) {
		views_.a_.push_back(view);
		view->nb1_ = nb1;
		view->box1_ = box1;
		view->label_box_ = label_box;
		view->window_ = this;
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
			/*view->kou_nb1_ = by->kou_nb1_;
			view->kou_box1_ = by->kou_box1_;*/
		}

		page_vs2___ views = page_vs2__(view);
		if(!views) {
			views = new page_vs___();
			view->views_ = views;
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
			break; }

			case 2: {
			GtkWidget *sw1 = gtk_scrolled_window_new (NULL, NULL);
			GtkScrolledWindow *sw = GTK_SCROLLED_WINDOW(sw1);
			gtk_scrolled_window_set_policy (sw, GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
			gtk_container_add (GTK_CONTAINER(sw1), view->hr__());
			gtk_box_pack_start(box, sw1, view->expand_, true, view->padding_);
			break; }

			default:
			gtk_box_pack_start(box, view->hr__(), view->expand_, true, view->padding_);
			break;
		}
		gtk_widget_show_all (view->box1_);
	}
	bool pack_2__(view___* view) {
		vec___ p3;
		{
			vec___ args = {"初始"};
			pub_->std__(view, args);
			pub_->main_eval__(args, &p3);
		}
		size_t from3 = 0;
		int ret2 = for2__(view, p3, from3);
		if(ret2 != 0)
			return false;
		ret2 = view->for__(p3, from3, nullptr, nullptr);
		if(ret2 != 0)
			return false;
		view->args1_.insert(view->args1_.end(), 
			std::make_move_iterator(p3.begin() + from3),
			std::make_move_iterator(p3.end()));
		return true;
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
	void switch_page2__ (view___* v, GtkNotebook* nb, guint page_num) {
		if(!v->p__()) {
			v->mk_p__([&](const std::string& s, const std::string& s1, const std::string& s2) {
				return pub_->new_view__(s, s1, s2);
			});
			pack_box__(v);
		}
		v->okopen__();

		std::string bname;
		pub_->name__(nb, bname);
		vec___ args = {"切换", std::to_string(page_num), bname};
		pub_->fanqiechaodan3__(v, args);
	}
	static void switch_page__ (GtkNotebook* self, GtkWidget* page, guint page_num, window___* w) {
		for(auto& v : w->views_.a_)
			if(v->box1_ == page) {
				if(v->hulve1qie_) {
					v->hulve1qie_ = false;
					continue;
				}
				if(v->lazy_) {
					g_idle_add(idle_switch_page__, new switch_page___{w, v, self, page_num});
				} else
					w->switch_page2__(v, self, page_num);
			}
	}

	static gboolean delete_event__(GtkWidget *widget, GdkEvent *event, window___* thiz) {
		vec___ args = {"窗将关", thiz->name__()}, ret;
		thiz->pub_->fanqiechaodan3__(nullptr, args, &ret);
		return bool__(ret);
	}

	std::string window_state_event_;
	static gboolean window_state_event__(GtkWidget *widget, GdkEventWindowState *event, window___* thiz) {
		vec___ args;
		auto fn = [&](GdkWindowState ws) {
			std::string s;
			if((ws & GDK_WINDOW_STATE_ICONIFIED))
				s += "最小化";
			if((ws & GDK_WINDOW_STATE_MAXIMIZED))
				s += "最大化";
			if((ws & GDK_WINDOW_STATE_STICKY))
				s += "总可见";
			if((ws & GDK_WINDOW_STATE_FULLSCREEN))
				s += "全屏";
			if((ws & GDK_WINDOW_STATE_ABOVE))
				s += "置顶";
			if((ws & GDK_WINDOW_STATE_BELOW))
				s += "置底";
			if((ws & GDK_WINDOW_STATE_FOCUSED))
				s += "焦点";
			args.push_back(s);
			//args.push_back(std::to_string(ws));
		};
		fn(event->new_window_state);
		fn(event->changed_mask);
		thiz->pub_->fanqiechaodan2__(nullptr, thiz->window_state_event_, args);
		return false;
	}

	public:
	views___ views_;
	std::vector<GtkWidget*> notebooks_;
	main_plugin___* pub_;

    GtkWidget* nbfind__(std::function<bool(GtkWidget*)> fn) {
        auto i = std::find_if(notebooks_.begin(), notebooks_.end(), fn);
        return i == notebooks_.end() ? nullptr : *i;
    }

	struct buju___ {
		GtkBox *box_lt_ = nullptr, *box_rt_ = nullptr, *box_tp_ = nullptr, *box_bm_ = nullptr;
		GtkWidget *nb1_ = nullptr;
	};
	std::vector<buju___*> bujus_;
	buju___*buju__(view___*v) {return (buju___*)v->buju_;}
	static page_vs2___ page_vs2__(view___* v) {
		return (page_vs2___)v->views_;
	}

	window___(main_plugin___ * pub, code___* code) : pub_(pub), code_(code) {
		hr_ = pub->window_new__();
		g_signal_connect(hr_, "delete-event", G_CALLBACK(delete_event__), this);
	}
	~window___() {
		for(auto& i : views_.a_)
			on_close__(i, 1 + 8 + 32 /* + 2 + 4*/);
		for(auto& i : bujus_) {
			delete i;
		}
	}
	bool on_destroy__() {
		pub_->main_eval__({"窗关闭", name__()});
		if(main_) {
			pub_->quit__();
			return true;
		}
		return false;
	}

	int for__(args___ p, size_t& from, bool restart, rust_add___ add, void* env);
	int for__(GtkWidget*, view___*&, args___, size_t&, bool, bool, bool, rust_add___, void*);
	int for2__(view___* view, args___ p, size_t& from, int fn2_ret2 = pub::clpars_ret_no_);

	static GtkWidget *pack__(plugin::view___*, plugin::view___*, int posi);

	static bool bool__(args___ p2) {
		return p2.size() == 1 && (p2[0] == "x" || p2[0] == "n");
	}
	static void close__(view___* v, bool and_vs2) {
		window___* w = (window___*)(v->window_);
		page_vs___ &vs = w->views_.a_, *vs2 = page_vs2__(v);
		if(vs2) for(auto& v2 : *vs2) {
			if(!v2->can_close__())
				return;
		}
		{
			vec___ args = {"关闭"};
			vec___ p2;
			w->pub_->std__(v, args);
			w->pub_->main_eval__(args, &p2);
			if(bool__(p2))
				return;
			else if(!p2.empty()) {
				w->pub_->pr__(&p2, args[0]);
				return;
			}
		}
		w->on_close__(v, 32 + 16 + 1 + (and_vs2 ? 2 : 0));
		bool can_rm = true;
		if(!and_vs2)
			if(vs2) for(auto& v2 : *vs2) {
				if(v2->yuxiangrousi__()) {
					can_rm = false;
					break;
				}
			}
		if(can_rm) {
			if(v->is_curr__()) for(auto& v2 : vs) {
				if(v->upid_ == v2->id_) {
					if(v->nb1_ == v2->nb1_)
						v2->curr__();
					break;
				}
			}
			gtk_notebook_remove_page(v->nb__(), v->page_num__());
		}
		w->on_close__(v, 8 + 4);
		if(vs.empty())
			gtk_window_close(w->hr2__());
	}

	void show__() {gtk_widget_show (hr_);}
	GtkWindow* hr2__() {return GTK_WINDOW (hr_);}
	GdkWindow *hr3__() {return gtk_widget_get_window(hr_);}
};
