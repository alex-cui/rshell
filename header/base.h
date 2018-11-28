#ifndef BASE_H
#define BASE_H

class Base {
    public:
        Base* lhs; 
        bool succeeded; 
        
        virtual void exec() = 0;
};

#endif
