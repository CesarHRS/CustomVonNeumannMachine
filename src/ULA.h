//
// Created by czarhrs on 10/10/24.
//

#ifndef ULA_H
#define ULA_H
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
    A,          // PASS A
    SHR,        // SHIFT RIGHT
    SHL         // SHIFT LEFT
};

struct ULA {
    int32_t A;
    int32_t B;
    int32_t result;
    bool overflow;
    operation op;

    void calculate();
};
#endif //ULA_H
