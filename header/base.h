#ifndef BASE_H
#define BASE_H

#include <string>

using namespace std;

class Base {
    public:
        Base* lhs; //only for connectors-- commands have no lhs 
        bool succeeded; //remembers past exec that succeeded, don't want to 
			            //exec again to see if it worked
        string id; //mainly to identify AND and OR connector

        virtual void exec() = 0;
};

#endif
