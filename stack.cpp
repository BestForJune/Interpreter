#include "stack.h"
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

data data::operator == (data arg){
    if (dataType == arg.dataType){
        if (dataType == CHAR && charData == arg.charData){ return 1; }
        else if (dataType == SHORT && shortData == arg.shortData){ return 1; }
        else if (dataType == INT && intData == arg.intData){ return 1; }
        else if (dataType == FLOAT && floatData == arg.floatData){ return 1; }
    }
    return 0;
}

data data::operator > (data arg){
    if (dataType == arg.dataType){
        if (dataType == CHAR && charData > arg.charData){ return 1; }
        else if (dataType == SHORT && shortData > arg.shortData){ return 1; }
        else if (dataType == INT && intData > arg.intData){ return 1; }
        else if (dataType == FLOAT && floatData > arg.floatData){ return 1; }
    }
    return 0;
}

data data::operator < (data arg){
    if (dataType == arg.dataType){
        if (dataType == CHAR && charData < arg.charData){ return 1; }
        else if (dataType == SHORT && shortData < arg.shortData){ return 1; }
        else if (dataType == INT && intData < arg.intData){ return 1; }
        else if (dataType == FLOAT && floatData < arg.floatData){ return 1; }
    }
    return 0;
}
