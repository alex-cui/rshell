#ifndef PRECEDENCE_H
#define PRECEDENCE_H

#include <iostream>
#include <vector>

#include "base.h"

using namespace std;

class Precedence : public Base {
    protected:
	    vector <Base*> v; //hold commands/connectors inside ()

    public:
        Precedence();
        
        void add(Base* b);
        bool isEmpty();

        virtual void exec();
};

#endif