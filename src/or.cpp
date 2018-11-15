#include "or.h"

Or::Or() {
    lhs = 0;
}

Or::Or(Base* left) {
    lhs = left;
}

//executes right if left FAILS
bool Or::exec() {
    if (lhs->exec()) {
        return false;
    }
    return true;
}
