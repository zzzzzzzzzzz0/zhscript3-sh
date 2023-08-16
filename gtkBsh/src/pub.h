#pragma once
#include <iostream>
#include <gtk/gtk.h>
#include "../../pub/tag.h"
#include "../../pub/l4.h"

bool starts__(const std::string& s, const std::string& s2);
bool ends__(const std::string& s, const std::string& s2);

void clpars2__(std::string& s, std::vector<char*>& args2);

void box_new__(GtkOrientation o, GtkWidget *&box1, GtkBox *&box);
void label_new__(GtkWidget *&label1, GtkLabel*& label);
GtkWidget* button_new__(GCallback cb, void* view, GtkBox *box, args___ args, size_t from, bool in_end = false);
GdkPixbuf* pixbuf__(args___ p, size_t from);

void scrn_w_h__(int& w, int& h);

int page_num__(GtkNotebook *nb, GtkWidget *w);
void curr__(GtkNotebook *nb, GtkWidget *w);
bool is_curr__(GtkNotebook *nb, GtkWidget *w);
void add__(GtkNotebook *nb, GtkWidget *box1, GtkWidget *label_box1 = nullptr, int posi = append_page_, bool reord = true);
void show_tabs__(GtkNotebook *nb, bool);

extern l4___ l4_;
