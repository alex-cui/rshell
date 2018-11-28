#ifndef TEST_H
#define TEST_H

#include "command.h"

class Test : public Command {
    public:
        Test();

        virtual void exec();
};

#endif
