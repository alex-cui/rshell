#ifndef SEMICOLON_H
#define SEMICOLON_H

#include "connector.h"

class Semicolon : public Connector {
    public:
        Semicolon();
        Semicolon(Base* left);
        
        bool exec();
};

#endif
