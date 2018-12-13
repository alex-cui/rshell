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
#include <fcntl.h> // needed for I/O redirection

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

        int getSize();
        char* getCmd(int i);
        char getFlag(); //used for testing
        
        bool isEmpty();

        virtual void exec();
};

#endif
