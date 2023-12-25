#pragma once
#include "type.h"
#include <dlfcn.h>
#include "fs.h"

class dl___ {
	private:
	void* hl_ = nullptr;
	
	protected:
	bool err__() {
		char *err = dlerror();
		if(err)
			err_ = err;
		else
			err_.clear();
		return !err_.empty();
	}

	public:
	~dl___() {
		if(hl_) {
			int eret = dlclose(hl_);
			hl_ = nullptr;
		}
	}

	std::string err_;
	bool open__(const std::string& path) {
		hl_ = dlopen(path.c_str(), RTLD_LOCAL | RTLD_LAZY);
		if(err__()) return false;
		return true;
	}
	void* sym__(const char* name) {return dlsym(hl_, name);}
};

class l4___ : public dl___ {
	public:
	class erret___ {
		public:
		int i_ = 0;
		std::string s_, s2_;
		int is_quit_ = 0;
	};
	erret___ erret_;

	private:
	using eval___ = bool (*)(const char*, bool, argc___, argv___, argc___, void*,
		void (*)(const char*, rets___), rets___, void (*)(int, const char*, const char*, int, erret___*), erret___*);
	eval___ eval_ = nullptr;
	//using eval2___ = int (*)(const char*, bool, argc___, va_list, void (*)(const char*, rets___), rets___);
	//eval2___ eval2_ = nullptr;
	static void ret__(const char* s, rets___ ret) {
		ret->push_back(s);
	}
	static void erret__(int i, const char* s, const char* s2, int is_quit, erret___* ret) {
		ret->i_ = i;
		ret->s_ = s;
		ret->s2_ = s2;
		ret->is_quit_ = is_quit;
	}

	public:
	fs::path path_;
	using path2___ = void(*)(const char*);
	path2___ path2_ = nullptr;
	using dbg_bp2___ = bool(*)(const char*);
	dbg_bp2___ dbg_bp2_ = nullptr;
	using true___ = bool(*)(const char*);
	true___ true_ = nullptr;

	bool open__(const char* arg0, const char* soname, vec___& paths2) {
		fs::path path1 = arg0;
		vec___ paths;
		auto absymlnk = [](const fs::path& path) {
			fs::path path2 = fs::read_symlink(path);
			if(path2.is_relative())
				path2 = path.parent_path().string() + '/' + path2.string();
			return path2;
		};
		for(;;) {
			paths.push_back(path1);
			paths2.push_back(path1);
			if(!fs::exists(path_)) {
				path_ = path1;
				path_.replace_filename(soname);
				fs::path path2 = path_;
				for(;fs::is_symlink(path2);) {
					path2 = absymlnk(path2);
					paths.push_back(path2);
				}
			}
			if(!fs::is_symlink(path1)) break;
			path1 = absymlnk(path1);
		}

		if(!dl___::open__(path_)) return false;
		eval_ = (eval___)sym__("hello__");
		if(err__()) return false;
		/*eval2_ = (eval2___)sym__("hello2__");
		if(err__()) return false;*/
		true_ = (true___)sym__("true__");
		if(err__()) return false;
		dbg_bp2_ = (dbg_bp2___)sym__("c_dbg_bp2__");
		//if(err__()) return false;
		path2_ = (path2___)sym__("c_path__");
		if(err__()) return false;
		for(auto& i : paths)
			path2_(i.c_str());
		return true;
	}

	enum {
		eval_quit_ = 1,
		eval_continue_ = 2,
		eval_break_ = 3,
		eval_ok_ = -1,
	};
	bool eval__(const char* s, bool src_is_file = false, argc___ argc = 0, argv___ argv = nullptr, argc___ from = 0,
	void* env = nullptr, rets___ ret = nullptr) {
		return eval_(s, src_is_file, argc, argv, from, env, ret__, ret, erret__, &erret_);
	}
	/*int eval__(const char* s, bool src_is_file, rets___ ret, argc___ argc, ...) {
		va_list argv;
		va_start(argv, argc);
		int err = eval2_(s, src_is_file, argc, argv, ret__, ret);
		va_end(argv);
		return err;
	}*/
};
