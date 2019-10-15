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



