#include "../header/base.h"

#include "../header/connector.h"
#include "../header/and.h"
#include "../header/or.h"

#include "../header/command.h"
#include "../header/test.h"

#include "../header/precedence.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

//used to find a certain character in the command
int charIndex(char* temp, char c[]) {
    int counter = 0;
    
    while (*temp != *c && *temp != '\0') {
        temp += 1;
        counter += 1;
    }
    return counter;
}

//special loop to parse commands in parenthesis
//very similar to main parsing loop in main
//to encapsulate all commands into one node, we make every subsequent command
//the lhs of Precedence* p
void parse(char* c, Precedence* vec) {
    char semicolon[] = ";";
    char pound[] = "#";
    string test = "test";   
    string ANDsym = "&&";
    string ORsym = "||";
    string openBrack = "[";
    char closeBrack[] = "]";
    char closePrec[] = ")";
    string input = "";

    Command* cmd = new Command();
    Precedence* pre = new Precedence();

    while (strpbrk(c,")") == NULL) {
        if (c[0] == '(') {
            c += 1; //move over 1 from ()

            //nested parenthesis
            parse(c, pre);
        }
        else if (c == test) {
            c = strtok(0, " "); 

            cmd = new Test();

            if ((c[0] == '-') && (c[2] == '\0')) {
                cmd->addFlag(c[1]);
               c = strtok(0, " "); 
            }

            cmd->addCmd(c);
        }
        if (strpbrk(c, "#") != NULL) {
            if (c[0] == '#') {
                return;
            } 
            else {    
                c[charIndex(&c[0], pound)] = '\0';
                    
                cmd->addCmd(c);
                return;
            }
        }
        else if (c == openBrack) {
            c = strtok(0, " "); 

            cmd = new Test();

            if ((c[0] == '-') && (c[2] == '\0')) {
                cmd->addFlag(c[1]);
                c = strtok(0, " "); 
            }

            cmd->addCmd(c); //next should be ]
        }
        else if (strpbrk(c, semicolon) != NULL) {
            c[strlen(c) - 1] = '\0'; 
                    
            cmd->addCmd(c);
            vec->add(cmd);
                    
            cmd = new Command();
        }
        else if (c == ANDsym) {
            if (!vec->isEmpty()) {
                vec->add(pre);
                vec->add(new And(vec));

                vec = new Precedence();
            }
            else {
                vec->add(cmd); //command is completed
                vec->add(new And(cmd));
                    
                cmd = new Command();
            }
        }
        else if (c == ORsym) {
            if (!vec->isEmpty()) {
                vec->add(pre);
                vec->add(new Or(vec));
                
                vec = new Precedence();
            }
            else {
                vec->add(cmd); //command is completed
                vec->add(new Or(cmd));
                    
                cmd = new Command();
            }
        }
        else {
            cmd->addCmd(c);
        }
        c = strtok (0, " ");
    }

    //now get last command
    c[charIndex(&c[0], closePrec)] = '\0';

    // c[strlen(c) - 1] = '\0';
    cmd->addCmd(c);
    vec->add(cmd); //build commands in parentheses
}



int main() {
    vector <Base*> v;

    Command* cmd = new Command();
    Precedence* p = new Precedence();

    char semicolon[] = ";"; //automatically fills in NULL
    char pound[] = "#";
    string test = "test";   
    string ANDsym = "&&";
    string ORsym = "||";
    string openBrack = "[";
    string closeBrack = "]";
    string input = "";
    char *c = 0;

    while (getline(cin, input)) {
        if (input != "") {
            c = &input.at(0);
        }

        strtok(c, " "); 

        //main loop that parses string 
        while (c != 0) {
            if (c[0] == '(') {
                c += 1; //move over 1 from ()

                parse(c, p); //forms precedence class which encapsulates all commands and connectors
            }
            else if (c == test) {
                c = strtok(0, " "); 

                cmd = new Test(); //now will exec() like test

                //add flag if specified, -e otherwise
                if ((c[0] == '-') && (c[2] == '\0')) {
                    cmd->addFlag(c[1]);
                    c = strtok(0, " "); 
                }

                cmd->addCmd(c); //points to same location
            }
            else if (strpbrk(c, pound) != NULL) {
                if (c[0] == '#') {
                    break;
                } //dont want to add # as command!
                else {    
                    c[charIndex(&c[0], pound)] = '\0';
                        
                    cmd->addCmd(c); //add possible command before c
                    break;
                }
            }
            else if (c == openBrack) {
                c = strtok(0, " "); 

                cmd = new Test();

                if ((c[0] == '-') && (c[2] == '\0')) {
                    cmd->addFlag(c[1]);
                    c = strtok(0, " "); 
                }

                cmd->addCmd(c);

                //only 2 differences from test
                while (c != closeBrack) {
                    c = strtok(0, " "); 
                    cmd->addCmd(c);
                }
            }
            else if (strpbrk(c, semicolon) != NULL) {
		        //semicolon should ALWAYS be at the end b/c ALWAYS space after
                c[strlen(c) - 1] = '\0'; 
                    
                cmd->addCmd(c);
                v.push_back(cmd); //command is completed
                    
                cmd = new Command(); //reset cmd
            }
            else if (c == ANDsym) {
                //in case a connector is attached to precedence
                if (!p->isEmpty()) {
                    v.push_back(p);
                    v.push_back(new And(p));

                    p = new Precedence();
                }
                else {
                    v.push_back(cmd); //command is completed
                    v.push_back(new And(cmd));
                    
                    cmd = new Command();
                }
            }
            else if (c == ORsym) {
                //in case a connector is attached to precedence
                if (!p->isEmpty()) {
                    v.push_back(p);
                    v.push_back(new Or(p));

                    p = new Precedence();
                }
                else {
                    v.push_back(cmd); //command is completed
                    v.push_back(new Or(cmd));
                    
                    cmd = new Command();
                }
            }
            else {
                cmd->addCmd(c); //keep building commands as possible flag
            }
            
            c = strtok (0, " ");
        }
        //checks for last command without connector
        if (!cmd->isEmpty()) {
            v.push_back(cmd);         
            cmd = new Command();
        }

        //checks for precedence operator without connector
        if (!p->isEmpty()) {
            v.push_back(p);
        }

        // outputs
        for (unsigned i = 0; i < v.size(); ++i) {
            v.at(i)->exec();

            //if a command failed or connector is false
            while (!(v.at(i)->succeeded) && (v.at(i)->lhs != 0)) {
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

        //reset
        p = new Precedence();
        cmd = new Command();
        v.clear(); 
    }

    return 0;
}
