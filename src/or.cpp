#include "../header/or.h"

Or::Or() {
    lhs = 0;
    id = "Or";
}

Or::Or(Base* left) {
    lhs = left;
    id = "Or";
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
