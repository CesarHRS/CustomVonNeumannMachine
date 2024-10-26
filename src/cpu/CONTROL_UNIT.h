#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

#include <iostream>
#include"ALU.h"
#include"REGISTER_BANK.h"
#include <string>
#include <vector>
#include"HashRegister.h"

using namespace std;

struct Temporary_Data{
    string code_first_register;
    string code_second_register;
    string code_third_register;
    string tarefa_a_ser_feita_pela_ula;
    string addressRAMResult;
};
struct Control_Unit{

    operation op;

    vector<Temporary_Data> data;

    // principais operações de uma unidade de controle
    string Pick_Adress_Result(const uint32_t instruction);
    string Pick_Code_Register_Load(const uint32_t instruction);
    string Pick_Third_Code_Register(const uint32_t instruction);
    string Pick_Second_Code_Register(const uint32_t instruction);
    string Pick_First_Code_Register(const uint32_t instruction);
    string Identificacao_instrucao(const uint32_t instruction, REGISTER_BANK &registers);
    void Fetch(REGISTER_BANK &registers);
    void Decode(REGISTER_BANK &registers, Temporary_Data &data);
    void Execute_Aritmetic_Operation(REGISTER_BANK &registers,Temporary_Data &data);
    void Execute(REGISTER_BANK &registers, Temporary_Data &data);
    void Memory_Acess(REGISTER_BANK &registers,Temporary_Data &data);
    void Write_Back(Temporary_Data &data);
};

#endif;