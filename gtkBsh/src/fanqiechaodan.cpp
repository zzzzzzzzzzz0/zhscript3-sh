#include "fanqiechaodan.h"

#include "slave.h"
class slave___ : public pub::slave___ {
	std::string code_;
	plugin::pub___* pub_;

public:
	slave___(plugin::pub___* pub) : pub_(pub) {}
	int init__(args___ p, size_t i, bool has_env) {
		code_ = p[i++];
		vec___ envs;
		if(has_env)
			pub_->eval__(p[i++].c_str(), &envs);
		return pub::slave___::init__(p, i, envs, pub::thread__(code_.c_str()));
	}

	void z__(const char *s) {
		vec___ args{s};
		pub_->eval__(code_.c_str(), args);
	}
};

class fanqiechaodan___ {
public:
    view___* by; vec___ p; size_t from; rets___ ret; rust_add___* add; void* env; main_plugin___* thiz;
};

int fanqiechaodan__(view___* by, args___ p, size_t& from, rets___ ret, rust_add___ add, void* env, main_plugin___* thiz);
static gboolean idle__(gpointer data) {
    fanqiechaodan___* f = (fanqiechaodan___*)data;
    fanqiechaodan__(f->by, f->p, f->from, f->ret, f->add, f->env, f->thiz);
    return FALSE;
}

