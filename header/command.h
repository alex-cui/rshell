#ifndef COMMAND_H
#define COMMAND_H

#include "base.h"

#include <string.h>
#include <stdio.h> //needed for perror
#include <stdlib.h>
#include <unistd.h> //execvp
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h> //for test commands

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Command : public Base {
    protected:
        vector <char*> cmd; //accounts for flags
	    char testFlag;
        
    public:
        Command();
        
        void addCmd(char* c);
        void addFlag(char f);
        char getFlag(); //used for testing
        bool isEmpty();
        vector<char*> getCmds();
        virtual void exec();
};

#endif
