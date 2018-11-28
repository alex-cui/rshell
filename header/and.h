#ifndef AND_H
#define AND_H

#include "connector.h"

class And : public Connector {
    public:
        And();
        And(Base* left);
        
        virtual void exec();
};

#endif
