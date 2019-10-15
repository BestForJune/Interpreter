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
    auto* progMem = new memory(file); // Program memory
    vector<data> rstack; //runtime stack
    int sp = -1; //runtime stack pointer
    vector<int> fpstack; //stack of frame pointers
    int fpsp = -1; // frame pointer stack pointer
    bool halt = false;

    while(!halt) {
        unsigned char instruction = progMem -> getCurrent();
        if (instruction == 68){ //pushc
            rstack[++sp] = mem[pc+1];
            pc += 2;
        }
        if(instruction == 151) { //print float

        }
        if(instruction == 0) { //halt
            halt = true;
        }
    }
    delete progMem;
    fclose(file);
    return EXIT_SUCCESS;
}
