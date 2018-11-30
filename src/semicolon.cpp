#include "../header/semicolon.h"

Semicolon::Semicolon() {
    lhs = 0;
    id = "semicolon";
}

Semicolon::Semicolon(Base* left) {
    lhs = left;
    id = "semicolon";
}

//always executes right
void Semicolon::exec() {
    succeeded = true;
}
