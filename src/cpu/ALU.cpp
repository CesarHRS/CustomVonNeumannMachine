#include "ALU.h"

void ALU::calculate() {
    overflow = false;

    switch (op) {
        case ADD:
            result = A + B;
        if ((A > 0 && B > 0 && result < 0) || (A < 0 && B < 0 && result > 0)) {
            overflow = true;
        }
        break;
        case SUB:
            result = A - B;
        if ((A > 0 && B < 0 && result < 0) || (A < 0 && B > 0 && result > 0)) {
            overflow = true;
        }
        break;
        case MUL:
            result = A * B;
        break;
        case DIV:
            if (B == 0) {
                cerr << "ULA: DIVISION BY ZERO!" << endl;
                return;
            }
            result = A / B;
        break;
        case BEQ:
            result = A == B;
        break;
        case BNE:
            result = A != B;
        break;
        case BLT:
            result = A < B;
        break;
        case BGT:
            result = A > B;
        break;
        case BGTI:
            result = A >= B;
        break;
        case BLTI:
            result = A <= B;
        break;
        default:
            cerr << "ULA: INVALID OPERATION!" << endl;
        break;
    }
}
