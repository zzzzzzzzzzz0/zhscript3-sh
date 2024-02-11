#pragma once
#include "../pub/tag.h"
#include "../pub/widget.h"
#include "../pub/type.h"
#include "../../zhscript/gjke4/rust.h"

namespace plugin {

class view___ : public widget___ {
	public:
	void *p_;

	virtual const char* path__() = 0;

	virtual void open__(const std::string& arg1, const std::string& arg2) = 0;

	virtual int for__(args___ args, size_t& from, rust_add___ add, void* env) = 0;
	virtual const char* plugin_id__() = 0;
	virtual void on_close__() {}
	virtual bool can_close__() {return true;}
	virtual bool yuxiangrousi__() {return false;}

	bool need_focus_;
	void focus__() {
		gtk_widget_grab_focus(hr_);
	}
};

class pub___ {
	public:
	using fn___ = std::function<void()>;
	using fn_b___ = std::function<bool()>;
	using fn__s___ = std::function<void(const std::string&)>;

	virtual int clpars1__(pub::tags___&, args___, size_t&, pub::clpars_fn___, pub::clpars_fn2___) = 0;
	int clpars__(pub::tags___ tags, args___ v, size_t& from, pub::clpars_fn___ fn, pub::clpars_fn2___ fn2 = []() {return pub::clpars_ret_no_;}) {
		return clpars1__(tags, v, from, fn, fn2);
	}
	virtual void clpars_pr__(pub::tags___&, args___, const std::string&) = 0;

	/*virtual void clpars2__(
		//std::vector<std::string[2]> a,
		std::string a[][2], size_t len,
		const std::string& s, clpars2_fn___ fn) = 0;*/
	virtual void clpars2_sou__(const std::string&, fn__s___) = 0;

	virtual int eval__(const char*, rets___ ret = nullptr, argc___ argc = 0, argv___ argv = nullptr, void* env = nullptr) = 0;
	virtual int eval__(const char*, args___, rets___ ret = nullptr, void* env = nullptr) = 0;

	virtual void pr__(rets2___, const std::string& s = "", const std::string& s2 = "", size_t end = SIZE_MAX) = 0;

	virtual int fanqiechaodan__(view___*, const std::string&, rets___ ret = nullptr, argc___ argc = 0, argv___ argv = nullptr, void* env = nullptr) = 0;
	virtual int fanqiechaodan2__(view___*, const std::string&, args___, rets___ ret = nullptr, void* env = nullptr) = 0;
	virtual int fanqiechaodan3__(view___*, vec___&, rets___ ret = nullptr, void* env = nullptr) = 0;
	virtual int fanqiechaodan3_ic__(view___*, vec___&, rets___ ret = nullptr, void* env = nullptr) = 0;
	virtual void add__(const char* s, bool& dunhao, rust_add___ add, void* env) = 0;

	virtual GtkWidget *pack__(plugin::view___*, plugin::view___*, int) = 0;
	virtual int main_eval__(args___, rets___ ret = nullptr, void* env = nullptr) = 0;
	virtual bool is_focus__(plugin::view___*) = 0;
	virtual void not_block__() = 0;
	virtual bool is_quit__() = 0;
	virtual void get_sel__(fn___ f1, bool& dunhao, rust_add___ add, void* env) = 0;
	virtual bool starts_with(const std::string& s, const std::string& s2) = 0;
	virtual bool ends_with(const std::string& s, const std::string& s2) = 0;
	virtual void op__(const std::string &s2, char c, std::string& s) = 0;
	virtual void read_symlink(const std::string& path, std::string& ret) = 0;
	virtual void replace_filename(const std::string& path, const char* name, std::string& ret) = 0;
	virtual bool exist_d__(const std::string& path) = 0;
	virtual bool exist_f__(const std::string& path) = 0;
	virtual void perms__(const std::string& filename, fn_b___ f1) = 0;
	//if(std::all_of(s.begin(), s.end(), [](char c) {return isdigit(c);})) {
};

class base___ {
	public:
	virtual view___* new__(const std::string& arg1, const std::string& arg2) = 0;
	virtual const char* id__() = 0;

	virtual int for__(args___ args, size_t& from, rust_add___ add, void* env) = 0;
};

}
