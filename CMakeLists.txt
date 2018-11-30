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
    src/precedence.cpp
)

ADD_EXECUTABLE(test
    src/connector.cpp
    src/and.cpp
    src/or.cpp
    src/command.cpp
    src/precedence.cpp
    src/test.cpp
    tests/test.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
