//
// Created by czarhrs on 10/10/24.
//

#ifndef REGISTER_BANK_H
#define REGISTER_BANK_H

#include <iomanip>
#include <iostream>
#include "REGISTER.h"
#include <functional>
#include <map>

using namespace std;

struct REGISTER_BANK {
    //registradores de uso especifico
    REGISTER pc, mar, cr, epc, sr;                      // program counter, memory address register, cause register, exception program counter, status register
    REGISTER hi, lo; 
    REGISTER ir;                                   // registradores usados para armazenar os resultados de operações de multiplicação e divisão (resultado de 64 bits dividido em dois registradores de 32 bits)
    //registradores de uso geral

    REGISTER zero;                                      // sempre é igual a 0
    REGISTER at;                                        // registrador reservado para o assembler
    REGISTER v0, v1;                                    // usados para armazenar valores de retorno de funções
    REGISTER a0, a1, a2, a3;                            // argumentos para chamadas de função
    REGISTER t0, t1, t2, t3, t4, t5, t6, t7, t8, t9;    // registradores temporários
    REGISTER s0, s1, s2, s3, s4, s5, s6, s7;            // registradores salvos (mantêm o valor entre chamadas de função)
    REGISTER k0, k1;                                    // registradores reservados para o sistema operacional (tratamento de interrupções)
    REGISTER gp, sp, fp, ra;                            // global pointer, stack pointer, frame pointer, return address

    map<string, function<uint32_t()>> acessoLeituraRegistradores;
    map<string, function<void(uint32_t)>> acessoEscritaRegistradores;

