#include <cstdlib>
#include <iostream>
#include <cstdio>
#include "memory.h"
using namespace std;

int main(int argc, char** argv) {
    cout<<argv[1]<<endl;
    FILE* file = fopen(argv[1], "r");
    if(file == nullptr) {
        cout << "Error opening the file!\n";
        return EXIT_FAILURE;
    }
    auto* progMem = new memory(file); // Program memory

    delete progMem;
    fclose(file);
    return EXIT_SUCCESS;
}