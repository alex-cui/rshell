#ifndef LESS_H
#define LESS_H

#include "command.h"

class Less : public Command {
    protected:
	    Command* prevCmd;

    public:
        Less();
	    Less(Command* prev);

        virtual void exec();
};

#endif