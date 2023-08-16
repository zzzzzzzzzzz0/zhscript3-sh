#include "pub.h"

bool starts__(const std::string& s, const std::string& s2) {
#ifdef _std20_
		return s.starts_with(s2);
#else
		for(int i = 0;; i++) {
			char c = s2[i];
			if(!c) break;
			if(c != s[i]) return false;
		}
		return true;
#endif
}
bool ends__(const std::string& s, const std::string& s2) {
#ifdef _std20_
		return s.ends_with(s2);
#else
		for(int i = s.length(), i2 = s2.length();;) {
			--i, --i2;
			if(i < 0 || i2 < 0) {
				if(i2 < 0) return true;
				return false;
			}
			if(s2[i2] != s[i]) return false;
		}
		return false;
#endif
}

void clpars2__(std::string& s, std::vector<char*>& args2) {
    char c1 = ' ', c2 = '"', c3 = '\'';
    char c = c1;
    std::string s2 = s, s3;
    for(bool b = false, b2 = false, b3 = false; !b2;) {
        size_t i2 = s2.find(c);
        if(i2 != std::string::npos) {
            if(!b) {
                s = s2.substr(0, i2);
	            b = true;
            } else {
                s3 = s2.substr(0, i2);
            }
            s2 = s2.substr(i2 + 1);
            size_t i21 = s2.find(c1);
            size_t i22 = s2.find(c2);
            size_t i23 = s2.find(c3);
            if(i21 == std::string::npos && i22 == std::string::npos && i23 == std::string::npos) {
                b2 = true;
                s3 += s2;
            } else {
                c = c1;
                size_t i3 = i21;
                if(i22 < i21) {
                    c = c2;
                    i3 = i22;
                }
                if(i23 < i22 || i23 < i21) {
                    c = c3;
                    i3 = i23;
                }
                s3 += s2.substr(0, i3);
                s2 = s2.substr(i3 + 1);
            }
            b3 = true;
/*#ifdef _debug_
            std::cout << "[" << c << "]" 
            << std::to_string(i21)
            << "," << std::to_string(i22)
            << "," << std::to_string(i23) 
            << "\t" << std::to_string(i2) 
            << "|" << s2 << std::endl;
#endif*/
        } else {
            b2 = true;
            if(b) {
            	s3 = s2;
            	b3 = true;
            }
        }
        if(b3) {
/*#ifdef _debug_
            std::cout << s3 << std::endl;
#endif*/
			if(s3 == "--。") {}
			else {
		        size_t end = s3.size();
		        char* s4 = new char[end + 1];
		        s3.copy(s4, end);
		        s4[end] = 0;
		        args2.push_back(s4);
            }
        }
    }
}

void box_new__(GtkOrientation o, GtkWidget *&box1, GtkBox *&box) {
    box1 = gtk_box_new(o, 0);
    box = GTK_BOX(box1);
}
void label_new__(GtkWidget *&label1, GtkLabel*& label) {
    label1 = gtk_label_new (nullptr);
    label = GTK_LABEL(label1);
}

static GdkPixbuf* pixbuf_2__(args___ p, size_t from) {
    return gtk_icon_theme_load_icon(gtk_icon_theme_get_default(), p[from].c_str(), std::atoi(p[from + 1].c_str()),
        GTK_ICON_LOOKUP_USE_BUILTIN, nullptr);
}
GdkPixbuf* pixbuf__(args___ p, size_t from) {
    switch(p.size() - from) {
        case 2:
        return pixbuf_2__(p, from);
        case 1:
        return gdk_pixbuf_new_from_file(p[from].c_str(), nullptr);
        default:
        return nullptr;
    }
}

GtkWidget *button_new__(GCallback cb, void* view, GtkBox *box, args___ args, size_t from, bool in_end) {
    GtkWidget* img = nullptr;
    switch(args.size() - from) {
    case 2: {
        int i = std::stoi(args[from + 1]);
        if(i <= GTK_ICON_SIZE_DIALOG) {
            //if(i < 0) i = -i;
            if(i <= -10) i = -(i + 10);
            img = gtk_image_new_from_icon_name(args[from].c_str(), (GtkIconSize)i);
        } else {
            img = gtk_image_new_from_pixbuf(pixbuf_2__(args, from));
        }
        break; }
    case 1:
        img = gtk_image_new_from_file(args[from].c_str());
        break;
    }
    GtkWidget *btn1 = gtk_button_new();
    GtkButton* btn = GTK_BUTTON(btn1);
    gtk_button_set_relief(btn, GTK_RELIEF_NONE);
    if(img)
        gtk_button_set_image(btn, img);
    g_signal_connect(btn1, "clicked", cb, view);
    if(in_end)
        gtk_box_pack_end (box, btn1, false, false, 0);
    else
        gtk_box_pack_start (box, btn1, false, false, 0);
    gtk_widget_set_can_focus(btn1, false);
    gtk_widget_show (btn1);
    return btn1;
}

void scrn_w_h__(int& w, int& h) {
    GdkRectangle r;
    r.width = r.height = 0;
    gdk_monitor_get_workarea(gdk_display_get_primary_monitor(gdk_display_get_default()), &r);
    w = r.width;
    h = r.height;
}

int page_num__(GtkNotebook *nb, GtkWidget *w) {
	return gtk_notebook_page_num(nb, w);
}
void curr__(GtkNotebook *nb, GtkWidget *w) {
	gtk_notebook_set_current_page (nb, page_num__(nb, w));
}
bool is_curr__(GtkNotebook *nb, GtkWidget *w) {
    return gtk_notebook_get_current_page (nb) == page_num__(nb, w);
}
void add__(GtkNotebook *nb, GtkWidget *box1, GtkWidget *label_box1, int posi, bool reord) {
	switch(posi) {
		case after_curr_page_:
		posi = gtk_notebook_get_current_page (nb) + 1;
		break;
        case before_curr_page_:
		posi = gtk_notebook_get_current_page (nb);
		break;
	}
	gtk_notebook_insert_page (nb, box1, label_box1, posi);
	gtk_notebook_set_tab_reorderable (nb, box1, reord);
}
void show_tabs__(GtkNotebook *nb, bool b) {
    gtk_notebook_set_show_tabs (nb, b);
    gtk_notebook_set_show_border (nb, b);
}

l4___ l4_;
