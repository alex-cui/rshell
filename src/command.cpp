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
    } //exit if command is "exit"; still obeys connector rules b/c of main!
    
    //pid = Process ID; fork is needed because executing a program will 
    //cause it to end, so we have a dummy program to do it and be killed
    //while we keep the main program
    pid_t pid = fork();

    if (pid == 0) { //child
        s = cmd.at(0);

        char* cstr[cmd.size() + 1];
	
	//copy vector into character array
        for (unsigned i = 0; i < cmd.size(); ++i) {
            cstr[i] = cmd.at(i);
        }

        cstr[cmd.size()] = NULL; //b/c must be null terminated

        if ((execvp(cstr[0], cstr)) == -1) {
            perror("execvp");

            return false;
        }

        return true;
    }
    else if (pid > 0) { //parent
        if (wait(0) < 0) {
            perror("wait");
        } //wait for child to finish then resume 
	
        return true;
    }
    else {
        perror("fork"); //otherwise there's no error message!
        
        return false;
    }
}
