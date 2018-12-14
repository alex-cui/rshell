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


## Guidelines and Info
------------
This program will continuously take a line of input from the user, and then parse that string using strtok, which separates the sentence by whitespace.  It will check if the word is or consists of #, ;, &&, or a || . 

If a connector is encountered, whatever command was constructed will become the child of the connector; and this connector will be pushed into a vector that will later be executed one by one.

If a pound symbol is encountered, the program will check if the word is the pound itself, or if the word consists of it. Either way, it will be parsed accordingly, pushing whatever command that exists before the pound into the execution vector,

If a semicolon is encountered, the command up to the semicolon will simply be pushed into the vector, and start anew. Note that semicolon **must** be followed by a space.

If "test" is encountered, or its symbolic version [ ], we will check the status of the file/directory specified. Possible flags are -e, -f, -d; if no flag is given, the default will be set to -e. The program will return (True) or (False), depending on the file/directory's existence. If the symbolic version is used, spaces **must** separate the symbol from a word, but test may be omitted from the statement.

If a parentheses is encountered, the order of operations is changed. So, we will encapsulate all commands/connectors in the parentheses into one node, then execute as normal. However, the bool returned from the whole statement will depend on the whatever was executed in the node.

If a less than, greater than, double greater than, or pipe symbol is encountered, the commands will need to be properly redirected. We create a new command accordingly and encapsulate the previous command into the new command object to handle the redirection.

When the loop is broken by using the special exit command, the program will simply end.


## Execution 
------------
Normal commands will be executed by using execvp. We will first make a fork to duplicate the program. We will check the PID as the child program has a PID of 0, and the parent program has a PID of greater than 0. We will execute the command only in the child program, as a program ends when a system call is used. We error check by using perror after each system call, as it will not give any error message without it.

Both connectors will be executed by returning a bool based on the last command's success. 

The test command will be executed by checking the flag and then running the stat() function.

The Precedence class will be executed by executing all commands/connectors within it, and then returning a bool based on the overall sucess.

The redirection classes will be executed by holding a pointer to the previous command and utilizing the dup2 and pipe functions to redirect to standard input and output.


## Known Bugs
------------

The bug that still remains is the exit bug, where after encountering a failed command, you must type "exit" for the amount of failed commands, + 1. The reason for this is unknown.


## Authors
------------

Alex Cui and Jacob Halvorson
