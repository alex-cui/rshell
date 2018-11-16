#include "../header/command.h"

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
    int exitFlag = 0;
    const char* ex = "exit";
    string s = cmd.at(0);
    
    if (s == ex) {
        exit(0);
    } //exit if command is "exit"
    
    //pid = Process ID
    pid_t pid = fork();

    if (pid == 0) { //child
        s = cmd.at(0);

        char* cstr[cmd.size() + 1];
	
	//copy vector into character array
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
    else if (pid > 0) { //parent
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
