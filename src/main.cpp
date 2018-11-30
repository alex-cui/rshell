#include "../header/base.h"

#include "../header/connector.h"
#include "../header/and.h"
#include "../header/or.h"
#include "../header/semicolon.h"

#include "../header/command.h"
#include "../header/test.h"

#include "../header/precedence.h"

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

void parse(char* c, Precedence* p) {
    char semicolon[] = ";";
    char pound[] = "#";
    string test = "test";   
    string ANDsym = "&&";
    string ORsym = "||";
    string openBrack = "[";
    string closeBrack = "]";
    string input = "";

    Connector* conn = 0;
    Command* cmd = new Command();
    Precedence* pre = new Precedence();

    while (c[strlen(c) - 1] != ')') {
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
        else if (c[0] == '(') {
            c = strtok(0, " ");

            while (c[strlen(c) - 1] != ')') {
                parse(c, pre);

                c = strtok(0, " ");
            }

            c[strlen(c) - 1] = '\0';
            cmd->addCmd(c);

            p->add(cmd);
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
        else if (strpbrk(c, semicolon) != NULL) {
            c[strlen(c) - 1] = '\0'; 
                    
            cmd->addCmd(c);
            p->add(cmd);

            conn = new Semicolon(cmd);
            p->add(conn);
                    
            cmd = new Command();
        }
        else if (c == ANDsym) {
            p->add(cmd); 

            conn = new And(cmd);
            p->add(conn);
                
            cmd = new Command();
        }
        else if (c == ORsym) {
            p->add(cmd);

            conn = new Or(cmd);
            p->add(conn);
                
            cmd = new Command();
        }
        else {
            cmd->addCmd(c);
        }

        c = strtok (0, " ");
     }

     //now get last command
     c[strlen(c) - 1] = '\0';
     cmd->addCmd(c);

     p->add(cmd);
}

int main() {
    vector <Base*> v; //holds every command and connector for execution

    Connector* conn = 0;
    Command* cmd = new Command();

    char semicolon[] = ";"; //automatically fills in NULL
    char pound[] = "#";
    string test = "test";   
    string ANDsym = "&&";
    string ORsym = "||";
    string openBrack = "[";
    string closeBrack = "]";
    string input;
    char *c = 0;

    //main loop-- ends when exit is entered
    while (getline(cin, input)) {
        if (input != "") {
            c = &input.at(0);
        }

        strtok(c, " "); 

	//parses the string
        while (c != 0) {
            if (c == test) {
                c = strtok(0, " "); 

                cmd = new Test(); 

		//add flag if specified, else -e
                if ((c[0] == '-') && (c[2] == '\0')) {
                    cmd->addFlag(c[1]);
                    c = strtok(0, " "); 
                }

                cmd->addCmd(c); //test should be one command
            }
            else if (c == openBrack) {
                c = strtok(0, " "); 

                cmd = new Test();

                if ((c[0] == '-') && (c[2] == '\0')) {
                    cmd->addFlag(c[1]);
                    c = strtok(0, " "); 
                }

                cmd->addCmd(c);

		//only difference from test
                while (c != closeBrack) {
                    c = strtok(0, " "); 
                    cmd->addCmd(c);
                }
            }
            else if (strpbrk(c, pound) != NULL) {
		//dont want to add # as command
                if (c[0] == '#') {
                    break;
                }
                else {
                    c[charIndex(&c[0], pound)] = '\0';
                        
                    cmd->addCmd(c); //add possible command before c
                    break;
                }
            }
            else if (strpbrk(c, semicolon) != NULL) {
		//semicolon should ALWAYS be at the end b/c no space after
                c[strlen(c) - 1] = '\0'; 
                    
                cmd->addCmd(c);
                v.push_back(cmd); //command is complete

                conn = new Semicolon(cmd);
                v.push_back(conn); 
                    
                cmd = new Command(); //reset command
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

            c = strtok (0, " "); //keep parsing string
        }

	//checks for last command without connector
        if (cmd->hasCommand()) {
            v.push_back(cmd);         
            cmd = new Command();
        } 

	//output loop
        for (unsigned i = 0; i < v.size(); ++i) {
            v.at(i)->exec();

	//if a command failed or conenctor is false
	//only connectors should have a child
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

        v.clear(); //clears vector for next getline
    }

    return 0;
}
