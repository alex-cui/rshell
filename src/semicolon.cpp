#include "../header/semicolon.h"

Semicolon::Semicolon() {
    lhs = 0;
}

Semicolon::Semicolon(Base* left) {
    lhs = left;
}

void Semicolon::exec() {
    succeeded = true;
}
