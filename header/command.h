#ifndef COMMAND_H
#define COMMAND_H

#include "base.h"

#include <string.h>
#include <stdio.h> //needed for perror
#include <stdlib.h>
#include <unistd.h> //execvp
#include <sys/types.h>
#include <sys/wait.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Command : public Base {
    protected:
        vector <char*> cmd; //accounts for flags

    public:
        Command();
        
        void add(char* c);
        bool hasCommand();
        virtual bool exec();
};

#endif
