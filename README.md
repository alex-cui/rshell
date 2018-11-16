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

If a pound symbol is encountered, the program will check if the word is the pound itself, or if the word consists of it. Either way, it will be parsed accordingly, pushing whatever command that exists into the execution vector,

Lastly, if a semicolon is encountered, the command will simply be pushed into the vector, and start anew.


When the loop is broken by using the special exit command, the program will simply end.## Details
------------

When parsing the string,


## Known Bugs
------------

The only bug we have found so far is when a user enters an invalid command and tries to exit the rshell after, they must type exit twice.

## Authors
------------

Alex Cui and Jacob Halvorson
