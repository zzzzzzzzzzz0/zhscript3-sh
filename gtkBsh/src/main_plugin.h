#pragma once
#include "../../plugin/pub.h"

class window___;

class main_plugin___ : public plugin::pub___ {
    public:
	std::vector<window___*> windows_;

    virtual GtkWidget *window_new__() = 0;
    virtual void quit__() = 0;
    virtual window___* find__(const std::string& name) = 0;
    virtual int goodbye__(args___ p, size_t from) = 0;

	virtual void name__(GtkNotebook*, std::string&) = 0;
};

class code___ {
    public:
    std::string code_, coderr_, code_new_, code_del_;
	size_t start_i_ = time(nullptr);

    static void op__(const std::string &s2, char c, std::string& s) {
        switch(c) {
            case '+': {
            size_t i2 = s.find(s2);
            if(i2 == std::string::npos)
                s += s2;
            break; }
            case '-': {
            size_t i2 = s.find(s2);
            if(i2 != std::string::npos)
                s = s.replace(i2, s2.size(), "");
            break; }
            default: s = s2; break;
        }
#ifdef _debug_
        printf("\t\tnew %s\n", s.c_str());
#endif
    }
    static void op__(const std::string &s2, const std::string &s3, size_t i3, const std::string &tag, std::string& s) {
        char c = s3[i3];
#ifdef _debug_
        printf("%s %s'%c'\told %s\n", s3.c_str(), tag.c_str(), c, s.c_str());
#endif
        op__(s2, c, s);
    }

    void on_new__(std::function<void(vec___&)> fn, plugin::view___* v, main_plugin___* pub) {
        if(!code_new_.empty()) {
            vec___ args;
            if(fn)
                fn(args);
            else {
                args.push_back(std::to_string(v->id_));
                args.push_back(v->has_name_ ? v->name__() : "");
            }
            pub->fanqiechaodan2__(v, code_new_, args);
        }
    }

    void on_del__(plugin::view___* v, main_plugin___* mp) {
		if(!code_del_.empty()) {
			vec___ args {std::to_string(v->id_),
                v->is_curr__() ? "1" : "",
                v->id_ < start_i_ ? "1" : ""};
			mp->fanqiechaodan2__(v, code_del_, args);
		}
    }
};
