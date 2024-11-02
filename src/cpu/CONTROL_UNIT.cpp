#include "CONTROL_UNIT.h"

//PIPELINE

void Control_Unit::Fetch(REGISTER_BANK &registers, bool &endProgram){
    const uint32_t instruction = registers.ir.read();
    if(instruction == 00000000000000000000000000001100)
    {
        endProgram = true;
        return;
    }
    registers.mar.write(registers.pc.value);
    //chamar a memória com a posição do pc e inserir em um registrador
    //registers.ir.write(aqui tem de ser passado a instrução que estiver na RAM);
    registers.pc.write(registers.pc.value += 1);//incrementando o pc 
}

void Control_Unit::Decode(REGISTER_BANK &registers, Temporary_Data &data){
    //Daqui vai ter de ser identificado o que fazer

    const uint32_t instruction = registers.ir.read();


    data.tarefa_a_ser_feita_pela_ula = Identificacao_instrucao(instruction,registers);
    if(data.tarefa_a_ser_feita_pela_ula != "LW" && data.tarefa_a_ser_feita_pela_ula != "LA" && data.tarefa_a_ser_feita_pela_ula != "ST" &&  data.tarefa_a_ser_feita_pela_ula != "BLT" && data.tarefa_a_ser_feita_pela_ula != "BGT" && data.tarefa_a_ser_feita_pela_ula != "BGTI" && data.tarefa_a_ser_feita_pela_ula != "BLTI"){
        // se entrar aqui é porque tem de carregar registradores, que estão especificados na instrução
        data.code_first_register = Pick_First_Code_Register(instruction);
        data.code_second_register = Pick_Second_Code_Register(instruction);
        data.code_third_register = Pick_Third_Code_Register(instruction);
        data.addressRAMResult = Pick_Adress_Result(instruction);

    }else if(data.tarefa_a_ser_feita_pela_ula == "LW" && data.tarefa_a_ser_feita_pela_ula == "LA" && data.tarefa_a_ser_feita_pela_ula == "ST")
    {
        data.code_first_register = Pick_Code_Register_Load(instruction);
        data.addressRAMResult = Pick_Adress_Result(instruction);
    }else if(data.tarefa_a_ser_feita_pela_ula == "BLT" && data.tarefa_a_ser_feita_pela_ula == "BGT" && data.tarefa_a_ser_feita_pela_ula == "BGTI" && data.tarefa_a_ser_feita_pela_ula == "BLTI"){
        data.code_first_register = Pick_First_Code_Register(instruction);
        data.code_second_register = Pick_Second_Code_Register(instruction);
        data.addressRAMResult = Pick_Adress_Result(instruction);
    }

    return;
}

void Control_Unit::Execute(REGISTER_BANK &registers,Temporary_Data &data, int &counter){
    /*Daqui tem de ser chamado o que tiver de ser chamado*/

    if(data.tarefa_a_ser_feita_pela_ula == "ADD" ||  data.tarefa_a_ser_feita_pela_ula == "SUB" || data.tarefa_a_ser_feita_pela_ula == "MUL" || data.tarefa_a_ser_feita_pela_ula == "DIV"){
        Execute_Aritmetic_Operation(registers, data);
    }else if(data.tarefa_a_ser_feita_pela_ula == "BEQ" || data.tarefa_a_ser_feita_pela_ula == "BNE" || data.tarefa_a_ser_feita_pela_ula == "BGT" || data.tarefa_a_ser_feita_pela_ula == "BGTI" || data.tarefa_a_ser_feita_pela_ula == "BLT" || data.tarefa_a_ser_feita_pela_ula == "BLTI"){
        Execute_Loop_Operation(registers, data, counter);
    }
    else if(data.tarefa_a_ser_feita_pela_ula == "PRINT" ){
        
    }
}

void Control_Unit::Memory_Acess(REGISTER_BANK &registers,Temporary_Data &data){

    //aqui devem ser executadas as intruções de LOAD de fato
    if(data.tarefa_a_ser_feita_pela_ula == "LW"){
        //aqui tem de ser feito a leitura na RAM
        //registers.acessoEscritaRegistradores[data.code_first_register] = Ram.insert[data.addressRAMResult];
    }if(data.tarefa_a_ser_feita_pela_ula == "LA"){
        Execute_Operation(registers,data);
    }
}

void Control_Unit::Write_Back(Temporary_Data &data){

    //aqui devem ocorrer qualquer uma das intruções de escrita na RAM
    if(data.tarefa_a_ser_feita_pela_ula == "ST"){
        //aqui tem de ser feito a escrita na RAM
        //memory.InsertData(data, row, col) = registers.acessoLeituraRegistradores[data.code_third_register]();
    }

    return;

}

