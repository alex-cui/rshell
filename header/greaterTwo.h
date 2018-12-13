#ifndef GREATERTWO_H
#define GREATERTWO_H

#include "command.h"

class GreaterTwo : public Command {
    protected:
	    Command* prevCmd;

    public:
        GreaterTwo();
	    GreaterTwo(Command* prev);

        virtual void exec();
};

#endif