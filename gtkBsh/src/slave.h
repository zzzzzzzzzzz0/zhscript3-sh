#pragma once
#include <string>
#include <vector>
#include <glib.h>

namespace pub {

class slave___ {
	int sv_[2];
	int pid_ = -1;
	GIOChannel *ioc_ = NULL;
	GSource *ios_;
	bool stop_ = true;
public:
	virtual void z__(const char *s) {}

	int init__(const std::vector<std::string>& args, size_t from, GMainContext *mc);
	void stop__();
	bool is_stop__() {return stop_;}
	void send__(const std::string& s);
};

GMainContext *thread__(const char *name);

}
