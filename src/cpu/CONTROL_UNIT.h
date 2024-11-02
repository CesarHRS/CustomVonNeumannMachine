#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

#include <iostream>
#include"ALU.h"
#include"REGISTER_BANK.h"
#include <string>
#include <vector>
#include"HashRegister.h"

using namespace std;

struct Instruction_Data{
    string source_register;
    string target_register;
    string destination_register;
    string op;
    string addressRAMResult;
};
struct Control_Unit{

    operation op;

    vector<Instruction_Data> data;
   
    unordered_map<string, string> instructionMap = {
        {"add", "000000"},
        {"and", "000001"},
        {"div", "000010"},
        {"mult","000011"},
        {"sub", "000100"},
        {"beq", "000101"},
        {"bne", "000110"},
        {"bgt", "000111"},
        {"bgti","001000"},
        {"blt", "001001"},
        {"blti","001010"},
        {"j", "001011"},
        {"lw", "001100"},
        {"sw", "001101"},
        {"li", "001110"},
        {"la", "001111"},
        {"print", "010000"},
        {"end", "111111"}
    };

    string Get_immediate(const uint32_t instruction);
    string Pick_Code_Register_Load(const uint32_t instruction);
    string Get_destination_Register(const uint32_t instruction);
    string Get_target_Register(const uint32_t instruction);
    string Get_source_Register(const uint32_t instruction);

    string Identificacao_instrucao(const uint32_t instruction, REGISTER_BANK &registers);
    void Fetch(REGISTER_BANK &registers, bool &endProgram);
    void Decode(REGISTER_BANK &registers, Instruction_Data &data);
    void Execute_Aritmetic_Operation(REGISTER_BANK &registers,Instruction_Data &data);
    void Execute_Operation(REGISTER_BANK &registers,Instruction_Data &data);
    void Execute_Loop_Operation(REGISTER_BANK &registers,Instruction_Data &data, int &counter); 
    void Execute(REGISTER_BANK &registers, Instruction_Data &data, int &counter);
    void Memory_Acess(REGISTER_BANK &registers,Instruction_Data &data);
    void Write_Back(Instruction_Data &data);
};

#endif;
