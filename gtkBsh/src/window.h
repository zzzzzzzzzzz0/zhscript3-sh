#pragma once
#include "main_plugin.h"
#include "pub.h"
#include "label_box.h"
#include "views.h"
#include "buju.h"

class window___ : public widget___ {
    private:
	code___* code_;
	bool main_ = false;
	GtkWidget *titlebar_ = nullptr, *titlebar_b_ = nullptr;
	int titlebar_w_1_, titlebar_w_2_;

	void on_close__(view___* v, int c);

	public:
	void switch_page2__ (view___* v, GtkNotebook* nb, guint page_num) {
		if(!v->p__()) {
			v->mk_p__([&](const std::string& s, const std::string& s1, const std::string& s2) {
				return pub_->new_view__(s, s1, s2);
			}, [&](args___ a, size_t& l) {
				return buju2_->for2_2__(v, a, l);
			}, [&](args___ a, size_t l) {
				return pub_->goodbye__(a, l);
			});
			pack_box__(v);
		}
		v->okopen__();

		std::string bname;
		pub_->name__(nb, bname);
		vec___ args = {"切换", std::to_string(page_num), bname};
		pub_->fanqiechaodan3__(v, args);
	}
	private:

	static gboolean delete_event__(GtkWidget *widget, GdkEvent *event, window___* thiz) {
		vec___ args = {"窗将关", thiz->name__()}, ret;
		thiz->pub_->fanqiechaodan3__(nullptr, args, &ret);
		return bool__(ret);
	}

	int x_ = -1, y_ = -1, width_ = -1, height_ = -1, border_w_ = 0, border_h_ = 0;
	std::string state_xy_, state_wh_;
	static gboolean configure_event__(GtkWidget *widget, GdkEventConfigure *event, window___* win) {
		int x = event->x, y = event->y;
		if(win->x_ != x || win->y_ != y) {
			win->x_ = x;
			win->y_ = y;
			int  x2, y2;
			gtk_window_get_position(GTK_WINDOW(widget), &x2, &y2);
			win->border_w_ = x - x2;
			win->border_h_ = y - y2;
			if(!win->state_xy_.empty())
				win->pub_->fanqiechaodan2__(nullptr, win->state_xy_, {std::to_string(x2), std::to_string(y2),
																	  std::to_string(x), std::to_string(y), });
		}

		if(!win->state_wh_.empty() || win->titlebar_b_) {
			int w = event->width, h = event->height;
			if(win->width_ != w || win->height_ != h) {
				win->width_ = w;
				win->height_ = h;
				if(!win->state_wh_.empty())
					win->pub_->fanqiechaodan2__(nullptr, win->state_wh_, {std::to_string(w), std::to_string(h)});
				if(win->titlebar_b_) {
					int w2, h2;
					gtk_widget_get_size_request(win->titlebar_, &w2, &h2);
					gtk_widget_set_size_request(win->titlebar_b_, w * win->titlebar_w_1_ / win->titlebar_w_2_, h2);
				}
			}
		}
		return false;
	}

	std::string window_state_event_;
	bool is_icon_ = false;
	static gboolean window_state_event__(GtkWidget *widget, GdkEventWindowState *event, window___* thiz) {
		thiz->is_icon_ = (event->new_window_state & GDK_WINDOW_STATE_ICONIFIED);
		if(!thiz->window_state_event_.empty()) {
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
			};
			fn(event->new_window_state);
			fn(event->changed_mask);
			thiz->pub_->fanqiechaodan2__(nullptr, thiz->window_state_event_, args);
		}
		return false;
	}

	public:
	views___ views_;
	std::vector<GtkWidget*> notebooks_;
	main_plugin___* pub_;
	buju2___* buju2_;

    GtkWidget* nbfind__(std::function<bool(GtkWidget*)> fn) {
        auto i = std::find_if(notebooks_.begin(), notebooks_.end(), fn);
        return i == notebooks_.end() ? nullptr : *i;
    }

	std::vector<buju___*> bujus_;

	window___(main_plugin___ * pub, code___* code) : pub_(pub), code_(code) {
		hr_ = pub->window_new__();
		g_signal_connect(hr_, "delete-event", G_CALLBACK(delete_event__), this);
		g_signal_connect(hr_, "configure-event", G_CALLBACK(configure_event__), this);
		g_signal_connect(hr_, "window-state-event", G_CALLBACK(window_state_event__), this);

		buju2_ = new buju2___(pub, code, &bujus_, &views_, &notebooks_);
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
	int for__(GtkWidget *nb1_, view___*& view_, args___ p, size_t& from,
			bool no_new, bool nb1_need_new, bool is1, rust_add___ add, void* env) {
		return buju2_->for__(this, to_cntr__(), nb1_, view_, p, from, no_new, nb1_need_new, is1, add, env);
	}
	int for2__(view___* view, args___ p, size_t& from, int fn2_ret2 = pub::clpars_ret_no_) {
		return buju2_->for2__(this, view, p, from, fn2_ret2);
	}

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

	void act__() {gtk_window_present(hr2__());}
	bool is_act__() {return gtk_window_is_active(hr2__());}

	void show__() {gtk_widget_show (hr_);}
	GtkWindow* hr2__() {return GTK_WINDOW (hr_);}
	GdkWindow *hr3__() {return gtk_widget_get_window(hr_);}
};
