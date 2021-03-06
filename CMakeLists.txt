CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(rshell
    src/main.cpp
    src/connector.cpp
    src/and.cpp
    src/or.cpp
    src/command.cpp
    src/test.cpp
    src/parenthesis.cpp
    src/greater.cpp
    src/less.cpp
    src/pipe.cpp
    src/greaterTwo.cpp
)

ADD_EXECUTABLE(test
    tests/test.cpp
    src/connector.cpp
    src/and.cpp
    src/or.cpp
    src/command.cpp
    src/test.cpp
    src/parenthesis.cpp
    src/greater.cpp
    src/less.cpp
    src/pipe.cpp
    src/greaterTwo.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
