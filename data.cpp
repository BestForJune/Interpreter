/******************************************************************************
 * File name: data.cpp
 * Description: member functions in class data
 * Programmers: Zhengsen Fu fu216@purdue.edu
 *              Yanjun Chen chen2620@purdue.edu
 ******************************************************************************/
#include "data.h"
#include <iostream>

/******************************************************************************
 * Function:    data::data(char dataInput) 
 * Description: Initialize the element if the input is a character
 * Parameters:  dataInput, char, target element
 * Return:      none
 ******************************************************************************/
data::data(char dataInput) {
    dataType = CHAR;
    charData = dataInput;
    shortData = 0;
    intData = 0;
    floatData = 0;
}

/******************************************************************************
 * Function:    data::data(short dataInput) 
 * Description: Initialize the element if the input is a short
 * Parameters:  dataInput, short, target element
 * Return:      none
 ******************************************************************************/
data::data(short dataInput) {
    dataType = SHORT;
    charData = 0;
    shortData = dataInput;
    intData = 0;
    floatData = 0;
}

/******************************************************************************
 * Function:    data::data(int dataInput) 
 * Description: Initialize the element if the input is an int
 * Parameters:  dataInput, int, target element
 * Return:      none
 ******************************************************************************/
data::data(int dataInput) {
    dataType = INT;
    charData = 0;
    shortData = 0;
    intData = dataInput;
    floatData = 0;
}

/******************************************************************************
 * Function:    data::data(float dataInput) 
 * Description: Initialize the element if the input is a float
 * Parameters:  dataInput, float, target element
 * Return:      none
 ******************************************************************************/
data::data(float dataInput) {
    dataType = FLOAT;
    charData = 0;
    shortData = 0;
    intData = 0;
    floatData = dataInput;
}

/******************************************************************************
 * Function:    data data::operator == (const data& arg)
 * Description: operator '==' overload, compare char, shor, int or float
 *              values in the given two elements
 * Parameters:  arg, data, compare element
 * Return:      1 if the two elements have same data type and same value
 *              0 if the two elements have different data type and different 
 *              value
 ******************************************************************************/
data data::operator == (const data& arg){
    if (dataType == arg.dataType){
        if (dataType == CHAR && charData == arg.charData){ return data(int(1)); }
        else if (dataType == SHORT && shortData == arg.shortData){ return data(int(1)); }
        else if (dataType == INT && intData == arg.intData){ return data(int(1)); }
        else if (dataType == FLOAT && floatData == arg.floatData){ return data(int(1)); }
    }
    return data(int(0));
}

/******************************************************************************
 * Function:    data data::operator > (const data& arg)
 * Description: operator '>' overload, compare char, shor, int or float
 *              values in the given two elements
 * Parameters:  arg, data, compare element
 * Return:      1 if the self element has bigger value than the compare element
 *              0 if the two elements have different data type and the self 
 *              element has smaller value than the compare element
 ******************************************************************************/
data data::operator > (const data& arg){
    if (dataType == arg.dataType){
        if (dataType == CHAR && charData > arg.charData){ return data(int(1)); }
        else if (dataType == SHORT && shortData > arg.shortData){ return data(int(1)); }
        else if (dataType == INT && intData > arg.intData){ return data(int(1)); }
        else if (dataType == FLOAT && floatData > arg.floatData){ return data(int(1)); }
    }
    return data(int(0));
}

/******************************************************************************
 * Function:    data data::operator < (const data& arg)
 * Description: operator '<' overload, compare char, shor, int or float
 *              values in the given two elements
 * Parameters:  arg, data, compare element
 * Return:      1 if the self element has smaller value than the compare element
 *              0 if the two elements have different data type and the self 
 *              element has bigger value than the compare element
 ******************************************************************************/
data data::operator < (const data& arg){
    if (dataType == arg.dataType){
        if (dataType == CHAR && charData < arg.charData){ return data(int(1)); }
        else if (dataType == SHORT && shortData < arg.shortData){ return data(int(1)); }
        else if (dataType == INT && intData < arg.intData){ return data(int(1)); }
        else if (dataType == FLOAT && floatData < arg.floatData){ return data(int(1)); }
    }
    return data(int(0));
}

/******************************************************************************
 * Function:    data data::operator + (const data& arg)
 * Description: operator '+' overload, add char, shor, int or float values 
 *              in the given two elements
 * Parameters:  arg, data, element with the value to add
 * Return:      value, data, element with the value added
 *              (self.data + arg.data)
 ******************************************************************************/
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

/******************************************************************************
 * Function:    data data::operator - (const data& arg)
 * Description: operator '-' overload, substract char, shor, int or float values 
 *              in the given two elements
 * Parameters:  arg, data, element with the value to substract
 * Return:      value, data, element with the value substracted 
 *              (self.data - arg.data)
 ******************************************************************************/
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

/******************************************************************************
 * Function:    data data::operator * (const data& arg)
 * Description: operator '*' overload, multiply char, shor, int or float values 
 *              in the given two elements
 * Parameters:  arg, data, element with the value to multiply
 * Return:      value, data, element with the value multiplied 
 *              (self.data * arg.data)
 ******************************************************************************/
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

/******************************************************************************
 * Function:    data data::operator / (const data& arg)
 * Description: operator '/' overload, divide char, shor, int or float values 
 *              in the given two elements
 * Parameters:  arg, data, element with the value to divide
 * Return:      value, data, element with the value divided 
 *              (self.data / arg.data)
 ******************************************************************************/
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

/******************************************************************************
 * Function:    getData(char indicator)
 * Description: get the target type of value from the data type element
 * Parameters:  indicator, char, an example of character 
 *              helping to reach this function
 * Return:      charData, char, the character value stored in the element
 ******************************************************************************/
char data::getData(char indicator) {
    if(dataType != CHAR) {
        std::cout << "Error in data type\n";
    }
    return charData;
}

/******************************************************************************
 * Function:    getData(short indicator)
 * Description: get the target type of value from the data type element
 * Parameters:  indicator, short, an example of short 
 *              helping to reach this function
 * Return:      charData, short, the short value stored in the element
 ******************************************************************************/
short data::getData(short indicator) {
    if(dataType != SHORT) {
        std::cout << "Error in data type\n";
    }
    return shortData;
}

/******************************************************************************
 * Function:    getData(int indicator)
 * Description: get the target type of value from the data type element
 * Parameters:  indicator, int, an example of int 
 *              helping to reach this function
 * Return:      charData, int, the int value stored in the element
 ******************************************************************************/
int data::getData(int indicator) {
    if(dataType != INT) {
        std::cout << "Error in data type\n";
    }
    return intData;
}

/******************************************************************************
 * Function:    getData(float indicator)
 * Description: get the target type of value from the data type element
 * Parameters:  indicator, float, an example of float 
 *              helping to reach this function
 * Return:      charData, float, the float value stored in the element
 ******************************************************************************/
float data::getData(float indicator) {
    if(dataType != FLOAT) {
        std::cout << "Error in data type\n";
    }
    return floatData;
}

/******************************************************************************
 * Function:    std::ostream& operator<<(std::ostream& os, const data& arg)
 * Description: operator '<<' overload
 * Return:      value stored in the element with the correct data type
 ******************************************************************************/
std::ostream& operator<<(std::ostream& os, const data& arg) {
    if (arg.dataType == CHAR){ return os << arg.charData; }
    else if (arg.dataType == SHORT){ return  os << arg.shortData; }
    else if (arg.dataType == INT){ return os << arg.intData; }
    else if (arg.dataType == FLOAT){ return os << arg.floatData; }
    return os;
}
