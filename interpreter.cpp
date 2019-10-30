/******************************************************************************
 * File name: interpreter.cpp 
 * Description: The bytecode interpreter will read a bytecode file produced by
 *              the compiler
 * Programmers: Zhengsen Fu fu216@purdue.edu
 *              Yanjun Chen chen2620@purdue.edu
 ******************************************************************************/
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <vector>
#include "memory.h"
#include "data.h"
using namespace std;

/******************************************************************************
 * Function:    printStack
 * Description: This functions print the elements in the runtime stack
 * Parameters:  stack, vector<data>, runtime stack
 * Return:      print the elements
 ******************************************************************************/
void printStack(vector<data> stack) {
    cout << "rstack: ";
    if (stack.size() <= 0){
        cout << "empty";
    }
    else{
        for(int i = 0; i < stack.size(); i++) {
            cout << stack[i] << ' ';
        }
    }
    cout << endl;
}

/******************************************************************************
 * Function:    printfStack
 * Description: This functions print the elements in the stack of frame 
 *              pointers
 * Parameters:  stack, vector<int>, stack of frame pointers
 * Return:      print the elements
 ******************************************************************************/
void printfStack(vector<int> stack){
    cout << "fpstack: ";
    if (stack.size() <= 0){
        cout << "empty";
    }
    else{
        for(int i = 0; i < stack.size(); i++) {
            cout << stack[i] << ' ';
        }
    }
    cout << endl;
}

