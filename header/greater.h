#ifndef GREATER_H
#define GREATER_H

#include "command.h"

class Greater : public Command {
    protected:
	    Command* prevCmd;

    public:
        Greater();
        Greater(Command* prev);

        virtual void exec();
};

#endif