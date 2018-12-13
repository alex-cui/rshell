#include "../header/less.h"

Less::Less() : Command() {}

Less::Less(Command* prevCmd) : Command() {
	this->prevCmd = prevCmd;
}

void Less::exec() {
    pid_t pid;
    char* input = cmd.at(0);
    int fd;
   
    pid = fork();
    
    fflush(0); // flush standard I/O
    if (pid == 0) {
	//child process
	char* cstr[prevCmd->getSize() + 1];

	for (unsigned i = 0; i < prevCmd->getSize(); ++i) {
		cstr[i] = prevCmd->getCmd(i);
	}
	cstr[prevCmd->getSize()] = NULL; //must be null terminated

	fd = open(input, O_RDONLY);
	dup2(fd, STDIN_FILENO); //redirect data in file to stdin
	close(fd);

	if (execvp(cstr[0], cstr) < 0) {
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
