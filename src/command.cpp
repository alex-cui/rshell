#include "../header/command.h"

Command::Command() {
    testFlag = 'e';
    lhs = 0;
}

void Command::addCmd(char* c) {
    cmd.push_back(c);
}

void Command::addFlag(char f) {
    testFlag = f;
}

bool Command::hasCommand() {
    if (cmd.size() == 0) {
        return false;
    }
    return true;
}

void Command::exec() {    
    string s = cmd.at(0);
    string temp = "exit";

    if (s == temp) {
        exit(0);
    }

    pid_t pid = fork();

    if (pid == 0) { 
        char* cstr[cmd.size() + 1];
	
        for (unsigned i = 0; i < cmd.size(); ++i) {
            cstr[i] = cmd.at(i);
        }

        cstr[cmd.size()] = NULL;

        if ((execvp(cstr[0], cstr)) == -1) {
            perror("execvp");
            succeeded = false;
        }
    }
    else if (pid > 0) { 
        if (wait(0) < 0) {
            perror("wait");
        } 

        succeeded = true;    
    }
    else {
        perror("fork");

        succeeded = false;
    }
}
