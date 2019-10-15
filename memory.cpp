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