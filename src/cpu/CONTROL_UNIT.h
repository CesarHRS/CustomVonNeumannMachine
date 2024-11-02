#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

#include <iostream>
#include"ALU.h"
#include"REGISTER_BANK.h"
#include <string>
#include <vector>
#include"HashRegister.h"
#include"unordered_map"

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

    
    const unordered_map<string, string> instructionMap = {
        {"add", "0b0000"},
        {"and", "0b0001"},
        {"div", "0b0010"},
        {"mult", "0b0011"},
        {"sub", "0b0100"},
        {"beq", "0b0101"},
        {"bne", "0b0110"},
        {"bgt", "0b0111"},
        {"bgti", "0b1000"},
        {"blt", "0b1001"},
        {"blti", "0b1010"},
        {"j", "0b1011"},
        {"lw", "0b1100"},
        {"sw", "0b1101"},
        {"li", "0b1110"},
        {"la", "0b1111"},
        {"print", "0b10000"}
    };

    // principais operações de uma unidade de controle
    void Execute_Operation(REGISTER_BANK &registers,Temporary_Data &data);
    string Pick_Adress_Result(const uint32_t instruction);
    string Pick_Code_Register_Load(const uint32_t instruction);
    string Pick_Third_Code_Register(const uint32_t instruction);
    string Pick_Second_Code_Register(const uint32_t instruction);
    string Pick_First_Code_Register(const uint32_t instruction);
    string Identificacao_instrucao(const uint32_t instruction, REGISTER_BANK &registers);
    void Fetch(REGISTER_BANK &registers, bool &endProgram);
    void Decode(REGISTER_BANK &registers, Temporary_Data &data);
    void Execute_Aritmetic_Operation(REGISTER_BANK &registers,Temporary_Data &data);
    void Execute_Loop_Operation(REGISTER_BANK &registers,Temporary_Data &data, int &counter); 
    void Execute(REGISTER_BANK &registers, Temporary_Data &data, int &counter);
    void Memory_Acess(REGISTER_BANK &registers,Temporary_Data &data);
    void Write_Back(Temporary_Data &data);
};

#endif;
