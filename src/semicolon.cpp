#include "../header/or.h"

Or::Or() {
    lhs = 0;
}

Or::Or(Base* left) {
    lhs = left;
}

void Or::exec() {    
    if (lhs->succeeded) {
        succeeded = false;
    }
    else { 
        succeeded = true;
    }
}
