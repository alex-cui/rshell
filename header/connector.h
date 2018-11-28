#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <iostream>

#include "base.h"

using namespace std;

class Connector : public Base {
    public:
        Connector();
        Connector(Base* left);

        Base* getLeft();
        void swapLeft(Base* left);
        
        virtual void exec() = 0;
};

#endif
