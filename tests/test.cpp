#include "../header/base.h"

#include "../header/connector.h"
#include "../header/and.h"
#include "../header/or.h"

#include "../header/test.h"
#include "../header/precedence.h"
#include "../header/command.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

#include "gtest/gtest.h"

int charIndex(char* temp, char c[]) {
    int counter = 0;

    while (*temp != *c) {
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

    Command* cmd = new Command();
    Precedence* pre = new Precedence();

    while (c[strlen(c) - 1] != ')') {
        if (c[0] == '(') {
            c += 1; 

            p = new Precedence();
            
            
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
                        cmd = new Command();
        }
        else if (c == ANDsym) {
            if (!p->isEmpty()) {
                p->add(pre);
                p->add(new And(p));

                p = new Precedence();
            }
            else {
                p->add(cmd); 
                p->add(new And(cmd));

                cmd = new Command();
            }
        }
        else if (c == ORsym) {
            if (!p->isEmpty()) {
                p->add(pre);
                p->add(new Or(p));

                p = new Precedence();
            }
            else {
                p->add(cmd); 
                p->add(new Or(cmd));

                cmd = new Command();
            }
        }
        else {
            cmd->addCmd(c);
        }

        c = strtok (0, " ");
    }
    
    
    c[strlen(c) - 1] = '\0';
    cmd->addCmd(c);

    p->add(cmd);
}

int mainFunc(string input, char* &c) {
    vector <Base*> v;

    Command* cmd = new Command();
    Precedence* p = new Precedence();

    char semicolon[] = ";";
    char pound[] = "#";
    string test = "test";   
    string ANDsym = "&&";
    string ORsym = "||";
    string openBrack = "[";
    string closeBrack = "]";
    //char *c = 0;
    
    if (input != "") {
    	c = &input.at(0);
    }

    strtok(c, " ");
    
    while (c != 0) {
            if (c[0] == '(') {
                c += 1; 

                p = new Precedence();

                parse(c, p);
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
                v.push_back(cmd); 

                cmd = new Command(); 
            }
            else if (c == ANDsym) {
                if (!p->isEmpty()) {
                    v.push_back(p);
                    v.push_back(new And(p));
                    p = new Precedence();
                }
                else {
                    v.push_back(cmd); 
                    v.push_back(new And(cmd));

                    cmd = new Command();
                }
            }
            else if (c == ORsym) {
                if (!p->isEmpty()) {
                    v.push_back(p);
                    v.push_back(new Or(p));
                    p = new Precedence();
                }
                else {
                    v.push_back(cmd); 
                    v.push_back(new Or(cmd));

                    cmd = new Command();
                }
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

        
        if (!p->isEmpty()) {
            v.push_back(p);
        }

    

    return v.size();
}
//test if vector get appropriate numbers of commands
TEST(VectorTest, oneCmd) {
    string input = "echo A";
    char* c = 0;
    int vSize = 0;
    vSize = mainFunc(input, c);

    EXPECT_EQ(1, vSize);
}

TEST(VectorTest, twoCmd) {
    string input = "echo A && echo B";
    char* c = 0;
    int vSize = 0;
    vSize = mainFunc(input, c);
    
    EXPECT_EQ(3, vSize);
}

TEST(VectorTest, threeCmd) {
    string input = "echo A && echo B || echo C";
    char* c = 0;
    int vSize = 0;
    vSize = mainFunc(input, c);

    EXPECT_EQ(5, vSize);
}
TEST(VectorTest, fourCmd) {
    string input = "echo A && echo B || echo C && echo D";
    char* c = 0;
    int vSize = 0;
    vSize = mainFunc(input, c);

    EXPECT_EQ(7, vSize);
}

//test hasCommand function
TEST(FuncTest, hasCmd) {
    Command* Cmd = new Command();
    int tVal = 0;
    string input = "echo A\0";
    char* c = &input.at(0);
    Cmd->addCmd(c);
    if (Cmd->hasCommand()) {
	tVal = 1;
    }
    EXPECT_EQ(1, tVal);	 
}
TEST(FuncTest, noCmd) {
    Command* Cmd = new Command();
    int tVal = 0;
    if (Cmd->hasCommand()){
	tVal = 1;
    }
    EXPECT_EQ(0, tVal);	
}
//check And connector
TEST(ConnTest, TAnd) {
    int tVal = 0;
    Command* Cmd = new Command();
    string input = "echo A";
    char* c = &input.at(0);
    Cmd->addCmd(c);
    Connector* conn = new And(Cmd);
   
    if (conn->succeeded) {
	tVal = 1;
    }
    EXPECT_EQ(1, tVal);
}
//command test code from main()
TEST(TestComm, one) {
    int tVal = 0;
    Command* cmd = new Command();
    char c[] = "-e\0";
    if ((c[0] == '-') && (c[2] == '\0')) {
      cmd->addFlag(c[1]);
    }	
    if (cmd->getFlag() == 'e') {
	tVal = 1;
    }
    EXPECT_EQ(1, tVal);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
