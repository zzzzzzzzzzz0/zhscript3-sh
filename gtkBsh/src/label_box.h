#pragma once

class button___ {
	private:
	static void clicked__(GtkButton *button, button___* thiz) {
		vec___ p {thiz->name_};
		view___* v = thiz->v_;
		if(v)
			p.push_back(v->name__());
		const char* s = gtk_button_get_label(button);
		if(s) {
			if(!v)
				p.push_back("");
			p.push_back(s);
		}
		thiz->pub_->fanqiechaodan2__(v, thiz->code_.empty() ? thiz->name_ : thiz->code_, p);
	}

	view___* v_;
	main_plugin___* pub_;

	public:
	std::string code_, name_;

	button___(view___* v, main_plugin___* pub) : v_(v), pub_(pub) {}
	void with__(char typ, GtkBox *box, args___ p2, size_t from2) {
		gtk_widget_set_tooltip_markup(button_new__(G_CALLBACK(clicked__), this, box, p2, from2, false, typ), name_.c_str());
	}
};

#define paddi_  0
#define paddi2_ 0
#define paddi3_ 0
#define paddi4_ 1
#define paddii_ 0
class label_box___ {
    private:
    GtkBox *box_ = nullptr;

    public:
    GtkWidget *box1_ = nullptr;
    GtkBox *right_ = nullptr, *right2_ = nullptr, *left_ = nullptr, *bottom_ = nullptr, *top_ = nullptr;
	GtkLabel *label_ = nullptr, *label2_ = nullptr, *label3_ = nullptr, *label4_ = nullptr;
	int has_close_ = 0;
    GtkAlign top_align_, bottom_align_;
    bool vert_;
	void *views_ = nullptr;

    std::vector<button___*> buttons_;

    label_box___(bool padding, bool vert, GtkAlign top_align, GtkAlign bottom_align) :
            vert_(vert),
            top_align_(top_align),
            bottom_align_(bottom_align) {
        GtkWidget *label1, *label2_1, *label3_1, *label4_1;
        label_new__(label1, label_);
        label_new__(label2_1, label2_);
        label_new__(label3_1, label3_);
        label_new__(label4_1, label4_);

        GtkWidget *right1, *right2_1, *left1, *bottom1, *top1, *box1;
        GtkBox *box;
        GtkOrientation o1, o2;
        if(vert) {
            o1 = GTK_ORIENTATION_HORIZONTAL;
            o2 = GTK_ORIENTATION_VERTICAL;
        } else {
            o2 = GTK_ORIENTATION_HORIZONTAL;
            o1 = GTK_ORIENTATION_VERTICAL;
        }
        box_new__(o1, box1_, box_);
        box_new__(o2, right1, right_); 
        box_new__(o2, right2_1, right2_); 
        box_new__(o2, left1, left_); 
        box_new__(o2, bottom1, bottom_); 
        box_new__(o2, top1, top_); 
        box_new__(o2, box1, box);
        gtk_widget_set_halign(top1, top_align_);
        gtk_widget_set_halign(bottom1, bottom_align_);
        gtk_box_pack_start (box, left1, false, false, paddii_);
        gtk_box_pack_start (box, label2_1, false, false, paddii_);
        gtk_box_pack_start (box, label1, true, true, padding ? 7 : paddii_);
        gtk_box_pack_start (box, label3_1, false, false, paddii_);
        gtk_box_pack_start (box, right1, false, false, paddii_);
        gtk_box_pack_start (box, right2_1, false, false, paddii_);
        gtk_box_pack_start (box, label4_1, false, false, paddii_);
        gtk_box_pack_start (box_, top1, false, false, paddii_);
        gtk_box_pack_start (box_, box1, true, true, paddii_);
        gtk_box_pack_start (box_, bottom1, false, false, paddii_);
        if(vert) {
            auto neww = []() {
                return gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            };
            auto add2 = [&](GtkBox *b) {
                gtk_box_pack_start(b, neww(), false, false, 0);
                gtk_box_pack_end  (b, neww(), false, false, 0);
            };
            add2(right_);
            add2(right2_);
            add2(left_);
            add2(top_);
            add2(bottom_);
        }
    }
};
