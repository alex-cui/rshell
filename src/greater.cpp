#include "../header/greater.h"

Greater::Greater() : Command() {}

Greater::Greater(Command* prevCmd) : Command() {
	this->prevCmd = prevCmd;
}

//opposite of less
void Greater::exec() {
    pid_t pid;
    int fd;
   
    pid = fork();
    
    fflush(0); // flush standard I/O

    //child process
    if (pid == 0) {
        //copies vector into cstr
        char* cstr[prevCmd->getSize() + 1];
        for (unsigned i = 0; i < prevCmd->getSize(); ++i) {
            cstr[i] = cmd.at(i);
        }
        cstr[cmd.size()] = NULL; //must be null terminated

        fd = open(prevCmd->getCmd(0), O_RDONLY); //should only be the first cmd
        dup2(fd, STDIN_FILENO);
        close(fd);
        
        if (execvp(cstr[0], cstr) < 0) {
            perror("execvp");
            succeeded = false;
        }
    }
    else if (pid > 0) {
        //parent process
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