#include "semicolon.h"

Semicolon::Semicolon() {
    lhs = 0;
}

Semicolon::Semicolon(Base* left) {
    lhs = left;
}

//always executes right
bool Semicolon::exec() {
    lhs->exec();
    
    return true;
}
