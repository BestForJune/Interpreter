//
// Created by 傅正森 on 2019/10/29.
//
#include <cstdio>

int main() {
    FILE* fptr = fopen("test.smp", "wb");
    unsigned char write = 70;
    fwrite(&write, sizeof(unsigned char), 1, fptr);

    int temp = 1;
    fwrite(&temp, sizeof(int), 1, fptr);

    write = 146;
    fwrite(&write, sizeof(unsigned char), 1, fptr);

    write = 0;
    fwrite(&write, sizeof(unsigned char), 1, fptr);
    fclose(fptr);
    return 0;
}


