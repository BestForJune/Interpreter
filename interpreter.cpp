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
            data data1 = rstack.back(); //rstack[sp]
            rstack.pop_back();
            data data2 = rstack.back();
            rstack.pop_back();//sp = sp-2
            int value = data2.getData(intIndicator);
            if (value){
                progMem.programCounter = data1.getData(intIndicator);
            }
            else{
                rstack.push_back(data2);
                rstack.push_back(data1);
            }
        }
        if (instruction == 44){ //call: 44, or 00101100
            sp = rstack.size();
            int dataresult = sp - rstack.back().getData(intIndicator)-1);
            fpstack.push_back(dataresult);
            rstack.pop_back();
            progMem.programCounter = rstack.back().getData(intIndicator); //pc = rstack[sp]
            rstack.pop_back();
        }
        if (instruction == 48){ //ret: 48, or 00110000
            sp = fpstack.back().getData(intIndicator);
            fpstack.pop_back();
            for (int i = rstack.size(); i < sp; i--){
                rstack.pop_back();
            }
            progMem.programCounter = rstack.back().getData(intIndicator); 
            rstack.pop_back();
        }
        if (instruction == 68){ //pushc: 68, or 01000100
            data result = new data(progMem.getChar());
            progMem.programCounter += 1;
            rstack.push_back(result);
        }
        if (instruction == 69){//pushs: 69 or 01000101
            data result = new data(progMem.getShort());
            progMem.programCounter += 1;
            rstack.push_back(result);
        }
        if (instruction == 70){ //pushi: 70 or 01000110
            data result = new data(progMem.getInt());
            progMem.programCounter += 1;          
            rstack.push_back(result);
        }
        if (instruction == 71){ //pushf: 71 or 01000111
            data result = new data(progMem.getFloat());
            progMem.programCounter += 1;
            rstack.push_back(result);
        }
        if (instruction == 72 || //pushvc: 72, or 01001000
            instruction == 73 || //pushvs: 73, or 01001001
            instruction == 74 || //pushvi: 74, or 01001010
            instruction == 75 ){ //pushvf: 75, or 01001011
            int result = rstack.back().getData(intIndicator);
            rstack.pop_back();
            int fpresult = fpstack.back().getData(intIndicator);
            rstack.push_back(rstack[result+fpresult+1]);
        }
        if (instruction == 76){ //popm: 76, or 01001100
            sp = rstack.back().getData(intIndicator)+1;
            for (int i = rstack.size(); i > sp; i--){
                rstack.pop_back();
            }
        }
        if (insturction == 80){ //popv: 80, or 01010000
            data result = rstack.back();
            rstack.pop_back();
            int fpresult = fpstack.back.getData(intIndicator);
            rstack[fpresult+result.getData(intIndicator)+1] = result;
            rstack.pop_back();
            rstack.pop_back();
        }
        if (instruction == 77){ //popa: 77, or 01001101
            int result = rstack.back().getData(intIndicator);
            int fpresult = fpstack.back.getData(intIndicator);
            sp = rstack.size();
            for (int i = 1; i < result + 1; i++){
                rstack[fpresult + i] = rstack[sp - result + i - 1];
            }
            sp = fpresult+result;
            for (int i = rstack.size(); i > sp; i--){
                rstack.pop_back();
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
