#include "../header/base.h"

#include "../header/connector.h"
#include "../header/and.h"
#include "../header/or.h"
#include "../header/semicolon.h"

#include "../header/command.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>

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
    vector <Base*> v; //mainly holds connectors but can hold commands
    string input;
    Command* cmd = new Command();
    Base* conn = 0;
    char semicolon[] = ";";
    char pound[] = "#";
    
    while (getline(cin, input)) { 
        char* c = &input.at(0);

        strtok(c, " "); 
       
	//main loop that parses string 
        while (c != 0) {
            if (strpbrk(c, pound) != NULL) {
                if (c[0] == '#') {
                    break;
                } //dont want to add # as command!
                else {
                    c[charIndex(&c[0], pound)] = '\0';
                        
                    cmd->add(c); //add possible command before c
                    break;
                }
            }
            else if (strpbrk(c, semicolon) != NULL) {
		//semicolon should ALWAYS be at the end b/c no space after
                c[charIndex(&c[0], semicolon)] = '\0'; 
                    
                cmd->add(c);
                    
                conn = new Semicolon(cmd);
                v.push_back(conn);
                    
                cmd = new Command(); //reset cmd
            }
            else if (c[0] == '&' && c[1] == '&' && c[2] == '\0') {
                conn = new And(cmd);
                v.push_back(conn);
                
                cmd = new Command();
            }
            else if (c[0] == '|' && c[1] == '|' && c[2] == '\0') {
                conn = new Or(cmd);
                v.push_back(conn);
                
                cmd = new Command();
            }
            else {
                cmd->add(c); //keep building commands as possible flag
            }
             
            c = strtok (0, " ");
        }
        
        if (cmd->hasCommand()) {
            v.push_back(cmd);
        } //check for last command without connector
    
        for (unsigned i = 0; i < v.size(); ++i) {
            if ((v.at(i))->exec() == false) {
                break;
            } //executes as long as connector rules are obeyed
        }

        v.clear(); //clears vector for next loop
        cmd = new Command();
    }
    
    return 0;
}