    REGISTER_BANK(){

        acessoLeituraRegistradores["hi"] = [this](){ return this->hi.read(); };
        acessoLeituraRegistradores["mar"] = [this](){ return this->mar.read(); };
        acessoLeituraRegistradores["pc"] = [this](){ return this->pc.read(); };
        acessoLeituraRegistradores["cr"] = [this](){ return this->cr.read(); };
        acessoLeituraRegistradores["epc"] = [this](){ return this->epc.read(); };
        acessoLeituraRegistradores["sr"] = [this](){ return this->sr.read(); };
        acessoLeituraRegistradores["lo"] = [this](){ return this->lo.read(); };
        acessoLeituraRegistradores["ir"] = [this](){ return this->ir.read(); };
        acessoLeituraRegistradores["zero"] = [this](){ return this->zero.read(); };
        acessoLeituraRegistradores["at"] = [this](){ return this->at.read(); };
        acessoLeituraRegistradores["v0"] = [this](){ return this->v0.read(); };
        acessoLeituraRegistradores["v1"] = [this](){ return this->v1.read(); };
        acessoLeituraRegistradores["a0"] = [this](){ return this->a0.read(); };
        acessoLeituraRegistradores["a1"] = [this](){ return this->a1.read(); };
        acessoLeituraRegistradores["a2"] = [this](){ return this->a2.read(); };
        acessoLeituraRegistradores["a3"] = [this](){ return this->a3.read(); };
        acessoLeituraRegistradores["t0"] = [this](){ return this->t0.read(); };
        acessoLeituraRegistradores["t1"] = [this](){ return this->t1.read(); };
        acessoLeituraRegistradores["t2"] = [this](){ return this->t2.read(); };
        acessoLeituraRegistradores["t3"] = [this](){ return this->t3.read(); };
        acessoLeituraRegistradores["t4"] = [this](){ return this->t4.read(); };
        acessoLeituraRegistradores["t5"] = [this](){ return this->t5.read(); };
        acessoLeituraRegistradores["t6"] = [this](){ return this->t6.read(); };
        acessoLeituraRegistradores["t7"] = [this](){ return this->t7.read(); };
        acessoLeituraRegistradores["t8"] = [this](){ return this->t8.read(); };
        acessoLeituraRegistradores["t9"] = [this](){ return this->t9.read(); };
        acessoLeituraRegistradores["s0"] = [this](){ return this->s0.read(); };
        acessoLeituraRegistradores["s1"] = [this](){ return this->s1.read(); };
        acessoLeituraRegistradores["s2"] = [this](){ return this->s2.read(); };
        acessoLeituraRegistradores["s3"] = [this](){ return this->s3.read(); };
        acessoLeituraRegistradores["s4"] = [this](){ return this->s4.read(); };
        acessoLeituraRegistradores["s5"] = [this](){ return this->s5.read(); };
        acessoLeituraRegistradores["s6"] = [this](){ return this->s6.read(); };
        acessoLeituraRegistradores["s7"] = [this](){ return this->s7.read(); };
        acessoLeituraRegistradores["k0"] = [this](){ return this->k0.read(); };
        acessoLeituraRegistradores["k1"] = [this](){ return this->k1.read(); };
        acessoLeituraRegistradores["gp"] = [this](){ return this->gp.read(); };
        acessoLeituraRegistradores["sp"] = [this](){ return this->sp.read(); };
        acessoLeituraRegistradores["fp"] = [this](){ return this->fp.read(); };
        acessoLeituraRegistradores["ra"] = [this](){ return this->ra.read(); };

        acessoEscritaRegistradores["hi"] = [this](uint32_t val) { this->hi.value = val; };
        acessoEscritaRegistradores["mar"] = [this](uint32_t val) { this->mar.value = val; };
        acessoEscritaRegistradores["pc"] = [this](uint32_t val) { this->pc.value = val; };
        acessoEscritaRegistradores["cr"] = [this](uint32_t val) { this->cr.value = val; };
        acessoEscritaRegistradores["epc"] = [this](uint32_t val) { this->epc.value = val; };
        acessoEscritaRegistradores["sr"] = [this](uint32_t val) { this->sr.value = val; };
        acessoEscritaRegistradores["lo"] = [this](uint32_t val) { this->lo.value = val; };
        acessoEscritaRegistradores["ir"] = [this](uint32_t val) { this->ir.value = val; };
        acessoEscritaRegistradores["zero"] = [this](uint32_t val) { this->zero.value = val; };
        acessoEscritaRegistradores["at"] = [this](uint32_t val) { this->at.value = val; };
        acessoEscritaRegistradores["v0"] = [this](uint32_t val) { this->v0.value = val; };
        acessoEscritaRegistradores["v1"] = [this](uint32_t val) { this->v1.value = val; };
        acessoEscritaRegistradores["a0"] = [this](uint32_t val) { this->a0.value = val; };
        acessoEscritaRegistradores["a1"] = [this](uint32_t val) { this->a1.value = val; };
        acessoEscritaRegistradores["a2"] = [this](uint32_t val) { this->a2.value = val; };
        acessoEscritaRegistradores["a3"] = [this](uint32_t val) { this->a3.value = val; };
        acessoEscritaRegistradores["t0"] = [this](uint32_t val) { this->t0.value = val; };
        acessoEscritaRegistradores["t1"] = [this](uint32_t val) { this->t1.value = val; };
        acessoEscritaRegistradores["t2"] = [this](uint32_t val) { this->t2.value = val; };
        acessoEscritaRegistradores["t3"] = [this](uint32_t val) { this->t3.value = val; };
        acessoEscritaRegistradores["t4"] = [this](uint32_t val) { this->t4.value = val; };
        acessoEscritaRegistradores["t5"] = [this](uint32_t val) { this->t5.value = val; };
        acessoEscritaRegistradores["t6"] = [this](uint32_t val) { this->t6.value = val; };
        acessoEscritaRegistradores["t7"] = [this](uint32_t val) { this->t7.value = val; };
        acessoEscritaRegistradores["t8"] = [this](uint32_t val) { this->t8.value = val; };
        acessoEscritaRegistradores["t9"] = [this](uint32_t val) { this->t9.value = val; };
        acessoEscritaRegistradores["s0"] = [this](uint32_t val) { this->s0.value = val; };
        acessoEscritaRegistradores["s1"] = [this](uint32_t val) { this->s1.value = val; };
        acessoEscritaRegistradores["s2"] = [this](uint32_t val) { this->s2.value = val; };
        acessoEscritaRegistradores["s3"] = [this](uint32_t val) { this->s3.value = val; };
        acessoEscritaRegistradores["s4"] = [this](uint32_t val) { this->s4.value = val; };
        acessoEscritaRegistradores["s5"] = [this](uint32_t val) { this->s5.value = val; };
        acessoEscritaRegistradores["s6"] = [this](uint32_t val) { this->s6.value = val; };
        acessoEscritaRegistradores["s7"] = [this](uint32_t val) { this->s7.value = val; };
        acessoEscritaRegistradores["k0"] = [this](uint32_t val) { this->k0.value = val; };
        acessoEscritaRegistradores["k1"] = [this](uint32_t val) { this->k1.value = val; };
        acessoEscritaRegistradores["gp"] = [this](uint32_t val) { this->gp.value = val; };
        acessoEscritaRegistradores["sp"] = [this](uint32_t val) { this->sp.value = val; };
        acessoEscritaRegistradores["fp"] = [this](uint32_t val) { this->fp.value = val; };
        acessoEscritaRegistradores["ra"] = [this](uint32_t val) { this->ra.value = val; };

    }

    void print_registers() const;
};



#endif //REGISTER_BANK_H
