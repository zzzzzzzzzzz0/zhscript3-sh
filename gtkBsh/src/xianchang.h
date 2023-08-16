#pragma once
#include "../../plugin/pub.h"

namespace xianchang {
    class item___ {
        public:
		GtkWidget *nb1_; GtkNotebook *nb_;
		plugin::view___ *view_, *by_;
    };

    class list___ {
        std::vector<item___*> a_;
        public:
        ~list___() {
        	for(size_t idx = 0; idx < a_.size();) {
        		delete a_[idx++];
        	}
        }
        
        void push__(item___* i) {
            a_.push_back(i);
        }
        void pop__(GtkWidget *&nb1_, GtkNotebook *&nb_, plugin::view___ *&view_, plugin::view___ *&by_) {
            size_t n = a_.size();
            if(n > 0) {
                item___* d = a_[--n];
                nb1_ = d->nb1_;
                nb_ = d->nb_;
                view_ = d->view_;
                by_ = d->by_;
                delete d;

                a_.pop_back();
            }
        }
    };
}