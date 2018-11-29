#include "../header/or.h"

Or::Or() {
    lhs = 0;
}

Or::Or(Base* left) {
    lhs = left;
}

//executes right if left fails
void Or::exec() {    
    if (lhs->succeeded) {
        succeeded = false;
    }
    else { 
        succeeded = true;
    }
}
