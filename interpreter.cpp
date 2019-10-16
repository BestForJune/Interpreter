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
    char charIndicator = 'c';
    short shortIndicator = 1;
    int intIndicator = 1;
    float floatIndicator = 1.2;

    while(!halt) {
        unsigned char instruction = progMem.getCurrent();
        if (instruction == 132){ //cmpe
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
            progMem.programCounter = rstack.back().getData(intIndicator);
            rstack.pop_back();
        }
        if (instruction == 40){ //jmpc: 40, or 00101000
            data data1 = rstack.back();
            if (data1.dataType == 3 && data1.intData){
                progMem.programCounter = rstack.back().getData(intIndicator);
                rstack.pop_back();
                rstack.pop_back();//sp = sp-2
            }
        }

        if(instruction == 94) { //swap
            data dataUpper = rstack.back();
            rstack.pop_back();
            data dataLower = rstack.back();
            rstack.pop_back();
            rstack.push_back(dataUpper);
            rstack.push_back(dataLower);
        }
        if(instruction == 100) { //addition
            data dataUpper = rstack.back();
            rstack.pop_back();
            data dataLower = rstack.back();
            rstack.pop_back();
            dataLower = dataLower + dataUpper;
            rstack.push_back(dataLower);
        }
        if(instruction == 104) { //subtract
            data dataUpper = rstack.back();
            rstack.pop_back();
            data dataLower = rstack.back();
            rstack.pop_back();
            dataLower = dataLower - dataUpper;
            rstack.push_back(dataLower);
        }
        if(instruction == 108) { //multiplication
            data dataUpper = rstack.back();
            rstack.pop_back();
            data dataLower = rstack.back();
            rstack.pop_back();
            dataLower = dataLower * dataUpper;
            rstack.push_back(dataLower);
        }
        if(instruction == 112) { //divide
            data dataUpper = rstack.back();
            rstack.pop_back();
            data dataLower = rstack.back();
            rstack.pop_back();
            dataLower = dataLower / dataUpper;
            rstack.push_back(dataLower);
        }
        if(instruction == 148) { //print character
            data data1 = rstack.back();
            rstack.pop_back();
            cout << data1.getData(charIndicator) << endl;
        }
        if(instruction == 149) { //print short
            data data1 = rstack.back();
            rstack.pop_back();
            cout << data1.getData(shortIndicator) << endl;
        }
        if(instruction == 150) { //print int
            data data1 = rstack.back();
            rstack.pop_back();
            cout << data1.getData(intIndicator) << endl;
        }
        if(instruction == 151) { //print float
            data data1 = rstack.back();
            rstack.pop_back();
            cout << data1.getData(floatIndicator) << endl;
        }
        if(instruction == 0) { //halt
            halt = true;
        }
    }
    fclose(file);
    return EXIT_SUCCESS;
}
