#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <vector>
#include "memory.h"
#include "stack.h"

using namespace std;

int main(int argc, char** argv) {
    FILE* file = fopen(argv[1], "r");
    if(file == nullptr) {
        cout << "Error opening the file!\n";
        return EXIT_FAILURE;
    }
    auto* progMem = new memory(file); // Program memory
    vector<data> rstack; //runtime stack
//    int rp = -1; //runtime stack pointer
    vector<int> fpstack; //stack of frame pointers
    bool halt = false;

    while(!halt) {
        unsigned char instruction = progMem -> getCurrent();
        if
    }
    delete progMem;
    fclose(file);
    return EXIT_SUCCESS;
}
