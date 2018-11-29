#include "../header/and.h"

And::And() {
    lhs = 0;
}

And::And(Base* left) {
    lhs = left;
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
