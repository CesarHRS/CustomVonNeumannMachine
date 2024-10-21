#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

#include <iostream>
#include"ALU.h"
#include"REGISTER_BANK.h"
#include <string>

using namespace std;


struct Control_Unit{

    operation op;

    void Unit_Control(const uint32_t opcode);

    // principais operações de uma unidade de controle
    void Identificacao_instrucao(const uint32_t instruction, REGISTER_BANK &registers);
    void Load(REGISTER_BANK &registers);
    void Fetch(REGISTER_BANK &registers);
    void Decode(REGISTER_BANK &registers);
    void Execute();
    void Memory_Acess();
    void Write_Back();
};

#endif