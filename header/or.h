#ifndef OR_H
#define OR_H

#include "connector.h"

class Or : public Connector {
    public:
        Or();
        Or(Base* left);
        
        virtual bool exec();
};

#endif
