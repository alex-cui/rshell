#ifndef PRECEDENCE_H
#define PRECEDENCE_H

#include <iostream>

#include "base.h"

using namespace std;

class Precedence : public Base {
    protected:
	vector <Base*> precCmd; //hold commands/connectors inside ()
    public:
        Precedence();
        
        void addPrecCmd(Base* b);
        
        virtual void exec();
};
#endif

