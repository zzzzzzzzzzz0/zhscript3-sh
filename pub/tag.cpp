/*
 * tag.cpp
 *
 *  Created on: 2017年8月5日
 *      Author: zzzzzzzzzzz
 */

#include "tag.h"

namespace pub {

char tags___::get__(args___ p, std::string &tag, size_t *argc, size_t from) {
	if(p.size() <= from)
		return '<';
	for(tag___& i : a_) {
		if(p[from] == i.flag_) {
			if(p.size() - from >= i.argc_) {
				tag = i.flag2_;
				if(argc)
					*argc = i.argc_;
				return 'y';
			}
			return '<';
		}
	}
	return 'n';
}

int clpars__(tags___& tags, args___ p, size_t& from, clpars_fn___ fn, clpars_fn2___ fn2) {
	std::string tag;
	size_t argc;
	int cnt = 0, ret = clpars_ok_;
	for(; from < p.size();) {
		switch(tags.get__(p, tag, &argc, from)) {
		case 'y': {
			size_t i = argc == 0 ? from : from+1, old = from;
			from += argc + 1;
			fn(tag, i, argc, ret);
			cnt++;
			switch(ret) {
			case clpars_throw_:
				from = old;
				break;
			case clpars_skip_ret_no_:
			case clpars_skip_:
				from -= 1;
				break;
			}
			break; }
		case 'n':
			ret = fn2();
			break;
		case '<':
			throw "参数不足";
		}
		clpars_ret_1__(ret, p, from);
		switch(ret) {
		case clpars_skip_ret_no_:
			from += 1;
		case clpars_ret_no_:
			cnt = -cnt;
		case clpars_ret_:
			goto ret;
		case clpars_skip_:
			from += 1;
			break;
		}
	}
	ret:
	return cnt;
}
int clpars_ret_1__(int ret, args___ p, size_t& from) {
	if(from >= p.size())
		return 1;
	switch(ret) {
	case clpars_throw_:
		throw "选项“" + p[from] + "”不支持";
	}
	return 0;
}

} /* namespace pub */
