/*
 * tag.h
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#ifndef PUB_TAG_H_
#define PUB_TAG_H_

#include "type.h"
#include <functional>
#include <initializer_list>

namespace pub {

class tag___ {
public:
	const char *flag_, *flag2_;
	unsigned argc_;
	const char *rem_ = nullptr;
};

class tags___ {
public:
	std::vector<tag___> a_;
	tags___(std::initializer_list<tag___> a) : a_(a) {}
	char get__(args___ v, std::string &tag, size_t *argc = nullptr, size_t from = 0);
};

/*
try {
} 
catch(std::exception& e) {std::cerr << e.what() << std::endl;}
catch(const char* s) {std::cerr << s << std::endl;}
catch(const std::string& s) {std::cerr << s << std::endl;}
*/
using clpars_fn___ = std::function<void(const std::string&, size_t, size_t, int&)>; 
using clpars_fn2___ = std::function<int()>;
enum {
	clpars_throw_ = 1,
	clpars_skip_ret_no_ = -10,
	clpars_ret_no_ = 0,
	clpars_ret_ = 2,
	clpars_skip_ = -1,
	clpars_ok_ = -20,
};
int clpars__(tags___& tags, args___ p, size_t& from, clpars_fn___ fn, clpars_fn2___ fn2 = []() -> int {return clpars_throw_;});
int clpars_ret_1__(int ret, args___ p, size_t& from);

} /* namespace pub */

#endif /* PUB_TAG_H_ */
