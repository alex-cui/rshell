#include "base.h"

#include "connector.h"
#include "and.h"
#include "or.h"
#include "semicolon.h"

#include "command.h"
#include "exit.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

int charIndex(char* temp, char c[]) {
    int counter = -1;
    
    while (*temp != '\0') {
        temp += 1;
        counter += 1;
    }
    return counter;
}

void request(string input) {
    vector <Base*> v;
    int flag = 0;
    Command* cmd = new Command();
    Base* conn = 0;
    char semicolon[] = ";";
    char pound[] = "#";
    
        char* c = &input.at(0);

        strtok(c, " ");
        
        while (c != 0) {
            if (strpbrk(c, pound) != NULL) {
                if (c[0] == '#') {
                    break;
                } 
                else {
                    c[charIndex(&c[0], pound)] = '\0';
                        
                    cmd->add(c);
                    break;
                }
            }
            else if (strpbrk(c, semicolon) != NULL) {
                c[charIndex(&c[0], semicolon)] = '\0'; 
                    
                cmd->add(c);
                    
                conn = new Semicolon(cmd);
                v.push_back(conn);
                    
                cmd = new Command();
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
                cmd->add(c);
            }
             
            c = strtok (0, " ");
        }
        
        if (cmd->hasCommand()) {
            v.push_back(cmd);
        }
    
        for (unsigned i = 0; i < v.size(); ++i) {
            if ((v.at(i))->exec() == false) {
                break;
            }
        }
}

TEST(execIntegrationTest, lsTest) {
  request("ls");

      


  EXPECT_EQ(execvp(
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
