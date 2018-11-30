#include "../header/and.h"

And::And() {
    lhs = 0;
    id = "and";
}

And::And(Base* left) {
    lhs = left;
    id = "and";
}

//executes right if left succeeds
void And::exec() {    
    if (lhs->succeeded) {
        succeeded = true;
    }
    else {
        succeeded = false;
    }
}
