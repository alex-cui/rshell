#include "../header/pipe.h"

Pipe::Pipe() : Command() {}

Pipe::Pipe(Command* prevCmd) : Command() {
	this->prevCmd = prevCmd;
}

void Pipe::exec() {
	pid_t p1, p2;
	int pfd[2];

	if (pipe(pfd) < 0) {
		perror("pipe");
		succeeded = false;
	}

	p1 = fork();

	if (p1 == 0) {
		//child 1 execution
		char* cstr1[prevCmd->getSize() + 1];
	
		for (unsigned i = 0; i < prevCmd->getSize(); ++i) {
			cstr1[i] = prevCmd->getCmd(i);
		}

		cstr1[prevCmd->getSize()] = NULL; //must be null terminated

		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);

		if (execvp(cstr1[0], cstr1) < 0) {
			perror("execvp");
			succeeded = false;
		}
	}
	else if (p1 > 0) {
        //wait for child to finish first then resume
        if (wait(0) < 0) {
            perror("wait");
        }  

		//parent process
		p2 = fork();

		//child 2 execution
		if (p2 == 0) {
			char* cstr2[cmd.size() + 1];

			for (unsigned i = 0; i < cmd.size(); ++i) {
				cstr2[i] = cmd.at(i);
			}
			
			cstr2[cmd.size()] = NULL; // must be null terminated

			close(pfd[1]);
			dup2(pfd[0], STDIN_FILENO);
			close(pfd[0]);

			if (execvp(cstr2[0], cstr2) < 0) {
				perror("execvp");
				succeeded = false;
			}
		}
		else if (p2 > 0) {
			//wait for child to finish first then resume
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
	else {
		perror("fork");
		succeeded = false;
	}
}