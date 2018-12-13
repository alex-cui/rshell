#include "../header/greaterTwo.h"

GreaterTwo::GreaterTwo() : Command() {}

GreaterTwo::GreaterTwo(Command* prevCmd) : Command() {
	this->prevCmd = prevCmd;
}

void GreaterTwo::exec() {
	pid_t pid;
	char* output = cmd.at(0);
	int fd;
	
	pid = fork();
	fflush(0);
	
	if (pid == 0) {
		//child process
		char* cstr[prevCmd->getSize() + 1];
		
		for (unsigned i = 0; i < prevCmd->getSize(); ++i) {
			cstr[i] = prevCmd->getCmd(i);
		}
		
		cstr[prevCmd->getSize()] = NULL; //must be null terminated

		fd = open(output,O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		dup2(fd, STDOUT_FILENO);
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
