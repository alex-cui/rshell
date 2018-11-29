#include "../header/precedence.h"

Precedence::Precedence() {
    lhs = 0;
}

void Precedence::addPrecCmd(Base* b) {
    precCmd.push_back(b);
}

void Precedence::exec() {

}

