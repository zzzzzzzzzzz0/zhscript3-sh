#pragma once
#include <gtk/gtk.h>

class widget___ {
    protected:
    GtkWidget *hr_;

	private:
	bool has_name_ = false;

    public:
    widget___(GtkWidget* hr = nullptr) : hr_(hr) {}

    GtkWidget *hr__() {return hr_;}
 	virtual int scroll__() {return 0;}
	GtkContainer* to_cntr__() {return GTK_CONTAINER(hr_);}

	void name__(const char* name) {
		gtk_widget_set_name(hr_, name);
		has_name_ = true;
	}
	const char* name__() {
		if(!has_name_)
			return "";
		const char* name = name__(hr_);
		return name ? name : "";
	}
	static const char* name__(GtkWidget* hr) {return gtk_widget_get_name(hr);}

	void this__() {var__(hr_, "对", this);}
	static widget___* this__(GtkWidget* hr) {return (widget___*)var__(hr, "对");}

	void var__(const char *name, gpointer data) {var__(hr_, name, data);}
	auto var__(const char *name) -> gpointer {return var__(hr_, name);}
	static void var__(GtkWidget* hr, const char *name, gpointer data) {
		g_object_set_data(G_OBJECT(hr), name, data);
	}
	static gpointer var__(GtkWidget* hr, const char *name) {
		return g_object_get_data(G_OBJECT(hr), name);
	}

	void* tuodong_ = nullptr;
};
