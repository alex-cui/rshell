#include "../header/less.h"

Less::Less() : Command() {}

Less::Less(Command* prevCmd) : Command() {
	this->prevCmd = prevCmd;
}

void Less::exec() {
	pid_t pid;

    ifstream inFS;
    ofstream oFS;

    string input;

    inFS.open(cmd.at(0)); //should only be one file
    oFS.open(prevCmd->getCmd(0));

    while (inFS >> input) {
        //now make it as input to prevCmd file
cout << input << "***" << endl;
        oFS << input;
    }
}