#pragma once
#include "view.h"

class window___;

class main_plugin___ : public plugin::pub___ {
    public:
    std::vector<window___*> windows_;

    virtual GtkWidget *window_new__() = 0;
    virtual void quit__() = 0;
    virtual window___* find__(const std::string& name) = 0;
    virtual int goodbye__(args___ p, size_t from) = 0;

    virtual void name__(GtkNotebook*, std::string&) = 0;
    virtual plugin::view___* new_view__(const std::string&, const std::string&, const std::string&) = 0;

    virtual int fanqiechaodan__(view___*, const std::string&, rets___ ret = nullptr, argc___ argc = 0, argv___ argv = nullptr, void* env = nullptr) = 0;
    virtual int fanqiechaodan2__(view___*, const std::string&, args___, rets___ ret = nullptr, void* env = nullptr) = 0;
    virtual int fanqiechaodan3__(view___*, vec___&, rets___ ret = nullptr, void* env = nullptr) = 0;
    virtual void std__(view___*, vec___&) = 0;

    virtual int for__(args___ p, size_t& from, rust_add___ add, void* env) = 0;
    virtual int for__(window___* window, GtkWidget *nb1, view___* view, args___ p, size_t& from, int fn2_ret,
			bool no_newindow, bool nb1_need_new, bool is1, rust_add___ add, void* env) = 0;
    virtual int for__(view___* view, args___ p, size_t& from, view___* by, rust_add___ add, void* env) = 0;
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

    void on_new__(std::function<void(vec___&)> fn, view___* v, main_plugin___* pub) {
        if(!code_new_.empty()) {
            vec___ args;
            if(fn)
                fn(args);
            else {
                args.push_back(std::to_string(v->id_));
                args.push_back(v->name__());
            }
            pub->fanqiechaodan2__(v, code_new_, args);
        }
    }

    void on_del__(view___* v, main_plugin___* mp) {
		if(!code_del_.empty()) {
			vec___ args {std::to_string(v->id_),
                v->is_curr__() ? "1" : "",
                v->id_ < start_i_ ? "1" : ""};
			mp->fanqiechaodan2__(v, code_del_, args);
		}
    }
};
