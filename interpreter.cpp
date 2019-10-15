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
        if (instruction == 132){ //cmpe
            int data1 = rstack.back();
            rstack.pop_back();
            int data2 = rstack.back();
            rstack.pop_back();
            rstack.push_back(data1 == data2);
        }
        if(instruction == 151) { //print float
            data data1 = rstack.back();
            rstack.pop_back();
            cout <<
            rstack.pop_back();

        }
        if(instruction == 0) { //halt
            halt = true;
        }
    }
    fclose(file);
    return EXIT_SUCCESS;
}
