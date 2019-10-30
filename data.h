#ifndef INTERPRETER_STACK_H
#define INTERPRETER_STACK_H

#define CHAR 1
#define SHORT 2
#define INT 3
#define FLOAT 4

#include <iostream>

class data {
    int dataType; //char 1; short 2; int 3; float 4;
    char charData;
    short shortData;
    int intData;
    float floatData;

public:
    explicit data(char dataInput);
    explicit data(short dataInput);
    explicit data(int dataInput);
    explicit data(float dataInput);
    virtual ~data() = default;
    data operator==(const data& input);
    data operator>(const data& input);
    data operator<(const data& input);
    data operator+(const data& input);
    data operator-(const data& input);
    data operator*(const data& input);
    data operator/(const data& input);
    char getData(char indicator);
    short getData(short indicator);
    int getData(int indicator);
    float getData(float indicator);
    friend std::ostream& operator<<(std::ostream& os, const data& arg);
};

#endif //INTERPRETER_STACK_H
