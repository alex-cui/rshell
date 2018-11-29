#include "../header/semicolon.h"

Semicolon::Semicolon() {
    lhs = 0;
}

Semicolon::Semicolon(Base* left) {
    lhs = left;
}

//always executes right
void Semicolon::exec() {
    succeeded = true;
}
