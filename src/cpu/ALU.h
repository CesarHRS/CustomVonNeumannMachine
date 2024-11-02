//
// Created by czarhrs on 10/10/24.
//

#ifndef ALU_H
#define ALU_H
#include <iostream>
#include <any>
#include <cstdint>
using namespace std;

enum operation {
    ADD,
    SUB,
    MUL,
    DIV,
    BEQ,
    BNE,
    BLT,
    BGT,
    BGTI,
    BLTI,
    LW,
    LA,
    ST      
};

struct ALU {
    uint32_t A;
    uint32_t B;
    int32_t result;
    bool overflow;
    operation op;

    void calculate();
};
#endif //ALU_H
