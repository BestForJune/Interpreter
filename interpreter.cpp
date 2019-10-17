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
        if(instruction == 87 || // peekf 01011011
           instruction == 86 || // peeki 01011010
           instruction == 85 || // peeks 01011001
           instruction == 84    // peekc 01011000
                ) {
            //offset of the one is going to be changed
            int offsetChange = rstack[rstack.size() - 2].getData(intIndicator);
            //offset of the value
            int offsetTarget = rstack.back().getData(intIndicator);
            fpsp = fpstack.back();
            rstack[fpsp + offsetChange + 1] = rstack[fpsp + offsetTarget + 1];
        }
        if(instruction == 91 || // pokef 01100011
           instruction == 90 || // pokei 01100010
           instruction == 89 || // pokes 01100001
           instruction == 88    // pokec 01100000
           ) {
            //offset of the one is going to be changed
            int offsetChange = rstack.back().getData(intIndicator);
            //offset of the value
            int offsetTarget = rstack[rstack.size() - 2].getData(intIndicator);
            fpsp = fpstack.back();
            rstack[fpsp + offsetChange + 1] = rstack[fpsp + offsetTarget + 1];
        }
        if(instruction == 94) { //swap 01100100
            data dataUpper = rstack.back();
            rstack.pop_back();
            data dataLower = rstack.back();
            rstack.pop_back();
            rstack.push_back(dataUpper);
            rstack.push_back(dataLower);
        }
        if(instruction == 100) { //addition 01100100
            data dataUpper = rstack.back();
            rstack.pop_back();
            data dataLower = rstack.back();
            rstack.pop_back();
            dataLower = dataLower + dataUpper;
            rstack.push_back(dataLower);
        }
        if(instruction == 104) { //subtract 01101000
            data dataUpper = rstack.back();
            rstack.pop_back();
            data dataLower = rstack.back();
            rstack.pop_back();
            dataLower = dataLower - dataUpper;
            rstack.push_back(dataLower);
        }
        if(instruction == 108) { //multiplication 01101100
            data dataUpper = rstack.back();
            rstack.pop_back();
            data dataLower = rstack.back();
            rstack.pop_back();
            dataLower = dataLower * dataUpper;
            rstack.push_back(dataLower);
        }
        if(instruction == 112) { //divide 01110000
            data dataUpper = rstack.back();
            rstack.pop_back();
            data dataLower = rstack.back();
            rstack.pop_back();
            dataLower = dataLower / dataUpper;
            rstack.push_back(dataLower);
        }
        if(instruction == 148) { //print character 10010100
            data data1 = rstack.back();
            rstack.pop_back();
            cout << data1.getData(charIndicator) << endl;
        }
        if(instruction == 149) { //print short 10010110
            data data1 = rstack.back();
            rstack.pop_back();
            cout << data1.getData(shortIndicator) << endl;
        }
        if(instruction == 150) { //print int
            data data1 = rstack.back();
            rstack.pop_back();
            cout << data1.getData(intIndicator) << endl;
        }
        if(instruction == 151) { //print float 10010111
            data data1 = rstack.back();
            rstack.pop_back();
            cout << data1.getData(floatIndicator) << endl;
        }
        if(instruction == 0) { //halt 00000000
            halt = true;
        }
    }
    fclose(file);
    return EXIT_SUCCESS;
}
