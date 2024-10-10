//
// Created by czarhrs on 10/10/24.
//

#ifndef REGISTER_BANK_H
#define REGISTER_BANK_H

#include <iomanip>

#include "REGISTER.h"
using namespace std;

struct REGISTER_BANK {
    //registradores de uso especifico
    REGISTER pc, mar, cr, epc, sr;                      // program counter, memory address register, cause register, exception program counter, status register
    REGISTER hi, lo;                                    // registradores usados para armazenar os resultados de operações de multiplicação e divisão (resultado de 64 bits dividido em dois registradores de 32 bits)
    //registradores de uso geral

    REGISTER zero;                                      // sempre é igual a 0
    REGISTER at;                                        // registrador reservado para o assembler
    REGISTER v0, v1;                                    // usados para armazenar valores de retorno de funções
    REGISTER a0, a1, a2, a3;                            // argumentos para chamadas de função
    REGISTER t0, t1, t2, t3, t4, t5, t6, t7, t8, t9;    // registradores temporários
    REGISTER s0, s1, s2, s3, s4, s5, s6, s7;            // registradores salvos (mantêm o valor entre chamadas de função)
    REGISTER k0, k1;                                    // registradores reservados para o sistema operacional (tratamento de interrupções)
    REGISTER gp, sp, fp, ra;                            // global pointer, stack pointer, frame pointer, return address

    void print_registers() const;
};



#endif //REGISTER_BANK_H
