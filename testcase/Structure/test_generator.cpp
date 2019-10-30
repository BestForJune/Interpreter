#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>

enum Instr {
    HALT = 0,
    JMP = 36,
    JMPC = 40,
    CALL = 44,
    RET = 48,
    PUSHC = 68,
    PUSHS,
    PUSHI,
    PUSHF,
    PUSHVC,
    PUSHVS,
    PUSHVI,
    PUSHVF,
    POPM = 76,
    POPA = 77,
    POPV = 80,
    PEEKC = 84,
    PEEKS,
    PEEKI,
    PEEKF,
    POKEC = 88,
    POKES,
    POKEI,
    POKEF,
    SWP = 94,
    ADD = 100,
    SUB = 104,
    MUL = 108,
    DIV = 112,
    CMPE = 132,
    CMPLT = 136,
    CMPGT = 140,
    PRINTC = 144,
    PRINTS,
    PRINTI,
    PRINTF
};

void output_to_binary_file(std::string str, std::vector<unsigned char> vec) {
    std::ofstream output_file(str, std::ios::out | std::ios::binary);
    std::ostream_iterator<unsigned char> output_iterator(output_file, "");
    std::copy(vec.begin(), vec.end(), output_iterator);
}

int main() {
    //Basics.bin - PUSH, PRINT, HALT
    std::vector<unsigned char> basics_vec {
        //Chars
        PUSHC, 12,
        PUSHC, 34,
        PUSHC, 56,
        PRINTC,
        PRINTC,
        PRINTC,

        //Shorts
        PUSHS, 0xD2, 0x04,
        PRINTS,
        PUSHS, 0x1F, 0xEF,
        PRINTS,

        //Ints
        PUSHI, 16, 0, 0, 0,
        PRINTI,
        PUSHI, 0xFF, 0xFF, 0xFF, 0xFF,
        PRINTI,

        //Floats
        PUSHF, 0x00, 0x00, 0x80, 0x41,
        PRINTF,
        PUSHF, 0x66, 0xE6, 0xF6, 0x42,
        PRINTF,

        //Halt
        HALT
        };
    output_to_binary_file("Basics.bin", basics_vec);

    //Math.bin - ADD, SUB, MUL, DIV
    std::vector<unsigned char> math_vec {
        //Char ADD
        PUSHC, 5,
        PUSHC, 7,
        ADD,
        PRINTC,

        //Char SUB
        PUSHC, 11,
        PUSHC, 10,
        SUB,
        PRINTC,

        //Char MUL
        PUSHC, 5,
        PUSHC, 5,
        MUL,
        PRINTC,

        //Char DIV
        PUSHC, 30,
        PUSHC, 6,
        DIV,
        PRINTC,

        //Short ADD
        PUSHS, 00, 2,
        PUSHS, 00, 1,
        ADD,
        PRINTS,

        //Short SUB
        PUSHS, 11, 00,
        PUSHS, 10, 00,
        SUB,
        PRINTS,

        //Short MUL
        PUSHS, 20, 00,
        PUSHS, 16, 00,
        MUL,
        PRINTS,

        //Short DIV
        PUSHS, 45, 00,
        PUSHS,  9, 00,
        DIV,
        PRINTS,

        //Int ADD
        PUSHI, 00, 01, 00, 00,
        PUSHI, 00, 01, 00, 00,
        ADD,
        PRINTI,

        //Int SUB
        PUSHI, 00, 00, 10, 00,
        PUSHI, 00, 00,  9, 00,
        SUB,
        PRINTI,

        //Int MUL
        PUSHI, 64, 00, 00, 00,
        PUSHI, 64, 00, 00, 00,
        MUL,
        PRINTI,

        //Int DIV
        PUSHI, 00, 16, 00, 00,
        PUSHI, 00, 01, 00, 00,
        DIV,
        PRINTI,

        //Float ADD
        PUSHF, 0x85, 0xEB, 0x55, 0x41, // 13.37
        PUSHF, 0x8f, 0xC2, 0x31, 0x42, // 44.44
        ADD,
        PRINTF,

        //Float SUB
        PUSHF, 0x85, 0xEB, 0x55, 0x41,
        PUSHF, 0x8f, 0xC2, 0x31, 0x42,
        SUB,
        PRINTF,

        //Float MUL
        PUSHF, 0x85, 0xEB, 0x55, 0x41,
        PUSHF, 0x8f, 0xC2, 0x31, 0x42,
        MUL,
        PRINTF,

        //Float DIV
        PUSHF, 0x85, 0xEB, 0x55, 0x41,
        PUSHF, 0x8f, 0xC2, 0x31, 0x42,
        DIV,
        PRINTF,

        //HALT
        0
    };
    output_to_binary_file("Math.bin", math_vec);

    //Comparisons.bin - CMPE, CMPLT, CMPGT
    std::vector<unsigned char> comparisons_vec {
        //CMPE
        PUSHI, 05, 00, 00, 00,
        PUSHI, 04, 00, 00, 00,
        CMPE,
        PRINTI,

        PUSHI, 04, 00, 00, 00,
        PUSHI, 04, 00, 00, 00,
        CMPE,
        PRINTI,

        //CMPLT
        PUSHI, 05, 00, 00, 00,
        PUSHI, 04, 00, 00, 00,
        CMPLT,
        PRINTI,

        PUSHI, 04, 00, 00, 00,
        PUSHI, 05, 00, 00, 00,
        CMPLT,
        PRINTI,

        PUSHI, 04, 00, 00, 00,
        PUSHI, 04, 00, 00, 00,
        CMPLT,
        PRINTI,

        //CMPGT
        PUSHI, 05, 00, 00, 00,
        PUSHI, 04, 00, 00, 00,
        CMPGT,
        PRINTI,

        PUSHI, 04, 00, 00, 00,
        PUSHI, 05, 00, 00, 00,
        CMPGT,
        PRINTI,

        PUSHI, 04, 00, 00, 00,
        PUSHI, 04, 00, 00, 00,
        CMPGT,
        PRINTI,

        //HALT
        HALT
    };
    output_to_binary_file("Comparisons.bin", comparisons_vec);

    //Jumps.bin - JMP, JMPC
    std::vector<unsigned char> jumps_vec {
        PUSHI, 10, 00, 00, 00, // PC 0 - 4
        JMP, // PC 5
        0, 0, 0, 0, // PC 6-9
        PUSHI, 1, 0, 0, 0, // PC 10 - 14
        PRINTI, // 15
        PUSHI, 4, 0, 0, 0, // PC 16 - 20
        PUSHI, 5, 0, 0, 0, // PC 21 - 25
        CMPGT, // PC 26
        PUSHI, 6, 0, 0, 0, // PC 27 - 31
        JMPC, // PC 32
        PUSHI, 2, 0, 0, 0, // PC 33 - 37
        PRINTI, //PC 38
        PUSHI, 4, 0, 0, 0, // PC 39 - 43
        PUSHI, 5, 0, 0, 0, // PC 44 - 48
        CMPLT, // PC 49
        PUSHI, 57, 0, 0, 0, //PC 50 - 54
        JMPC, // PC 55
        HALT, // PC 56
        PUSHI, 3, 0, 0, 0, // PC 57 - 61
        PRINTI, // PC 62
        HALT // PC 63
    };
    output_to_binary_file("Jumps.bin", jumps_vec);

//    //Subroutines.bin - CALL, RET
//    std::vector<unsigned char> subroutines_vec {
//
//    };
//    output_to_binary_file("Subroutines.bin", subroutines_vec);
//
//    //Push_Pop.bin - PUSHV, POPM, POPV, POPA
//    std::vector<unsigned char> push_pop_vec {
//
//    };
//    output_to_binary_file("Push_Pop.bin", push_pop_vec);
//
//    //Peek_Poke.bin - PEEK, POKE
//    std::vector<unsigned char> peek_poke_vec {
//
//    };
//    output_to_binary_file("Peek_Poke.bin", peek_poke_vec);

    return 0;
}