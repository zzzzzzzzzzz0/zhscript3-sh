#pragma once
#include "../../plugin/pub.h"

using page_vs___ = std::vector<plugin::view___*>;
using page_vs1___ = const page_vs___&;
using page_vs2___ = page_vs___*;

class views___ {
    public:
	page_vs___ a_;

    plugin::view___* find__(std::function<bool(plugin::view___*)> fn) {
        auto i = std::find_if(a_.begin(), a_.end(), fn);
        return i == a_.end() ? nullptr : *i;
    }
    void del__(plugin::view___* v) {
        a_.erase(std::find(a_.begin(), a_.end(), v));
    }
};