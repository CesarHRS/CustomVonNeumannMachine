//
// Created by czarhrs on 10/10/24.
//

#ifndef ALU_H
#define ALU_H
#include <iostream>
using namespace std;

enum operation {
    ADD,
    SUB,
    AND,
    OR,
    XOR,
    NOT_A,      // NOT A
    SLT,        //(A < B)
    PASS_A,     // PASS A
    SHR,        // SHIFT RIGHT
    SHL         // SHIFT LEFT
};

struct ALU {
    int32_t A;
    int32_t B;
    int32_t result;
    bool overflow;
    operation op;

    void calculate();
};
#endif //ALU_H
