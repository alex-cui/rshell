#include "../header/test.h"

Test::Test() : Command() {}

void Test::exec() {
    const char* temp = cmd.at(0);
    struct stat buffer;
    
    if (stat(temp, &buffer) == -1) {
        // perror("stat"); //-1 on failure
        cout << "(False)" << endl;
        succeeded = false;
    } 
    else {
        if (flag == 'e') {
            cout << "(True)" << endl;

            succeeded = true;
            return;
        }
        else if (flag == 'f') {
            if (S_ISREG(buffer.st_mode)) {
                cout << "(True)" << endl;

                succeeded = true;
                return;
            }
        }
        else if (flag == 'd') {
            if (S_ISDIR(buffer.st_mode)) {
                cout << "(True)" << endl;

                succeeded = true;
                return;
            }
        }
    }
}
