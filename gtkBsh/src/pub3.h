#pragma once
#include "event.h"
#include "window.h"

class event___ : public pub::event___ {
	gboolean jieshi__(const std::vector<std::string>* p, gboolean ret1) {
		vec___ arg, ret;
		if(p)
			arg = *p;
		pub_->fanqiechaodan2__(v_, code_, arg, &ret);
		if(ret.size() == 1) {
			if(ret[0] == "1") return TRUE;
			if(ret[0] == "0") return FALSE;
		}
		if(!ret.empty())
			pub_->goodbye__(ret, 0);
		return ret1;
	}
	main_plugin___* pub_ = nullptr;
	view___* v_ = nullptr;
	public:
	event___(main_plugin___* pub, view___* v) : pub_(pub), v_(v) {}
};
class tuodong___ : public pub::tuodong___ {
	GtkWindow* hr2__() {return w_->hr2__();}
	GdkWindow *hr3__() {return w_->hr3__();}
	window___* w_ = nullptr;
	public:
	tuodong___(window___* w) : w_(w) {}

    static size_t for__(const std::vector<std::string>& args, size_t& from, window___* w, widget___* p) {
        const char* ss[] = {"-鼠标拖动", "-鼠标拖动-停", "-鼠标拖动-启", "-鼠标拖动-切停"};
        size_t ret = std::string::npos;
        for(size_t i2 = from; i2 < args.size(); i2++) {
			auto& s = args[i2];
			if(s.empty()) continue;
			bool b = true;
            for(size_t i = 0; i <= 3; i++) {
                if(s == ss[i]) {
                    switch(i) {
                        case 0:
						if(!p->tuodong_) {
							tuodong___* td = new tuodong___(w);
							td->conn__(p->hr__());
							p->tuodong_ = td;
						}
                        break;
						default:
						if(p->tuodong_) {
							tuodong___* td = (tuodong___*)p->tuodong_;
							td->pause_ = i == 3 ? !td->pause_ : i == 2;
						} else
							return ret;
						break;
                    }
					from = i2;
                    ret = i;
					b = false;
					break;
                }
            }
			if(b) break;
        }
        return ret;
    }
};
