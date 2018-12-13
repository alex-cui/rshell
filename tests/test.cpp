#include "../header/base.h"

#include "../header/connector.h"
#include "../header/and.h"
#include "../header/or.h"

#include "../header/command.h"
#include "../header/test.h"
#include "../header/greater.h"
#include "../header/greaterTwo.h"
#include "../header/less.h"
#include "../header/pipe.h"

#include "../header/parenthesis.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

#include "gtest/gtest.h"

//main function needed for testing
int charIndex(char* temp, char c) {
    int counter = 0;
    
    while (*temp != c && *temp != '\0') {
        temp += 1;
        counter += 1;
    }
    return counter;
}

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
        else if (*c == '<') {
            c = strtok(0, " ");
		
            cmd = new Less(cmd);
            cmd->addCmd(c); //get the destination to take input from
        }
        else if (c[0] == '>' && c[1] != '>') {
            c = strtok(0, " ");

            cmd = new Greater(cmd);

            cmd->addCmd(c); //get the destination to put input into
        }
        else if (c[0] == '>' && c[1] == '>' && c[2] == '\0') {
            c = strtok(0, " ");

            cmd = new GreaterTwo(cmd);

            cmd->addCmd(c); //get the destination to put input into
        }
        else if (c[0] == '|' && c[1] != '|') {
            c = strtok(0, " ");
		
            //saves previous cmd to pipe                    
            cmd = new Pipe(cmd);
            cmd->addCmd(c); //get the destination for redirection
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

vector<Base*> mainFunc(string input) {
    vector <Base*> v;

    Command* cmd = new Command();
    Parenthesis* p = new Parenthesis();

    string test = "test";   

    char* c = 0;

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
        if (c[0] == '(' && c[1] == '\0') {
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
        else if (*c == '<' && c[1] == '\0') {
            c = strtok(0, " ");
    
            cmd = new Less(cmd);
            cmd->addCmd(c); //get the destination to take input from
        }
        else if (*c == '>' && c[1] == '\0') {
            c = strtok(0, " ");

            cmd = new Greater(cmd);

            cmd->addCmd(c); //get the destination to put input into
        }
        else if (c[0] == '>' && c[1] == '>' && c[2] == '\0') {
            c = strtok(0, " ");

            cmd = new GreaterTwo(cmd);

            cmd->addCmd(c); //get the destination to put input into
        }
        else if (*c == '|' && c[1] == '\0') {
            c = strtok(0, " ");
    
            //saves previous cmd to pipe                    
            cmd = new Pipe(cmd);
            cmd->addCmd(c); //get the destination for redirection
        }
        else if (*c == '[' && c[1] == '\0') {
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

    return v;
}


//--------------TESTS--------------
//-----Vector Size Tests-----
TEST(VectorTest, oneCmd) {
    vector <Base*> v = mainFunc("echo A");

    EXPECT_EQ(1, v.size());
}

TEST(VectorTest, twoCmd) {
    vector <Base*> v = mainFunc("echo A && echo B");
    
    EXPECT_EQ(3, v.size());
}

TEST(VectorTest, threeCmd) {
    vector <Base*> v = mainFunc("echo A && echo B || echo C");

    EXPECT_EQ(5, v.size());
}

TEST(VectorTest, fourCmd) {
    vector <Base*> v = mainFunc("echo A && echo B || echo C && echo D");

    EXPECT_EQ(7, v.size());
}

//-----Test hasCommand Function-----
TEST(FuncTest, hasCmd) {
    Command* Cmd = new Command();
    int tVal = 0;
    string input = "echo A\0";
    char* c = &input.at(0);

    Cmd->addCmd(c);

    if (!Cmd->isEmpty()) {
        tVal = 1;
    }

    EXPECT_EQ(1, tVal);	 
}

TEST(FuncTest, noCmd) {
    Command* Cmd = new Command();
    int tVal = 0;

    if (!Cmd->isEmpty()){
        tVal = 1;
    }

    EXPECT_EQ(0, tVal);	
}

//-----Connector Test-----
TEST(ConnectorTest, And) {
    vector <Base*> v = mainFunc("echo A && echo B");

    EXPECT_EQ(3, v.size());
    EXPECT_EQ(v.at(0)->id, "Command"); 
    EXPECT_EQ(v.at(1)->id, "And"); 
    EXPECT_EQ(v.at(2)->id, "Command"); 
}

//-----Flag Test-----
TEST(TestCommandTest, one) {
    Command* cmd = new Command();

    EXPECT_EQ(cmd->getFlag(), 'e');

    cmd->addFlag('l');

    EXPECT_EQ(cmd->getFlag(), 'l');
}

//-----Redirection Tests-----
TEST(RedirectionTest, Greater) {
    vector <Base*> v = mainFunc("cat > CMakeLists.txt");

    EXPECT_EQ(1, v.size());
    EXPECT_EQ(v.at(0)->id, "Greater"); 
}

TEST(RedirectionTest, GreaterTwo) {
    vector <Base*> v = mainFunc("cat >> CMakeLists.txt");

    EXPECT_EQ(1, v.size());
    EXPECT_EQ(v.at(0)->id, "GreaterTwo"); 
}

TEST(RedirectionTest, Less) {
    vector <Base*> v = mainFunc("cat < CMakeLists.txt");

    EXPECT_EQ(1, v.size());
    EXPECT_EQ(v.at(0)->id, "Less"); 
}

TEST(RedirectionTest, Pipe) {
    vector <Base*> v = mainFunc("cat | CMakeLists.txt");

    EXPECT_EQ(1, v.size());
    EXPECT_EQ(v.at(0)->id, "Pipe"); 
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}