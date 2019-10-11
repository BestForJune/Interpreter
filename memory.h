#ifndef INTERPRETER_MEMORY_H
#define INTERPRETER_MEMORY_H

#include <iostream>
#include <cstdio>
class memory {
    int programCounter;
    long memSize;
    unsigned char* mem; //stores bytes read from input file
    void readFromFile(FILE* file);
public:
    explicit memory(FILE* file);
    virtual ~memory();

};

long countFromFile(FILE* file);
#endif //INTERPRETER_MEMORY_H
