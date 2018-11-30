#include "../header/precedence.h"

Precedence::Precedence() {
    lhs = 0;
}

void Precedence::add(Base* b) {
    v.push_back(b);
}

bool Precedence::isEmpty() {
    if (v.empty()) {
        return true;
    }
    return false;
}

void Precedence::exec() {
    //then only one command
    for (unsigned i = 0; i < v.size(); ++i) {
            v.at(i)->exec();

            if (v.at(i)->id == "and") {
                if (v.at(i)->lhs->succeeded) {
                    ++i; //should be command

                    v.at(i)->exec();
                    succeeded = v.at(i)->succeeded;
                }
                else {
                    succeeded = false;
                }
            }
            else if (v.at(i)->id == "or") {
                if (v.at(i)->lhs->succeeded) {
                    succeeded = true;
                }
                else {
                    ++i;

                    v.at(i)->exec();
                    succeeded = v.at(i)->succeeded;
                }
            }

            //if a command failed or connector is false
            while (!(v.at(i)->succeeded)) {
                if (v.size() == 1) {
                    break;
                }
                else if (i == (v.size() - 2)) {
                    v.pop_back();
                    break;
                }
                else {
                    i += 2; //moves 2 since next is command
                    v.at(i)->lhs = v.at(i - 2)->lhs;
                    v.at(i)->exec();
                }
            }
        }
}
