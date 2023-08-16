#pragma once

#include <string>
#include <vector>
#include <gtk/gtk.h>

namespace pub {

class event___ {
    private:
    static gboolean mouse__(GtkWidget *widget, GdkEventButton *event, event___* thiz) {
        std::vector<std::string> p;
        p.push_back(std::to_string(event->button));
        p.push_back(std::to_string(event->x));
        p.push_back(std::to_string(event->y));
        return thiz->jieshi__(&p, TRUE);
    }
    static gboolean key__(GtkWidget *widget, GdkEventKey *event, event___* thiz) {
        std::string state;
        if((event->state & GDK_SUPER_MASK))
            state += "Super";
        if((event->state & GDK_SHIFT_MASK))
            state += "Shift";
        if((event->state & GDK_CONTROL_MASK))
            state += "Control";
        if((event->state & GDK_MOD1_MASK))
            state += "Alt";
        std::vector<std::string> p;
        p.push_back(gdk_keyval_name(event->keyval));
        p.push_back(state);
        return thiz->jieshi__(&p, TRUE);
    }
    static gboolean scroll__(GtkWidget *widget, GdkEventScroll *scroll, event___* thiz) {
        std::vector<std::string> p;
        p.push_back(std::to_string(scroll->direction));
        return thiz->jieshi__(&p, TRUE);
    }
    static gboolean other__(GtkWidget *widget, GdkEvent *event, event___* thiz) {
        return thiz->jieshi__(nullptr, FALSE);
    }

    protected:
    std::string code_;
 
    virtual gboolean jieshi__(const std::vector<std::string>*, gboolean) = 0;

    public:
    void conn__(GtkWidget *hr, const std::string& p2, const std::string& code) {
    	GObject *obj = G_OBJECT(hr);
        std::string sn = p2;
        if(sn == "-按键")
            sn = "key-press-event";
        code_ = code;
        do {
    		std::string head = "key";
            if(sn.compare(0, head.size(), head) == 0) {
                g_signal_connect(obj, sn.c_str(), G_CALLBACK(key__), this);
                break;
            }
            head = "button";
            if(sn.compare(0, head.size(), head) == 0 || sn == "motion-notify-event") {
                g_signal_connect(obj, sn.c_str(), G_CALLBACK(mouse__), this);
                break;
            }
            if(sn == "scroll-event") {
                g_signal_connect(obj, sn.c_str(), G_CALLBACK(scroll__), this);
                break;
            }
            g_signal_connect(obj, sn.c_str(), G_CALLBACK(other__), this);
        } while(false);
    }
};

class tuodong___ {
    private:
    bool in_ = false;
    double x_, y_;
    GdkCursor *cursor_ = nullptr;
    static gboolean bp__(GtkWidget *widget, GdkEventButton *event, tuodong___* thiz) {
        if(thiz->pause_) return false;
        switch(event->button) {
            case 1:
            thiz->in_ = true;
            thiz->x_ = event->x;
            thiz->y_ = event->y;
            thiz->cursor_ = gdk_cursor_new(GDK_FLEUR);
            gdk_window_set_cursor(thiz->hr3__(), thiz->cursor_);
            return true;
        }
        return false;
    }
    static gboolean br__(GtkWidget *widget, GdkEventButton *event, tuodong___* thiz) {
        if(thiz->pause_) return false;
        if(thiz->in_) {
            thiz->in_ = false;
            gdk_cursor_unref(thiz->cursor_);
            thiz->cursor_ = nullptr;
            gdk_window_set_cursor(thiz->hr3__(), thiz->cursor_);
            return true;
        }
        return false;
    }
    static gboolean mn__(GtkWidget *widget, GdkEventButton *event, tuodong___* thiz) {
        if(thiz->pause_) return false;
        if(thiz->in_) {
            int x, y;
			gtk_window_get_position(thiz->hr2__(), &x, &y);
            x += event->x - thiz->x_;
            y += event->y - thiz->y_;
            gtk_window_move(thiz->hr2__(), x, y);
            return true;
        }
        return false;
    }

    protected:
    bool pause_ = false;
    virtual GtkWindow* hr2__() = 0;
    virtual GdkWindow *hr3__() = 0;

    public:
    void conn__(GtkWidget *hr) {
    	GObject *obj = G_OBJECT(hr);
        g_signal_connect(obj, "button-press-event", G_CALLBACK(bp__), this);
        g_signal_connect(obj, "button-release-event", G_CALLBACK(br__), this);
        g_signal_connect(obj, "motion-notify-event", G_CALLBACK(mn__), this);
    }
};

}