string Control_Unit::Identificacao_instrucao(const uint32_t instruction, REGISTER_BANK &registers){


    //instrução do tipo I
        string string_instruction = to_string(instruction);
        string opcode = "";
        char first_check = 'x'; // → indica que tem endereço na instrução
        string instruction_type = "";

        for(int i = 2; i < 8; i++){
            opcode[i] = string_instruction[i];
        }

    if (string_instruction.find(first_check) != std::string::npos) {
        if (opcode == this->instructionMap.at("la")) {              // LOAD from vector
            instruction_type = "LA";
        } else if (opcode == this->instructionMap.at("lw")) {       // LOAD
            instruction_type = "LW";
        } else if (opcode == this->instructionMap.at("st")) {       // STORE
            instruction_type = "ST";
        } else if (opcode == this->instructionMap.at("beq")) {      // EQUAL
            instruction_type = "BEQ";
        } else if (opcode == this->instructionMap.at("blt")) {      // LESS THAN
            instruction_type = "BLT";
        } else if (opcode == this->instructionMap.at("blti")) {     // LESS THAN OR EQUAL
            instruction_type = "BLTI";
        } else if (opcode == this->instructionMap.at("bgt")) {      // GREATER THAN
            instruction_type = "BGT";
        } else if (opcode == this->instructionMap.at("bgti")) {     // GREATER THAN OR EQUAL
            instruction_type = "BGTI";
        }
        else if (opcode == this->instructionMap.at("print")) {    
            instruction_type = "PRINT";
        }
        else if (opcode == this->instructionMap.at("li")) {    
            instruction_type = "LI"; // LOAD IMMEDIATE
        }
    }else{

        //identificação das instruções do tipo R

        // O começo não devieria ser 0 tmb?
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

        case 0b00000000000000000000000000011010:
            //instrução de DIV, neste caso teremos registradores especificos a serem usados
            instruction_type = "DIV";
            break;

        default:
            break;
        }
    }


} 

string Control_Unit::Pick_Adress_Result(const uint32_t instruction)
{
    string copia_instrucao = to_string(instruction);
    string code;
    for(int i = 11; i < 17; i++){
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

void Control_Unit::Execute_Aritmetic_Operation(REGISTER_BANK &registers,Temporary_Data &data){

        ALU alu;
        if(data.tarefa_a_ser_feita_pela_ula == "ADD"){
            alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
            alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
            alu.result = registers.acessoEscritaRegistradores[data.code_third_register]();
            alu.op = ADD;
            alu.calculate();
        }else if(data.tarefa_a_ser_feita_pela_ula == "SUB"){
            alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
            alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
            alu.result = registers.acessoEscritaRegistradores[data.code_third_register]();
            alu.op = SUB;
            alu.calculate();
        }else if(data.tarefa_a_ser_feita_pela_ula == "MUL"){
            alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
            alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
            alu.result = registers.acessoEscritaRegistradores[data.code_third_register]();
            alu.op = MUL;
            alu.calculate();
        }else if(data.tarefa_a_ser_feita_pela_ula == "DIV"){
            alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
            alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
            alu.result = registers.acessoEscritaRegistradores[data.code_third_register]();
            alu.op = DIV;
            alu.calculate();
        }

        return;
}

void Control_Unit::Execute_Loop_Operation(REGISTER_BANK &registers,Temporary_Data &data, int &counter){
    
    ALU alu;
    if(data.tarefa_a_ser_feita_pela_ula == "BLT"){
        alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
        alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
        alu.op = BLT;
        alu.calculate();
        if(alu.result == 1){
            registers.pc.write(static_cast<uint32_t>(stoul(data.addressRAMResult)));
            counter = 0;
        }
    }else if(data.tarefa_a_ser_feita_pela_ula == "BLTI"){
        alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
        alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
        alu.op = BLTI;
        alu.calculate();
        if(alu.result == 1){
            registers.pc.write(static_cast<uint32_t>(stoul(data.addressRAMResult)));
            counter = 0;
        }
    }else if(data.tarefa_a_ser_feita_pela_ula == "BGT"){
        alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
        alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
        alu.op = BGT;
        alu.calculate();
        if(alu.result == 1){
            registers.pc.write(static_cast<uint32_t>(stoul(data.addressRAMResult)));
            counter = 0;
        }
    }else if(data.tarefa_a_ser_feita_pela_ula == "BGTI"){
        alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
        alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
        alu.op = BGTI;
        alu.calculate();
        if(alu.result == 1){
            registers.pc.write(static_cast<uint32_t>(stoul(data.addressRAMResult)));
            counter = 0;
        }
    }
}

void Control_Unit::Execute_Operation(REGISTER_BANK &registers,Temporary_Data &data){

}
