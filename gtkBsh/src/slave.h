#pragma once
#include "../../plugin/pub.h"
#include <glib.h>

class slave___ {
	int sv_[2];
	int pid_ = -1;
	GIOChannel *ioc_;
	GSource *ios_;
public:
	std::string code_;
	plugin::pub___* pub_;

	slave___(plugin::pub___* pub) : pub_(pub) {}
	int init__(args___ args, size_t from, GMainContext *mc);
	void stop__();
	void send__(const std::string& s);
};