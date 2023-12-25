#pragma once
#include <gtk/gtk.h>
#include <cairo.h>

bool screenshot__(GtkWidget *hr, const char *path) {
    GtkWindow* hr2 = GTK_WINDOW (hr);
    gint w, h;
    gtk_window_get_size(hr2, &w, &h);
    GdkPixbuf *pixbuf = gdk_pixbuf_get_from_window(gtk_widget_get_window(hr), 0, 0, w, h);
    if(!pixbuf)
        return false;
    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h);
    cairo_t *cr = cairo_create(surface);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
    cairo_paint(cr);
    bool ret = cairo_surface_write_to_png(surface, path) == CAIRO_STATUS_SUCCESS;
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    g_object_unref(pixbuf);
    return ret;
}