int fanqiechaodan__(view___* by, args___ p, size_t& from, rets___ ret, rust_add___ add, void* env, main_plugin___* thiz) {
    int ret2 = thiz->for__(p, from, add, env); if(ret2 != 0) return ret2;
    view___* view_ = by;
    window___* window = view_ ? (window___*)view_->window_ : (!thiz->windows_.empty() ? thiz->windows_[0] : nullptr);
    GtkWidget* nb1_ = view_ ? view_->nb1_ : nullptr;
    bool is1 = false, dunhao = false, threads_enter = false;
    int test_1 = 0;
    auto test_2 = [&](bool b, int& fn2_ret2) -> bool {
        if(test_1 && !b) {
            if(test_1 == '1')
                thiz->add__("0", dunhao, add, env);
            fn2_ret2 = pub::clpars_ret_;
            return true;
        }
        return false;
    };
    ret2 = thiz->clpars__({
        {"-id",  "ji ", 1},
        {"-id2", "ji2", 1, "后继也改"},
        {"-页",  "j  ", 1},
        {"-页2", "j 2", 1, "后继也改"},
        {"-簿", "b", 1},
        {"-窗", "w", 1},
        {"-储",     "v  ", 2},
        {"-窗储",   "vw ", 2},
        {"-得储",   "v =", 1},
        {"-得窗储", "vw=", 1},
        {"-被动者", "s", 3},
        {"-被动者2", "s2", 3},
        {"-命令被动者", "sc", 2},
        {"-停止被动者", "sx", 1},
        {"-稳", "T", 0},
        {"-单", "1", 0},
        {"-试", "t1", 0, "有错不报而回0"},
        {"-勉", "t2", 0, "有错算了"},
        {"-等待", "W", 1},
    }, p, from, [&](const std::string& tag, size_t i, size_t argc, int& fn2_ret2) {
        switch(tag[0]) {
        case 'j': {
            view___* view = nullptr;
            switch(tag[1]) {
                case 'i': {
                    size_t id = std::stoul(p[i]);
                    for(auto& w : thiz->windows_)
                        if((view = w->views_.find__([&](auto v) {return v->id_ == id;})))
                            goto bj;
                    break; }
                default: {
                    const std::string& name = p[i];
                    for(auto& w : thiz->windows_)
                        if((view = w->views_.find__([&](auto v) {
                            const char* name2 = v->name__();
                            return name2 && name2 == name;
                        })))
                            goto bj;
                    break; }
            }
            bj:
            if(test_2(view, fn2_ret2)) return;
            if(!view)
                throw "页无觅 " + p[i];
            do {
                ret2 = thiz->for__(view, p, from, by, add, env);
                if(ret2 != 0) {
                    fn2_ret2 = pub::clpars_ret_;
                    return;
                }
                view->for__(p, from, add, env);
                switch(tag[2]) {
                    case '2':
                    view_ = view;
                    nb1_ = view_->nb1_;
                    break;
                }
            } while(false);
            break; }
        case 'b': {
            nb1_ = nullptr;
            view_ = nullptr;
            for(auto& w : thiz->windows_)
            for(auto& nb1 : w->notebooks_) {
                const char* name = gtk_widget_get_name(nb1);
                if(name && name == p[i]) {
                    nb1_ = nb1;
                    for(auto& v : w->views_.a_) {
                        if(v->nb1_ == nb1 && v->is_curr__()) {
                            view_ = v;
                            if(v->yuxiangrousi__())
                                break;
                        }
                        if(v->kou_nb1_ == nb1 && is_curr__(GTK_NOTEBOOK(v->kou_nb1_), v->kou_box1_)) {
                            for(auto& v2 : w->views_.a_) {
                                if(v2->nb1_ == v->nb1_ && v2->is_curr__()) {
                                    view_ = v2;
                                    if(v2->yuxiangrousi__())
                                        goto b;
                                }
                            }
                        }
                    }
                    b:
                    break;
                }
            }
            if(test_2(nb1_, fn2_ret2)) return;
            if(!nb1_)
                throw "簿无觅 " + p[i];
            do {
                ret2 = thiz->for__(view_, p, from, by, add, env);
                if(ret2 != 0) {
                    fn2_ret2 = pub::clpars_ret_;
                    return;
                }
                if(view_) view_->for__(p, from, add, env);
            } while(false);
            break; }
        case 'w':
            window = nullptr;
            for(auto& w : thiz->windows_)
                if(w->name__() == p[i]) {
                    window = w;
                    break;
                }
            if(test_2(window, fn2_ret2)) return;
            if(!window)
                throw "窗无觅 " + p[i];
            break;
        case 'v': {
            std::string name = "储-" + p[i];
            switch(tag[2]) {
            case '=': {
                auto fn = [&](auto* w) {
                    thiz->add__((char*)w->var__(name.c_str()), dunhao, add, env);
                };
                switch(tag[1]) {
                case 'w': fn(window); break;
                default: fn(view_->p__()); break;
                }
                break; }
            default: {
                auto& s = p[i + 1];
                auto fn = [&](auto* w) {
                    char* s2 = new char[s.length() + 1];
                    s.copy(s2, s.length());
                    s2[s.length()] = 0;
                    w->var__(name.c_str(), s2);
                };
                switch(tag[1]) {
                case 'w': fn(window); break;
                default: fn(view_->p__()); break;
                }
                break; }
            }
            break; }
        case 's': {
            slave___* slave;
            switch(tag[1]) {
            case 'c':
                slave = (slave___*)std::stoul(p[i + 1]);
                slave->send__(p[i]);
                break;
            case 'x':
                slave = (slave___*)std::stoul(p[i]);
                slave->stop__();
                delete slave;
                break;
            default: {
                slave = new slave___(thiz);
                int err = slave->init__(p, i, tag[1]);
                if(err) {
                    delete slave;
                    throw "错误" + std::to_string(err);
                } else
                    thiz->add__(std::to_string((unsigned long)slave).c_str(), dunhao, add, env);
                from = p.size();
                break; }
            }
            break; }
        case 'T':
            threads_enter = true;
            break;
        case '1':
            is1 = true;
            view_ = nullptr;
            break;
        case 't': test_1 = tag[1]; break;
        case 'W':
            for(int i2 = std::stoi(p[i]); i2 > 0; i2--)
                thiz->not_block__();
            break;
        }
    });
    if(ret2 != 0) return ret2;
    if(threads_enter) {
        fanqiechaodan___* f = new fanqiechaodan___ {
            by, p, from, ret, add, env, thiz
        };
        gdk_threads_add_idle (idle__, f);
        return 1;
    }
    if(window) {
        ret2 = window->for__(p, from, false, add, env); if(ret2 != 0) return ret2;
        if(view_) {
            ret2 = window->for2__(view_, p, from); if(ret2 != 0) return ret2;
        }
    }
    ret2 = thiz->for__(window, nb1_, view_, p, from, 0, true, false, is1, add, env); if(ret2 != 0) return ret2;
    ret2 = thiz->for__(view_, p, from, by, add, env); if(ret2 != 0) return ret2;
    if(view_) {
        ret2 = view_->for__(p, from, add, env); if(ret2 != 0) return ret2;
    }
    if(ret) {
        ret->insert(ret->end(), p.begin() + from, p.end());
        return 1;
    }
    if(test_1 == '2')
        return 1;
    return thiz->goodbye__(p, from);
}

int fanqiechaodan1__(view___* by, const char* s, rets___ ret, rust_add___ add, void* env, argc___ argc, argv___ argv, main_plugin___* ptr) {
    static main_plugin___* thiz = nullptr;
    if(ptr)
        thiz = ptr;
    if(!s) return 1;
    vec___ p;
    int ret2 = thiz->eval__(s, &p, argc, argv, env);
    if(ret2 != l4___::eval_ok_)
        return ret2;
    size_t from = 0;
    return fanqiechaodan__(by, p, from, ret, add, env, thiz);
}
