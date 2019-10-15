#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <vector>
#include "memory.h"
#include "stack.h"
#include "instruction.h"

using namespace std;

int main(int argc, char** argv) {
    FILE* file = fopen(argv[1], "r");
    if(file == nullptr) {
        cout << "Error opening the file!\n";
        return EXIT_FAILURE;
    }
    memory progMem = memory(file); // Program memory
    vector<data> rstack; //runtime stack
    int sp = -1; //runtime stack pointer
    vector<int> fpstack; //stack of frame pointers
    int fpsp = -1; // frame pointer stack pointer
    bool halt = false;

    while(!halt) {
        unsigned char instruction = progMem -> getCurrent();
        if (instruction == 132){ //cmpe: 132, or 10000100
            data data1 = rstack.back();
            rstack.pop_back();
            data data2 = rstack.back();
            rstack.pop_back();
            rstack.push_back(data1 == data2);
        }
        if (instruction == 135){ //cmplt: 136, or 10001000
            data data1 = rstack.back();
            rstack.pop_back();
            data data2 = rstack.back();
            rstack.pop_back();
            rstack.push_back(data1 < data2);
        }
        if (instruction == 140){ //cmpgt: 140, or 10001100
            data data1 = rstack.back();
            rstack.pop_back();
            data data2 = rstack.back();
            rstack.pop_back();
            rstack.push_back(data1 > data2);
        }
        if (instruction == 36){ //jmp: 36, or 00100100 
            progMem.programCounter = rstack.back().getData;
            rstack.pop_back();
        }
        if (instruction == 40){ //jmpc: 40, or 00101000
            data data1 = rstack.back();

        }
        if(instruction == 151) { //print float
            rstack
        }
        if(instruction == 0) { //halt
            halt = true;
        }
    }
    fclose(file);
    return EXIT_SUCCESS;
}
