#include "memory.h"
memory::memory(FILE* file) {
    programCounter = 0;
    memSize = countFromFile(file);
    mem = new unsigned char[memSize];
    this -> readFromFile(file);

    //debug************
//    for(long lcv = 0; lcv < memSize; lcv++) {
//        std::cout<<int(mem[lcv])<<std::endl;
//    }
    //debug************
}

//read the whole file to an array
void memory::readFromFile(FILE *file) {
    unsigned char temp; // to store one byte read from file
    for(long lcv = 0; lcv < memSize; lcv++) {
        fread(&temp,  sizeof(unsigned char), 1, file);
        mem[lcv] = temp;
    }
}

memory::~memory() {
    delete mem;
}


unsigned char memory::getCurrent() {
    return mem[programCounter];
}



//count size of the byte array from file
//so that the array can be initialized
long countFromFile(FILE* file)
{
    long size;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

//get a character from memory
//From current program point
//When returns, put the PC into the next one
char memory::getChar() {
    return char(mem[programCounter++]);
}

//get a short from memory
//From current program point
//When returns, put the PC into the next one
short memory::getShort() {
    short result = short(mem[programCounter] << 8 |
                        (mem[programCounter + 1]));
    programCounter += 2;
    return result;
}

//get a int from memory
//From current program point
//When returns, put the PC into the next one
int memory::getInt() {
    int result = int(mem[programCounter] << 24 |
                mem[programCounter + 1] << 16 |
                mem[programCounter + 2] << 8 |
                mem[programCounter + 3]);
    programCounter += 4;
    return result;
}

//get a float from memory
//From current program point
//When returns, put the PC into the next one
float memory::getFloat() {
    float result = float(mem[programCounter] << 24 |
                     mem[programCounter + 1] << 16 |
                     mem[programCounter + 2] << 8 |
                     mem[programCounter + 3]);
    programCounter += 4;
    return result;
}

