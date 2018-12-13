#include "../header/base.h"

#include "../header/connector.h"
#include "../header/and.h"
#include "../header/or.h"

#include "../header/command.h"
#include "../header/test.h"
#include "../header/greater.h"
// #include "../header/greaterTwo.h"
#include "../header/less.h"
#include "../header/pipe.h"

#include "../header/parenthesis.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

//used to find a certain character in the command
int charIndex(char* temp, char c) {
    int counter = 0;
    
    while (*temp != c && *temp != '\0') {
        temp += 1;
        counter += 1;
    }
    return counter;
}

//special loop to parse commands in parenthesis
//very similar to main parsing loop in main
//to encapsulate all commands into one node, we make every subsequent command
//the lhs of Parenthesis* p
void parse(char* c, Parenthesis* inside, int skip) {
    string test = "test";   
    string input = "";

    Command* cmd = new Command();
    Parenthesis* pre = new Parenthesis();

    while (strpbrk(c,")") == NULL) {
        if (strpbrk(c, "#") != NULL) {
            if (c[0] == '#') {
                return;
            } 
            else {    
                c[charIndex(&c[0], '#')] = '\0';
            }
        }
        if (strpbrk(c, ";") != NULL) {
            c[strlen(c) - 1] = '\0'; 
        }

        if (c[0] == '(') {
            c += 1; //move over 1 from ()

            //nested parenthesis
            parse(c, pre, skip);
            c += skip; //idk
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
        else if (*c == '[') {
            c = strtok(0, " "); 

            cmd = new Test();

            if ((c[0] == '-') && (c[2] == '\0')) {
                cmd->addFlag(c[1]);
                c = strtok(0, " "); 
            }

            cmd->addCmd(c); //next should be ]

            //only 2 differences from test
            while (*c != ']') {
                c = strtok(0, " "); 
                cmd->addCmd(c);
            }
        }
        else if (c[0] == '&' && c[1] == '&' && c[2] == '\0') {
            if (!inside->isEmpty()) {
                inside->add(pre);
                inside->add(new And(inside));

                inside = new Parenthesis();
            }
            else {
                inside->add(cmd); //command is completed
                inside->add(new And(cmd));
                    
                cmd = new Command();
            }
        }
        else if (c[0] == '|' && c[1] == '|' && c[2] == '\0') {
            if (!inside->isEmpty()) {
                inside->add(pre);
                inside->add(new Or(inside));
                
                inside = new Parenthesis();
            }
            else {
                inside->add(cmd); //command is completed
                inside->add(new Or(cmd));
                    
                cmd = new Command();
            }
        }
        else {
            cmd->addCmd(c);
        }

        skip += strlen(c - 1);
        c = strtok (0, " ");
    }

    //now get last command
    c[charIndex(&c[0], ')')] = '\0';
    cmd->addCmd(c);

    inside->add(cmd); //build commands in parentheses
}



int main() {
    vector <Base*> v;

    Command* cmd = new Command();
    Parenthesis* p = new Parenthesis();

    string test = "test";   
    string input = "";
    char *c = 0;

    //while quit when user puts "exit" (still obey connector rules)
    while (getline(cin, input)) {
        //checks for empty input
        if (input != "") {
            c = &input.at(0);
        }

        strtok(c, " "); 

        //main loop that parses string 
        while (c != 0) {
            //for key words could be ANYWHERE
            if (strpbrk(c, "#") != NULL) {
                if (c[0] == '#') {
                    break;
                } //dont want to add # as command!
                else {    
                    //essentially cuts off everything after the #
                    c[charIndex(&c[0], '#')] = '\0';
                }
            }
            if (strpbrk(c, ";") != NULL) {
		        //semicolon should ALWAYS be at the end b/c ALWAYS space after
                c[strlen(c) - 1] = '\0'; 
            }
            
            //for when all of c is the key word
            if (c[0] == '(') {
                c += 1; //move over 1 from (

                parse(c, p, 0); //forms precedence class which encapsulates all commands and connectors
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
            else if (*c == '<') {
                c = strtok(0, " ");
		
                cmd = new Less(cmd);
                cmd->addCmd(c); //get the destination to take input from
            }
            else if (*c == '>') {
                c = strtok(0, " ");

                cmd = new Greater(cmd);

                cmd->addCmd(c); //get the destination to put input into
            }
            else if (c[0] == '>' && c[1] == '>' && c[2] == '\0') {
                c = strtok(0, " ");
            }
            else if (c[0] == '|' && c[1] != '|') {
                c = strtok(0, " ");
		
                //saves previous cmd to pipe                    
                cmd = new Pipe();
                cmd->addCmd(c); //get the destination for redirection
            }
            else if (*c == '[') {
                c = strtok(0, " "); 

                cmd = new Test();

                if ((c[0] == '-') && (c[2] == '\0')) {
                    cmd->addFlag(c[1]);
                    c = strtok(0, " "); 
                }

                cmd->addCmd(c);

                //only 2 differences from test
                while (*c != ']') {
                    c = strtok(0, " "); 
                    cmd->addCmd(c);
                }
            }
            else if (c[0] == '&' && c[1] == '&' && c[2] == '\0') {
                //in case a connector is attached to precedence
                if (!p->isEmpty()) {
                    v.push_back(p);
                    v.push_back(new And(p));

                    p = new Parenthesis();
                }
                else {
                    v.push_back(cmd); //command is completed
                    v.push_back(new And(cmd));
                    
                    cmd = new Command();
                }
            }
            else if (c[0] == '|' && c[1] == '|' && c[2] == '\0') {
                //in case a connector is attached to parentheses
                if (!p->isEmpty()) {
                    v.push_back(p);
                    v.push_back(new Or(p));

                    p = new Parenthesis();
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
        }

        //checks for parentheses operator without connector
        if (!p->isEmpty()) {
            v.push_back(p);
        }

        //outputs
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
        p = new Parenthesis();
        cmd = new Command();
        v.clear(); 
    }

    return 0;
}
