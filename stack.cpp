#include "stack.h"
#include <iostream>
data::data(char dataInput) {
    dataType = CHAR;
    charData = dataInput;
    shortData = 0;
    intData = 0;
    floatData = 0;
}

data::data(short dataInput) {
    dataType = SHORT;
    charData = 0;
    shortData = dataInput;
    intData = 0;
    floatData = 0;
}

data::data(int dataInput) {
    dataType = INT;
    charData = 0;
    shortData = 0;
    intData = dataInput;
    floatData = 0;
}

data::data(float dataInput) {
    dataType = FLOAT;
    charData = 0;
    shortData = 0;
    intData = 0;
    floatData = dataInput;
}

data data::operator == (const data& arg){
    if (dataType == arg.dataType){
        if (dataType == CHAR && charData == arg.charData){ return data(int(1)); }
        else if (dataType == SHORT && shortData == arg.shortData){ return data(int(1)); }
        else if (dataType == INT && intData == arg.intData){ return data(int(1)); }
        else if (dataType == FLOAT && floatData == arg.floatData){ return data(int(1)); }
    }
    return data(int(0));
}

data data::operator > (const data& arg){
    if (dataType == arg.dataType){
        if (dataType == CHAR && charData > arg.charData){ return data(int(1)); }
        else if (dataType == SHORT && shortData > arg.shortData){ return data(int(1)); }
        else if (dataType == INT && intData > arg.intData){ return data(int(1)); }
        else if (dataType == FLOAT && floatData > arg.floatData){ return data(int(1)); }
    }
    return data(int(0));
}

data data::operator < (const data& arg){
    if (dataType == arg.dataType){
        if (dataType == CHAR && charData < arg.charData){ return data(int(1)); }
        else if (dataType == SHORT && shortData < arg.shortData){ return data(int(1)); }
        else if (dataType == INT && intData < arg.intData){ return data(int(1)); }
        else if (dataType == FLOAT && floatData < arg.floatData){ return data(int(1)); }
    }
    return data(int(0));
}

data data::operator + (const data& arg){
    if (dataType == arg.dataType){
        if (dataType == CHAR){ return data(charData + arg.charData); }
        else if (dataType == SHORT){ return data(shortData + arg.shortData); }
        else if (dataType == INT){ return data(intData + arg.intData); }
        else if (dataType == FLOAT){ return data(floatData + arg.floatData); }
    }
    std::cout<< "None matching data Type!\n";
    return data(0);
}

data data::operator - (const data& arg){
    if (dataType == arg.dataType){
        if (dataType == CHAR){ return data(charData - arg.charData); }
        else if (dataType == SHORT){ return data(shortData - arg.shortData); }
        else if (dataType == INT){ return data(intData - arg.intData); }
        else if (dataType == FLOAT){ return data(floatData - arg.floatData); }
    }
    std::cout<< "None matching data Type!\n";
    return data(0);
}

data data::operator * (const data& arg){
    if (dataType == arg.dataType){
        if (dataType == CHAR){ return data(charData * arg.charData); }
        else if (dataType == SHORT){ return data(shortData * arg.shortData); }
        else if (dataType == INT){ return data(intData * arg.intData); }
        else if (dataType == FLOAT){ return data(floatData * arg.floatData); }
    }
    std::cout<< "None matching data Type!\n";
    return data(0);
}

data data::operator / (const data& arg){
    if (dataType == arg.dataType){
        if (dataType == CHAR){ return data(charData / arg.charData); }
        else if (dataType == SHORT){ return data(shortData / arg.shortData); }
        else if (dataType == INT){ return data(intData / arg.intData); }
        else if (dataType == FLOAT){ return data(floatData / arg.floatData); }
    }
    std::cout<< "None matching data Type!\n";
    return data(0);
}

char data::getData(char indicator) {
    if(dataType != CHAR) {
        std::cout << "Error in data type\n";
    }
    return charData;
}
short data::getData(short indicator) {
    if(dataType != SHORT) {
        std::cout << "Error in data type\n";
    }
    return shortData;
}

int data::getData(int indicator) {
    if(dataType != INT) {
        std::cout << "Error in data type\n";
    }
    return intData;
}
float data::getData(float indicator) {
    if(dataType != FLOAT) {
        std::cout << "Error in data type\n";
    }
    return floatData;
}

std::ostream& operator<<(std::ostream& os, const data& arg) {
    if (arg.dataType == CHAR){ return os << arg.charData; }
    else if (arg.dataType == SHORT){ return  os << arg.shortData; }
    else if (arg.dataType == INT){ return os << arg.intData; }
    else if (arg.dataType == FLOAT){ return os << arg.floatData; }
    return os;
}
