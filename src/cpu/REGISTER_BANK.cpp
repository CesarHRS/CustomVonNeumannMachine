//
// Created by czarhrs on 10/10/24.
//

#include "REGISTER_BANK.h"

void REGISTER_BANK::print_registers() const {
    cout << hex << setfill('0');

    // Registradores de uso específico
    cout << "$pc: " << setw(8) << pc.read() << endl;
    cout << "$mar: " << setw(8) << mar.read() << endl;
    cout << "$cr: " << setw(8) << cr.read() << endl;
    cout << "$epc: " << setw(8) << epc.read() << endl;
    cout << "$sr: " << setw(8) << sr.read() << endl;
    cout << "$hi: " << setw(8) << hi.read() << endl;
    cout << "$lo: " << setw(8) << lo.read() << endl;
    cout << "$ir: " << setw(8) << ir.read() << endl;


    // Registradores de uso geral
    cout << "$zero: " << setw(8) << zero.read() << endl;
    cout << "$at: " << setw(8) << at.read() << endl;
    cout << "$v0: " << setw(8) << v0.read() << endl;
    cout << "$v1: " << setw(8) << v1.read() << endl;
    cout << "$a0: " << setw(8) << a0.read() << endl;
    cout << "$a1: " << setw(8) << a1.read() << endl;
    cout << "$a2: " << setw(8) << a2.read() << endl;
    cout << "$a3: " << setw(8) << a3.read() << endl;

    cout << "$t0: " << setw(8) << t0.read() << endl;
    cout << "$t1: " << setw(8) << t1.read() << endl;
    cout << "$t2: " << setw(8) << t2.read() << endl;
    cout << "$t3: " << setw(8) << t3.read() << endl;
    cout << "$t4: " << setw(8) << t4.read() << endl;
    cout << "$t5: " << setw(8) << t5.read() << endl;
    cout << "$t6: " << setw(8) << t6.read() << endl;
    cout << "$t7: " << setw(8) << t7.read() << endl;
    cout << "$t8: " << setw(8) << t8.read() << endl;
    cout << "$t9: " << setw(8) << t9.read() << endl;

    cout << "$s0: " << setw(8) << s0.read() << endl;
    cout << "$s1: " << setw(8) << s1.read() << endl;
    cout << "$s2: " << setw(8) << s2.read() << endl;
    cout << "$s3: " << setw(8) << s3.read() << endl;
    cout << "$s4: " << setw(8) << s4.read() << endl;
    cout << "$s5: " << setw(8) << s5.read() << endl;
    cout << "$s6: " << setw(8) << s6.read() << endl;
    cout << "$s7: " << setw(8) << s7.read() << endl;

    cout << "$k0: " << setw(8) << k0.read() << endl;
    cout << "$k1: " << setw(8) << k1.read() << endl;

    cout << "$gp: " << setw(8) << gp.read() << endl;
    cout << "$sp: " << setw(8) << sp.read() << endl;
    cout << "$fp: " << setw(8) << fp.read() << endl;
    cout << "$ra: " << setw(8) << ra.read() << endl;
}
