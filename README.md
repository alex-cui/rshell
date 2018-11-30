# Assignment 2 -- Rshell

## Installation
------------

Run these commands to install and run Rshell
```Install Process
$ git clone https://github.com/cs100/assignment-1-team-4.git

$ cd assignment-1-team-4

$ cmake3 .

$ make

$ ./rshell
```

## Overview
------------

This program will continuously take a line of input from the user, and then parse that string using strtok, which separates the sentence by whitespace.  It will check if the word is or consists of #, ;, &&, or a || . 

If a connector is encountered, whatever command was constructed will become the child of the connector; and this connector will be pushed into a vector that will later be executed one by one.

If a pound symbol is encountered, the program will check if the word is the pound itself, or if the word consists of it. Either way, it will be parsed accordingly, pushing whatever command that exists before the pound into the execution vector,

Lastly, if a semicolon is encountered, the command will simply be pushed into the vector, and start anew.

Every command will be executed by using execvp. We will first make a fork to duplicate the program. We will check the PID as the child program has a PID of 0, and the parent program has a PID of greater than 0. We will execute the command only in the child program, as a program ends when a system call is used. We error check by using perror after each system call, as it will not give any error message without it.

When the loop is broken by using the special exit command, the program will simply end.

When 



## Known Bugs
------------

The bug that still remains is the exit bug, where after encountering a failed command, you must type "exit" for the amount of failed commands, + 1. The reason for this is unknown.

## Authors
------------

Alex Cui and Jacob Halvorson
