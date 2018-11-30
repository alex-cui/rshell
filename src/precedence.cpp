#include "../header/precedence.h"

Precedence::Precedence() {
    lhs = 0;
}

void Precedence::add(Base* b) {
    v.push_back(b);
}

void Precedence::exec() {
    //then only one command
    if (v.size() == 1) {
	v.at(0)->exec();
    }
    else {
    }
}
