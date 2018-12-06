#ifndef GREATER_H
#define GREATER_H

#include "command.h"

class Greater : public Command {
    public:
        Greater();

        virtual void exec();
};

#endif