int main(int argc, char** argv) {
    FILE* file = fopen(argv[1], "r");
    if(file == nullptr) {
        cout << "Error opening the file!\n";
        return EXIT_FAILURE;
    } //read file
    memory progMem = memory(file); //Program memory
    vector<data> rstack; //runtime stack
    int sp = -1; //runtime stack pointer
    vector<int> fpstack; //stack of frame pointers
    int fpsp = -1; //frame pointer stack pointer
    bool halt = false; //help to end the program
    char charIndicator = 'c'; //example of a character, use to grep element from target stack
    short shortIndicator = 1; //example of a short, use to grep element from target stack
    int intIndicator = 1; //example of an int, use to grep element from target stack
    float floatIndicator = 1.2; //example of a float, use to grep element from target stack
    //progMem.printMem(); //helper function: print elements in program memory

    while(!halt) {
        //printStack(rstack); //helper function: print elements on the run time stack
        //printfStack(fpstack); //helper function: print the elements in the stack of frame pointers
        unsigned char instruction = progMem.getCurrent(); //get the instruction from program memory

        if (instruction == 132){ //cmpe: 132, or 10000100
            data data1 = rstack.back();
            rstack.pop_back();
            data data2 = rstack.back();
            rstack.pop_back();
            rstack.push_back(data1 == data2);
            continue;
        }
        if (instruction == 136){ //cmplt: 136, or 10001000
            data data1 = rstack.back();
            rstack.pop_back();
            data data2 = rstack.back();
            rstack.pop_back();
            rstack.push_back(data1 < data2);
            continue;
        }
        if (instruction == 140){ //cmpgt: 140, or 10001100
            data data1 = rstack.back();
            rstack.pop_back();
            data data2 = rstack.back();
            rstack.pop_back();
            rstack.push_back(data1 > data2);
            continue;
        }
        if (instruction == 36){ //jmp: 36, or 00100100 
            progMem.programCounter = rstack.back().getData(intIndicator);
            rstack.pop_back();
            continue;
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
            continue;
        }
        if (instruction == 44){ //call: 44, or 00101100
            sp = rstack.size() - 1;
            int dataResult = sp - rstack.back().getData(intIndicator) - 1;
            fpstack.push_back(dataResult); //current address on the runtime stack 
            rstack.pop_back();
            progMem.programCounter = rstack.back().getData(intIndicator); //point the pc to called address
            rstack.pop_back();
            continue;
        }
        if (instruction == 48){ //ret: 48, or 00110000
            sp = fpstack.back();
            fpstack.pop_back();
            for (int i = rstack.size() - 1; i > sp; i--){
                rstack.pop_back();
            }
            progMem.programCounter = rstack.back().getData(intIndicator); 
            rstack.pop_back();
            continue;
        }
        if (instruction == 68){ //pushc: 68, or 01000100
            data result = data(progMem.getChar());
            rstack.push_back(result);
            continue;
        }
        if (instruction == 69){//pushs: 69 or 01000101
            data result = data(progMem.getShort());
            rstack.push_back(result);
            continue;
        }
        if (instruction == 70){ //pushi: 70 or 01000110
            data result = data(progMem.getInt());
            rstack.push_back(result);
            continue;
        }
        if (instruction == 71){ //pushf: 71 or 01000111
            data result = data(progMem.getFloat());
            rstack.push_back(result);
            continue;
        }
        if (instruction == 72 || //pushvc: 72, or 01001000
            instruction == 73 || //pushvs: 73, or 01001001
            instruction == 74 || //pushvi: 74, or 01001010
            instruction == 75 ){ //pushvf: 75, or 01001011
            int result = rstack.back().getData(intIndicator);
            rstack.pop_back();
            int fpresult = fpstack.back();
            rstack.push_back(rstack[result + fpresult + 1]);
            continue;
        }
        if (instruction == 76){ //popm: 76, or 01001100
            sp = rstack.back().getData(intIndicator) + 1;
            for (int i = 0; i < sp; i++){
                rstack.pop_back();
            }
            continue;
        }
        if (instruction == 80){ //popv: 80, or 01010000
            data result = rstack.back();
            rstack.pop_back();
            data into = rstack.back();
            rstack.pop_back();
            int fpresult = fpstack.back();
            rstack[fpresult + result.getData(intIndicator) + 1] = into;
            continue;
        }
        if (instruction == 77){ //popa: 77, or 01001101
            int result = rstack.back().getData(intIndicator);
            int fpresult = fpstack.back();
            sp = rstack.size() - 1;
            for (int i = result; i >= 1; i--){
                rstack[fpresult + i] = rstack[sp - (result - i + 1)];
            }
            sp = fpresult+result;
            for (int i = rstack.size() - 1; i > sp; i--){
                rstack.pop_back();
            }
            continue;
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
            continue;
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
            continue;
        }
        if(instruction == 94) { //swap 01100100
            data dataUpper = rstack.back();
            rstack.pop_back();
            data dataLower = rstack.back();
            rstack.pop_back();
            rstack.push_back(dataUpper);
            rstack.push_back(dataLower);
            continue;
        }
        if(instruction == 100) { //addition 01100100
            data dataUpper = rstack.back();
            rstack.pop_back();
            data dataLower = rstack.back();
            rstack.pop_back();
            dataLower = dataLower + dataUpper;
            rstack.push_back(dataLower);
            continue;
        }
        if(instruction == 104) { //subtract 01101000
            data dataUpper = rstack.back();
            rstack.pop_back();
            data dataLower = rstack.back();
            rstack.pop_back();
            dataLower = dataLower - dataUpper;
            rstack.push_back(dataLower);
            continue;
        }
        if(instruction == 108) { //multiplication 01101100
            data dataUpper = rstack.back();
            rstack.pop_back();
            data dataLower = rstack.back();
            rstack.pop_back();
            dataLower = dataLower * dataUpper;
            rstack.push_back(dataLower);
            continue;
        }
        if(instruction == 112) { //divide 01110000
            data dataUpper = rstack.back();
            rstack.pop_back();
            data dataLower = rstack.back();
            rstack.pop_back();
            dataLower = dataLower / dataUpper;
            rstack.push_back(dataLower);
            continue;
        }
        if(instruction == 144) { //print character 10010100
            data data1 = rstack.back();
            rstack.pop_back();
            cout << data1.getData(charIndicator) << endl;
            continue;
        }
        if(instruction == 145) { //print short 10010110
            data data1 = rstack.back();
            rstack.pop_back();
            cout << data1.getData(shortIndicator) << endl;
            continue;
        }
        if(instruction == 146) { //print int
            data data1 = rstack.back();
            rstack.pop_back();
            cout << data1.getData(intIndicator) << endl;
            continue;
        }
        if(instruction == 147) { //print float 10010111
            data data1 = rstack.back();
            rstack.pop_back();
            cout << data1.getData(floatIndicator) << endl;
            continue;
        }
        if(instruction == 0) { //halt 00000000
            halt = true;
            progMem.programCounter -= 1;
            continue;
        }
    }

    cout << "\nCompile values:" << endl;
    cout << "PC: " << progMem.programCounter << endl;
    cout << "sp: " << int(rstack.size()-1) <<endl;
    printStack(rstack);
    cout << "fpsp: " << int(fpstack.size()-1) <<endl;
    printfStack(fpstack);

    fclose(file);
    return EXIT_SUCCESS;
}
