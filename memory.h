#ifndef INTERPRETER_MEMORY_H
#define INTERPRETER_MEMORY_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
class memory {
    long memSize;
    unsigned char* mem; //stores bytes read from input file
    void readFromFile(FILE* file);
public:
    int programCounter;
    explicit memory(FILE* file);
    virtual ~memory();
    unsigned char getCurrent(); // get current byte
    char getChar();
    short getShort();
    int getInt();
    float getFloat();

    void printMem();
};

long countFromFile(FILE* file);
#endif //INTERPRETER_MEMORY_H
