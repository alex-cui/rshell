#include "../header/command.h"

Command::Command() {
    flag = 'e';
    lhs = 0;
    id = "Command";
}

void Command::addCmd(char* c) {
    cmd.push_back(c);
}

void Command::addFlag(char f) {
    flag = f;
}

int Command::getSize() {
    return cmd.size();
}

char* Command::getCmd(int i) {
    return cmd.at(i);
}

char Command::getFlag() {
    return flag;
}

bool Command::isEmpty() {
    if (cmd.size() == 0) {
        return true;
    }
    return false;
}

void Command::exec() {    
    string temp = "exit";

    //end program if cmd is EXIT
    if (cmd.at(0) == temp) {
        exit(0);
    }

    //pid = Process ID; fork is needed b/c executing a program will
    //cause it to end, so we have a dummy program to do it and be killed 
    //while we keep the main program
    pid_t pid = fork();

    if (pid == 0) { //child
        char* cstr[cmd.size() + 1];
	
	    //copy vector into character array for execvp
        for (unsigned i = 0; i < cmd.size(); ++i) {
            cstr[i] = cmd.at(i);
        }

        cstr[cmd.size()] = NULL; //b/c must be null terminated

        if ((execvp(cstr[0], cstr)) == -1) {
            perror("execvp");
            succeeded = false;
        }
    }
    else if (pid > 0) { //parent
        //wait for child to finish then resume
        if (wait(0) < 0) {
            perror("wait");
        }  

        succeeded = true;    
    }
    else {
        perror("fork"); //need perror otherwise no error message!

        succeeded = false;
    }
}
