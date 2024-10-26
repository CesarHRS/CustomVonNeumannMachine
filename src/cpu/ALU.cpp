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
        case BME:
            result = A < B;
        break;
        case BMA:
            result = A > B;
        break;
        case BMAI:
            result = A >= B;
        break;
        case BMEI:
            result = A <= B;
        break;
        default:
            cerr << "ULA: INVALID OPERATION!" << endl;
        break;
    }
}
