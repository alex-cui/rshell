#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "base.h"

using namespace std;

class Connector : public Base {
    protected:
        Base* lhs; 

    public:
        Connector();
        Connector(Base* left);

        virtual bool exec() = 0;
};

#endif
