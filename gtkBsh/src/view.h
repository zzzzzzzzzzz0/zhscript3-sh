#pragma once
#include "../../plugin/pub.h"

class view___ {
    private:
    plugin::view___* p_ = nullptr;
    std::string pluginame_, name_;
    int w_, h_;
    bool no_focus_, open_ = false;

    public:
 	size_t id_ = 0, upid_ = 0;
	std::string arg1_, arg2_, attach_;
    vec___ args1_;
	bool is_die_ = false;
    const char* path__() {
        return p_ ? p_->path__() : "";
    }

	view___(const std::string& pluginame, const std::string& arg1, const std::string& arg2,
    const std::string& name, int w, int h, bool no_focus) :
    pluginame_(pluginame),arg1_(arg1),arg2_(arg2),name_(name),w_(w),h_(h),no_focus_(no_focus) {}
    view___* copy__(plugin::view___* v1) {
        view___* v = new view___(pluginame_, "", "", "", w_, h_, no_focus_);
        v->buju_ = buju_;
        v->kou_nb1_ = kou_nb1_;
        v->kou_box1_ = kou_box1_;
        v->p_ = v1;
        v1->p_ = v;
        v->open_ = true;
        return v;
    }

	using new_view___ = std::function<plugin::view___*(const std::string&, const std::string&, const std::string&)>;
    void mk_p__(new_view___ new_view) {
        p_ = new_view(pluginame_, arg1_, arg2_);
        if(!p_)
            return;
        p_->p_ = this;
        p_->need_focus_ = need_focus_;
        if(!name_.empty())
            p_->name__(name_.c_str());
        if(w_ != -1 || h_ != -1) {
            gtk_widget_set_size_request (p_->hr__(), w_, h_);
        }
        if(no_focus_)
            gtk_widget_set_can_focus(p_->hr__(), false);
        if(!args1_.empty()) {
            size_t from = 0;
            int ret2 = p_->for__(args1_, from, nullptr, nullptr);
        }
        open_ = true;
    }
    plugin::view___* p__() {
        return p_;
    }

    GtkWidget *hr__() {
        return p_ ? p_->hr__() : nullptr;
    }
    const char* name__() {
        return name_.c_str();
    }

    void open__(const std::string& arg1, const std::string& arg2) {
        if(p_) {
            p_->open__(arg1_, arg2_);
            open_ = true;
        }
    }
	void okopen__() {
        if(!open_)
            open__(arg1_, arg2_);
    }
	bool is_open__() {return open_;}

    int for__(args___ args, size_t& from, rust_add___ add, void* env) {
        return p_ ? p_->for__(args, from, add, env) : 0;
    }
    const char* plugin_id__() {
        return p_ ? p_->plugin_id__() : pluginame_.c_str();
    }
    void on_close__() {
        if(p_)
            p_->on_close__();
    }
    bool can_close__() {
        return p_ ? p_->can_close__() : true;
    }
    bool yuxiangrousi__() {
        return p_ ? p_->yuxiangrousi__() : false;
    }

	GtkWidget *nb1_ = nullptr, *box1_ = nullptr, *kou_nb1_ = nullptr, *kou_box1_ = nullptr;
	GtkNotebook *nb__() {return GTK_NOTEBOOK(nb1_);}
	GtkBox* box__() {return GTK_BOX(box1_);}
	void *window_ = nullptr, *label_box_ = nullptr, *buju_ = nullptr, *views_ = nullptr;
	char has_close_ = '\0';
	bool need_focus_ = false, lazy_ = false, hulve1qie_ = false, expand_;
    int padding_;

	int page_num__() {
		return gtk_notebook_page_num(nb__(), box1_);
	}
	void curr__() {
		if(!lazy_)
			okopen__();
		gtk_notebook_set_current_page (nb__(), page_num__());
		if(kou_nb1_) {
			GtkNotebook *nb = GTK_NOTEBOOK(kou_nb1_);
			gtk_notebook_set_current_page (nb, gtk_notebook_page_num(nb, kou_box1_));
		}
	}
	bool is_curr__() {
		return gtk_notebook_get_current_page (nb__()) == page_num__();
	}
	void focus__() {
		if(p_)
            p_->focus__();
	}
};