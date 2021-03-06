#ifndef PIPE_H
#define PIPE_H

#include "command.h"

class Pipe : public Command {
    protected:
	    Command* prevCmd;

    public:
        Pipe();
	    Pipe(Command* prev);

        virtual void exec();
};

#endif