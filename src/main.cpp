#include "../header/base.h"

#include "../header/connector.h"
#include "../header/and.h"
#include "../header/or.h"
#include "../header/semicolon.h"

#include "../header/command.h"
#include "../header/test.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

int charIndex(char* temp, char c[]) {
    int counter = -1;
    
    while (*temp != '\0') {
        temp += 1;
        counter += 1;
    }
    return counter;
}

int main() {
    vector <Base*> v;

    Connector* conn = 0;
    Command* cmd = new Command();

    char semicolon[] = ";";
    char pound[] = "#";
    string test = "test";   
    string ANDsym = "&&";
    string ORsym = "||";
    string openBrack = "[";
    string closeBrack = "]";
    string input;
    char *c = 0;

    while (getline(cin, input)) {
        if (input != "") {
            c = &input.at(0);
        }

        strtok(c, " "); 

        while (c != 0) {
            if (c == test) {
                c = strtok(0, " "); 

                cmd = new Test(); 

                if ((c[0] == '-') && (c[2] == '\0')) {
                    cmd->addFlag(c[1]);
                    c = strtok(0, " "); 
                }

                cmd->addCmd(c);
            }
            else if (c == openBrack) {
                c = strtok(0, " "); 

                cmd = new Test();

                if ((c[0] == '-') && (c[2] == '\0')) {
                    cmd->addFlag(c[1]);
                    c = strtok(0, " "); 
                }

                cmd->addCmd(c);

                while (c != closeBrack) {
                    c = strtok(0, " "); 
                    cmd->addCmd(c);
                }
            }
            else if (strpbrk(c, pound) != NULL) {
                if (c[0] == '#') {
                    break;
                }
                else {
                    c[charIndex(&c[0], pound)] = '\0';
                        
                    cmd->addCmd(c); 
                    break;
                }
            }
            else if (strpbrk(c, semicolon) != NULL) {
                c[charIndex(&c[0], semicolon)] = '\0'; 
                    
                cmd->addCmd(c);
                v.push_back(cmd);

                conn = new Semicolon(cmd);
                v.push_back(conn);
                    
                cmd = new Command();
            }
            else if (c == ANDsym) {
                v.push_back(cmd);

                conn = new And(cmd);
                v.push_back(conn);
                
                cmd = new Command();
            }
            else if (c == ORsym) {
                v.push_back(cmd);

                conn = new Or(cmd);
                v.push_back(conn);
                
                cmd = new Command();
            }
            else {
                cmd->addCmd(c);
            }

            c = strtok (0, " ");
        }

        if (cmd->hasCommand()) {
            v.push_back(cmd);         
            cmd = new Command();
        } 

        for (unsigned i = 0; i < v.size(); ++i) {
            v.at(i)->exec();

            while (!(v.at(i)->succeeded)) {
                if (v.size() == 1) {
                    break;
                }
                else if (i == (v.size() - 2)) {
                    v.pop_back();
		    break; 
                }
                else {
                    i += 2;
                    v.at(i)->lhs = v.at(i - 2)->lhs;
                    v.at(i)->exec();
                }
            }
        }

        v.clear();
    }

    return 0;
}
