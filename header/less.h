#ifndef LESS_H
#define LESS_H

#include "command.h"

class Less : public Command {
    public:
        Less();

        virtual void exec();
};

#endif