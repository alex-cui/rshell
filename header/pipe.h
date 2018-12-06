#ifndef PIPE_H
#define PIPE_H

#include "command.h"

class Pipe : public Command {
    public:
        Pipe();

        virtual void exec();
};

#endif