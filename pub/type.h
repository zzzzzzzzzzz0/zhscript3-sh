#pragma once
#include <string>
#include <vector>

using argc___ = uint32_t;
using argv___ = const char* const*;

using vec___ = std::vector<std::string>;
using args___ = const vec___&;
using rets___ = vec___*;
using rets2___ = const vec___*;

enum {
	append_page_ = -1,
	after_curr_page_ = -10,
	before_curr_page_ = -11,
};
