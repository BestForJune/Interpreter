//
// Created by 傅正森 on 2019/10/29.
//
#include <cstdio>
void instruction(unsigned char ins, FILE* fptr) {
    fwrite(&ins, sizeof(unsigned char), 1, fptr);
}

void push_int(int data, FILE* fptr) {
    instruction(70, fptr);
    fwrite(&data, sizeof(int), 1, fptr);
}

void push_char(char data, FILE* fptr) {
    instruction(68, fptr);
    fwrite(&data, sizeof(char), 1, fptr);
}

void push_float(float data, FILE* fptr) {
    instruction(71, fptr);
    fwrite(&data, sizeof(float), 1, fptr);
}

void push_short(short data, FILE* fptr) {
    instruction(69, fptr);
    fwrite(&data, sizeof(short), 1, fptr);
}

int main() {
    FILE* fptr = fopen("test.smp", "wb");
    push_int(1, fptr);
    push_int(2,fptr);
    push_int(3,fptr);
    push_int(4,fptr);
    push_int(3, fptr);
    instruction(44, fptr);
    instruction(146, fptr);
    instruction(0, fptr);
    return 0;
}



