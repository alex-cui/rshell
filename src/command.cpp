#include "command.h"

Command::Command() {}

void Command::add(char* c) {
    cmd.push_back(c);
}

bool Command::hasCommand() {
    if (cmd.size() == 0) {
        return false;
    }
    return true;
}

bool Command::exec() {
    pid_t pid = fork();
    
    if (pid == 0) { 
        char* cstr[cmd.size() + 1];

        for (unsigned i = 0; i < cmd.size(); ++i) {
            cstr[i] = cmd.at(i);
        }
        
        cstr[cmd.size()] = NULL;

        if ((execvp(cstr[0], cstr)) == -1) {
            perror("execvp");
            return false;
        }

        return true;
    }
    else if (pid > 0) {
        if (wait(0) < 0) {
            perror("wait");
        } 
        
        return true;
    }
    else {
        perror("fork"); 
        
        return false;
    }
}
