#include "and.h"

And::And() {
    lhs = 0;
}

And::And(Base* left) {
    lhs = left;
}

//executes right if left succeeds
bool And::exec() {
    if (lhs->exec()) {
        return true;
    }
    return false;
}
