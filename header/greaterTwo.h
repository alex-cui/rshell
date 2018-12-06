#ifndef GREATERTWO_H
#define GREATERTWO_H

#include "command.h"

class GreaterTwo : public Command {
    public:
        GreaterTwo();

        virtual void exec();
};

#endif