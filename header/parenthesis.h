#ifndef PARENTHESIS_H
#define PARENTHESIS_H

#include <iostream>
#include <vector>

#include "base.h"

using namespace std;

class Parenthesis : public Base {
    protected:
	    vector <Base*> v; //hold commands/connectors inside ()

    public:
        Parenthesis();
        
        void add(Base* b);
        bool isEmpty();

        virtual void exec();
};

#endif