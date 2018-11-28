#include "../header/base.h"

#include "../header/connector.h"
#include "../header/and.h"
#include "../header/or.h"
#include "../header/semicolon.h"

#include "../header/command.h"

#include "gtest/gtest.h"

int charIndex(char* temp, char c[]) {
    int counter = -1;
    
    while (*temp != '\0') {
        temp += 1;
        counter += 1;
    }
    return counter;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
