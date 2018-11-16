#ifndef BASE_H
#define BASE_H

class Base {
    public:
	//exec() is required by all inherited classes as every command or
	//connector in the command line will execute some sort of action
        virtual bool exec() = 0;
};

#endif
