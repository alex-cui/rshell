#include "../header/test.h"

Test::Test() {
    testFlag = 'e';
    lhs = 0;
}

void Test::exec() {
    const char* temp = cmd.at(0);
    struct stat buffer;
    
    if (stat(temp, &buffer) == -1) {
        perror("stat"); //-1 on failure

        succeeded = false;
    } 
    else {
        if (testFlag == 'e') {
            cout << "(True)" << endl;

            succeeded = true;
            return;
        }
        else if (testFlag == 'f') {
            if (S_ISREG(buffer.st_mode)) {
                cout << "(True)" << endl;

                succeeded = true;
                return;
            }
        }
        else if (testFlag == 'd') {
            if (S_ISDIR(buffer.st_mode)) {
                cout << "(True)" << endl;

                succeeded = true;
                return;
            }
        }
        
        cout << "(False)" << endl;
        succeeded = true; //bc still executed correctly just false
    }
}
