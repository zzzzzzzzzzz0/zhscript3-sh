#pragma once
#include "view.h"

struct buju___ {
    GtkBox *box_lt_ = nullptr, *box_rt_ = nullptr, *box_tp_ = nullptr, *box_bm_ = nullptr;
    GtkWidget *nb1_ = nullptr;
};

buju___*buju__(view___*v);
page_vs2___ page_vs2__(view___* v);

class buju2___ {
    private:
    std::vector<buju___*> *bujus_;
    views___ *views_;
    std::vector<GtkWidget*> *notebooks_;
    main_plugin___* pub_;
    code___* code_;

    public:
    buju2___(main_plugin___* pub, code___* code, std::vector<buju___*> *bujus, views___ *views, std::vector<GtkWidget*> *notebooks)
        : views_(views), bujus_(bujus), pub_(pub), notebooks_(notebooks), code_(code) {}

    int for__(void* window, GtkContainer* cntr_, GtkWidget *nb1_, view___*& view_, args___ p, size_t& from,
		bool no_new, bool nb1_need_new, bool is1, rust_add___ add, void* env);
	int for2__(void* window, view___* view, args___ p, size_t& from, int fn2_ret2 = pub::clpars_ret_no_);
	int for2_2__(view___* view, args___ p, size_t& from);

	void pack__(void* window, view___* view, GtkWidget *box1, label_box___ *label_box, GtkWidget *nb1, size_t id, view___* by,
			char can_close, bool can_close2, bool page_curr2, bool expand, int padding);
	bool pack_2__(void* window, view___* view) {
		vec___ p3;
		{
			vec___ args = {"初始"};
			pub_->fanqiechaodan3__(view, args, &p3);
		}
		view->args1_.insert(view->args1_.end(), 
			std::make_move_iterator(p3.begin()),
			std::make_move_iterator(p3.end()));
		return true;
	}
};

void new_page__(bool vert, int posi, bool reord, bool padding2, bool vert2, GtkAlign top_align, GtkAlign bottom_align,
    GtkNotebook *nb, GtkWidget *&box1, GtkBox *&box, label_box___ *&label_box);
void pack_box__(view___* view);
