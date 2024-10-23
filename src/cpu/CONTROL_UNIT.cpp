#include "CONTROL_UNIT.h"

//PIPELINE

void Control_Unit::Fetch(REGISTER_BANK &registers){
    //Aqui são as ações para colocar a próxima instrução de prontidão
    registers.mar.write(registers.pc.value);
    //chamar a memória com a posição do pc e inserir em um registrador
    //registers.ir.write(aqui tem de ser passado a instrução que estiver na RAM);
    registers.pc.write(registers.pc.value += 1);//incrementando o pc  
}

void Control_Unit::Decode(REGISTER_BANK &registers, Temporary_Data &data){
    //Daqui vai ter de ser identificado o que fazer

    const uint32_t instruction = registers.ir.read();
    // tenho de converte o valor de 32 bits para binario e separar cada uma das partes para fazer a análise


    data.tarefa_a_ser_feita_pela_ula = Identificacao_instrucao(instruction,registers);
    if(data.tarefa_a_ser_feita_pela_ula != "LOAD" && data.tarefa_a_ser_feita_pela_ula != "LOADV" && data.tarefa_a_ser_feita_pela_ula != "STORE" && data.tarefa_a_ser_feita_pela_ula != "JUMP"){
        // se entrar aqui é porque tem de carregar registradores, que estão especificados na instrução
        data.code_first_register = Pick_First_Code_Register(instruction);
        data.code_second_register = Pick_Second_Code_Register(instruction);
        data.code_third_register = Pick_Third_Code_Register(instruction);
    }else if(data.tarefa_a_ser_feita_pela_ula != "LOAD" && data.tarefa_a_ser_feita_pela_ula != "LOADV")
    {
        data.code_first_register = Pick_Code_Register_Load(instruction);
    }

    return;
}

void Control_Unit::Execute(REGISTER_BANK &registers,Temporary_Data &data){
    /*Daqui tem de ser chamado o que tiver de ser chamado, 
    aqui tem de ser consultado a instrução que será feita,
    para saber se por exemplo vai ser feita uma multiplicação ou divisão*/

    if(data.tarefa_a_ser_feita_pela_ula != "LOAD" && data.tarefa_a_ser_feita_pela_ula != "LOADV" && data.tarefa_a_ser_feita_pela_ula != "STORE" && data.tarefa_a_ser_feita_pela_ula != "JUMP"){
        Execute_AritmeticOrLogical_Operation(registers, data);
    }    
}

void Control_Unit::Memory_Acess(){

}

void Control_Unit::Write_Back(){

}

string Control_Unit::Identificacao_instrucao(const uint32_t instruction, REGISTER_BANK &registers){


    //instrução do tipo j
        string string_instruction = to_string(instruction);
        char first_check = 'x'; // → indica que tem endereço na instrução
        char second_check = 'v'; // → indica que tem endereço na instrução
        string instruction_type = "";

    if(string_instruction.find(first_check) != string::npos){
        //instrução do tipo j
        if(string_instruction.find(second_check) != string::npos){
            // LOAD de vetor
            instruction_type = "LOADV";
        }
        else if(string_instruction.find("100011") != string::npos){
            // LOAD
            instruction_type = "LOAD";
        }else{
            // STORE
            instruction_type = "STORE";
        }
    }else{

        //identificação das instruções do tipo R

        unsigned long long int opcode = instruction & 0b11111100000000000000000000111111;

        switch (opcode)
        {
        case 0b00000000000000000000000000100000:
            //instrução de ADD 
            instruction_type = "ADD";
            break;

        case 0b00000000000000000000000000100010:
            //instrução de SUB
            instruction_type = "SUB";
            break;

        case 0b00000000000000000000000000011000:
            //instrução de MUL
            instruction_type = "MUL";
            break;


        case 0b00000000000000000000000000100101:
            //instrução de AND
            instruction_type = "AND";
            break;

        case 0b00000000000000000000000000100100:
            //instrução de OR
            instruction_type = "OR";
            break;

        case 0b00000000000000000000000000100110:
            //instrução de XOR
            instruction_type = "XOR";
            break;

        case 0b00000000000000000000000000011010:
            //instrução de DIV, neste caso teremos registradores especificos a serem usados
            instruction_type = "DIV";
            break;

        default:

            // instruções do tipo J → a única no nosso caso é a instrução de JUMP    
                
            break;
        }
    }


} 

string Control_Unit::Pick_Code_Register_Load(const uint32_t instruction){

    string copia_instrucao = to_string(instruction);
    string code;
    for(int i = 8; i < 13; i++){
        code[i] = copia_instrucao[i];
    }

    return code;

}

string Control_Unit::Pick_Third_Code_Register(const uint32_t instruction){
    string copia_instrucao = to_string(instruction);
    string code;
    for(int i = 18; i < 23; i++){
        code[i] = copia_instrucao[i];
    }

    return code;
}

string Control_Unit::Pick_Second_Code_Register(const uint32_t instruction){
    string copia_instrucao = to_string(instruction);
    string code;
    for(int i = 13; i < 18; i++){
        code[i] = copia_instrucao[i];
    }

    return code;
}

string Control_Unit::Pick_First_Code_Register(const uint32_t instruction){
    string copia_instrucao = to_string(instruction);
    string code;
    for(int i = 8; i < 13; i++){
        code[i] = copia_instrucao[i];
    }

    return code;
}

void Execute_AritmeticOrLogical_Operation(REGISTER_BANK &registers,Temporary_Data &data){

        ALU alu;
        if(data.tarefa_a_ser_feita_pela_ula == "ADD"){
            alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
            alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
            alu.op = ADD;
            alu.calculate();
        }else if(data.tarefa_a_ser_feita_pela_ula == "SUB"){
            alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
            alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
            alu.op = SUB;
            alu.calculate();
        }else if(data.tarefa_a_ser_feita_pela_ula == "MUL"){
            alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
            alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
            alu.op = MUL;
            alu.calculate();
        }else if(data.tarefa_a_ser_feita_pela_ula == "AND"){
            alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
            alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
            alu.op = AND;
            alu.calculate();
        }else if(data.tarefa_a_ser_feita_pela_ula == "OR"){
            alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
            alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
            alu.op = OR;
            alu.calculate();
        }else if(data.tarefa_a_ser_feita_pela_ula == "XOR"){
            alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
            alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
            alu.op = XOR;
            alu.calculate();
        }else if(data.tarefa_a_ser_feita_pela_ula == "DIV"){
            alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
            alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
            alu.op = DIV;
            alu.calculate();
        }
}

