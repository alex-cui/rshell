#include "../header/or.h"

Or::Or() {
    lhs = 0;
    id = "or";
}

Or::Or(Base* left) {
    lhs = left;
    id = "or";
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
