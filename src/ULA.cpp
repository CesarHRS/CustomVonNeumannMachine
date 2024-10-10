#include "ULA.h"

void ULA::calculate() {
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
        case AND:
            result = A & B;
        break;
        case OR:
            result = A | B;
        break;
        case XOR:
            result = A ^ B;
        break;
        case NOT_A:
            result = ~A;
        break;
        case SLT:
            result = (A < B) ? 1 : 0;
        break;
        case A:
            result = A;
        break;
        case SHR:
            result = A >> B;
        break;
        case SHL:
            result = A << B;
        break;
        default:
            cerr << "ULA: INVALID OPERATION!" << endl;
        break;
    }
}
