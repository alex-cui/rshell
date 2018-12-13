#include "../header/and.h"

And::And() {
    lhs = 0;
    id = "And";
}

And::And(Base* left) {
    lhs = left;
    id = "And";
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
