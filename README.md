# Assignment 2 -- Rshell

## Installation
--------------
Run these commands to install and run Rshell
```Install Process
$ git clone https://github.com/cs100/assignment-1-team-4.git

$ cd assignment-1-team-4

$ cmake3 .

$ make

$./rshell
```

## Overview
------------
This program will take a string input from a user, and then parse that string checking for three types of flags: &&, ||, and ; and execute commands based on the user input.
After the user enters a string, the program will parse the string using the strtok function in the cstring library. The funtion splits the string up into tokens based on whether a flag or null character was reached. If a connector is reached, the code continues to parse the string looking for commands. If a null character is reached, that is the end of the input. The commands are executed using the system calls: fork, execvp, and waitpid, and error checked these using perror. 
## Known Bugs
------------
The only bug we have found so far is when a user enters an invalid command and tries to exit the rshell after, they must type exit twice.

## Authors
------------
Alex Cui
Jacob Halvorson
