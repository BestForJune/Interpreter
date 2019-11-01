/******************************************************************************
 * File name:   memory.cpp
 * Description: This file contains mmeory class which stores all the instruction
 *              read from file.
 * Programmers: Zhengsen Fu fu216@purdue.edu
 *              Yanjun Chen chen2620@purdue.edu
 ******************************************************************************/

#include "memory.h"
#include <cstring>
#include <iostream>

/******************************************************************************
 * Function:    memory class constructor
 * Description: Constructor sets program counter to 0 and count the number of
 *              instructions in the file and initialize the memory arr
 * Parameters:  FILE* file // input instruction file pointer
 * Return:      void
 ******************************************************************************/
memory::memory(FILE* file) {
    programCounter = 0;
    memSize = countFromFile(file); //total length of the instruction
    mem = new unsigned char[memSize];
    this -> readFromFile(file);

    //debug************
//    for(long lcv = 0; lcv < memSize; lcv++) {
//        std::cout<<int(mem[lcv])<<std::endl;
//    }
    //debug************
}

/******************************************************************************
 * Function:    readFromFile
 * Description: read instructions byte by byte into memory arr
 * Parameters:  memory* this // this point of the memory object
 *              FILE* file   // input instruction file
 * Return:      void
 ******************************************************************************/
void memory::readFromFile(FILE *file) {
    unsigned char temp; // to store one byte read from file
    for(long lcv = 0; lcv < memSize; lcv++) {
        fread(&temp,  sizeof(unsigned char), 1, file);
        mem[lcv] = temp;
    }
}

/******************************************************************************
 * Function:    memory object destructor
 * Description: delete memory arr that stores the instruction first
 * Parameters:  void
 * Return:      void
 ******************************************************************************/
memory::~memory() {
    delete mem;
}

/******************************************************************************
 * Function:    getCurrent
 * Description: Get current byte which should be an instruction and increment
 *              the program counter
 * Parameters:  memory* this  //memory object
 * Return:      unsigned char //byte read from memory
 ******************************************************************************/
unsigned char memory::getCurrent() {
    return mem[programCounter++];
}

/******************************************************************************
 * Function:    getCurrent
 * Description: Get current byte which should be an instruction and increment
 *              the program counter
 * Parameters:  memory* this  //memory object
 * Return:      unsigned char //byte read from memory
 ******************************************************************************/
long countFromFile(FILE* file)
{
    long size;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

/******************************************************************************
 * Function:    getChar
 * Description: get a character from memory from current program point
 *              when returns, put the PC into the next instruction
 * Parameters:  memory* this  //memory object
 * Return:      char //character read from memory
 ******************************************************************************/
char memory::getChar() {
    return char(mem[programCounter++]);
}


/******************************************************************************
 * Function:    getShort
 * Description: get a short from memory from current program point
 *              when returns, put the PC into the next instruction
 * Parameters:  memory* this  //memory object
 * Return:      short          //short read from memory
 ******************************************************************************/
short memory::getShort() {
    short result;
    unsigned char temp[] = {mem[programCounter],
                            mem[programCounter + 1]};
    memcpy(&result, &temp, sizeof(result));
    programCounter += 2;
    return result;
}

/******************************************************************************
 * Function:    getInt
 * Description: get a integer from memory from current program point
 *              when returns, put the PC into the next instruction
 * Parameters:  memory* this  //memory object
 * Return:      int           //integer read from memory
 ******************************************************************************/
int memory::getInt() {
    int result;
    unsigned char temp[] = {mem[programCounter],
                            mem[programCounter + 1],
                            mem[programCounter + 2],
                            mem[programCounter + 3]};
    memcpy(&result, &temp, sizeof(result));
    programCounter += 4;
    return result;
}

/******************************************************************************
 * Function:    getFloat
 * Description: get a float from memory from current program point
 *              when returns, put the PC into the next instruction
 * Parameters:  memory* this  //memory object
 * Return:      float         //float read from memory
 ******************************************************************************/
float memory::getFloat() {
    float result;
    unsigned char temp[] = {mem[programCounter],
                            mem[programCounter + 1],
                            mem[programCounter + 2],
                            mem[programCounter + 3]};
    memcpy(&result, &temp, sizeof(result));
    programCounter += 4;
    return result;
}

/******************************************************************************
 * Function:    printMem
 * Description: A helper function that prints program counter and all bytes in memory
 * Parameters:  memory* this  //memory object
 * Return:      void
 ******************************************************************************/
void memory::printMem() {
    std::cout << "memory: ";
    for(long lcv = 0; lcv < memSize; lcv++) {
        std::cout << lcv << ":";
        std::cout << int(mem[lcv]) << ' ';
    }
    std::cout << std::endl;
}


