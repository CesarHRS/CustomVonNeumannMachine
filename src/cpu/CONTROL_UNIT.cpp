#include "CONTROL_UNIT.h"
#include <bitset>

// TODO
// - Implement print, li, la, lw, sw, j

uint32_t ConvertToDecimalValue(uint32_t value){
    string bin_str = to_string(value);
        uint32_t decimal_value = 0;       
        int len = bin_str.length();
        for (int i = 0; i < len; ++i) {
        if (bin_str[i] == '1') {
            decimal_value += std::pow(2, len - 1 - i);
            }
        }
    return decimal_value;
}

//PIPELINE

void Control_Unit::Fetch(REGISTER_BANK &registers, bool &endProgram, MainMemory &ram){
    const uint32_t instruction = registers.ir.read();
    registers.ir.write(ram.ReadMem(registers.mar.read()));
    if(instruction == 0b11111100000000000000000000000000)
    {
        //cout << "END FOUND" << endl;
        endProgram = true;
        return;
    }
    registers.mar.write(registers.pc.value);
    //chamar a memória com a posição do pc e inserir em um registrador
    //registers.ir.write(aqui tem de ser passado a instrução que estiver na RAM);

    registers.ir.write(ram.ReadMem(registers.mar.read()));
    //cout << "IR: " << bitset<32>(registers.ir.read()) << endl;
    registers.pc.write(registers.pc.value += 1);//incrementando o pc 
}

void Control_Unit::Decode(REGISTER_BANK &registers, Instruction_Data &data){

    const uint32_t instruction = registers.ir.read();
    data.op = Identificacao_instrucao(instruction,registers);
    //cout << data.op << endl;

    //cout <<instruction << endl;

    if(data.op == "ADD" || data.op == "SUB" || data.op == "MULT" || data.op == "DIV"){
        // se entrar aqui é porque tem de carregar registradores, que estão especificados na instrução
        data.source_register = Get_source_Register(instruction);
        data.target_register = Get_target_Register(instruction);
        data.destination_register = Get_destination_Register(instruction);

    }else if(data.op == "LI" || data.op == "LW" || data.op == "LA" || data.op == "SW")
    {
        data.target_register = Get_target_Register(instruction);
        data.addressRAMResult = Get_immediate(instruction);
        //cout << "source register: " <<data.source_register << endl;
        //cout << "segundo registrador:" << data.addressRAMResult << endl;

    }else if(data.op == "BLT" || data.op == "BGT" || data.op == "BGTI" || data.op == "BLTI"){
        data.source_register = Get_source_Register(instruction);
        data.target_register = Get_target_Register(instruction);
        data.addressRAMResult = Get_immediate(instruction);   
    }
    else if(data.op == "J"){
        data.addressRAMResult = Get_immediate(instruction);
    }
    else if(data.op == "PRINT"){
        string instrucao = to_string(instruction);
        if(Get_immediate(instruction) == "0000000000000000"){  //se for zero, então é um registrador
            data.target_register = Get_target_Register(instruction);
        }else{  //se não for zero, então é um valor imediato
            data.addressRAMResult = Get_immediate(instruction); 
        }
    }

    return;
}

void Control_Unit::Execute(REGISTER_BANK &registers,Instruction_Data &data, int &counter, int& counterForEnd,bool& programEnd, MainMemory& ram){
    /*Daqui tem de ser chamado o que tiver de ser chamado*/

    if(data.op == "ADD" ||  data.op == "SUB" || data.op == "MUL" || data.op == "DIV"){
        Execute_Aritmetic_Operation(registers, data);
    }else if(data.op == "BEQ" || data.op == "J" || data.op == "BNE" || data.op == "BGT" || data.op == "BGTI" || data.op == "BLT" || data.op == "BLTI"){
        Execute_Loop_Operation(registers, data, counter,counterForEnd,programEnd,ram);
    }
    else if( data.op == "PRINT" ){
        Execute_Operation(registers,data);
    }

    //cout<<"entrou"<<endl;
    //cout << counter << endl;

    // demais operações realizadas no memory acess
}

void Control_Unit::Memory_Acess(REGISTER_BANK &registers,Instruction_Data &data, MainMemory &memory){

    
    string nameregister = this->map.mp[data.target_register];

    //aqui devem ser executadas as intruções de LOAD de fato
    if(data.op == "LW"){
        int decimal_addr = ConvertToDecimalValue(stoul(data.addressRAMResult));
        //aqui tem de ser feito a leitura na RAM
        registers.acessoEscritaRegistradores[nameregister](memory.ReadMem(decimal_addr));
        //cout << "valor da memória RAM: " << registers.acessoLeituraRegistradores[nameregister]() << endl;
    }if(data.op == "LA" || data.op == "LI"){
        int decimal_value = ConvertToDecimalValue(stoul(data.addressRAMResult));
        registers.acessoEscritaRegistradores[nameregister](decimal_value);
    }
    else if(data.op == "PRINT" && data.target_register == ""){
        int decimal_addr = ConvertToDecimalValue(stoul(data.addressRAMResult));
        int value = memory.ReadMem(decimal_addr);
        cout << "PROGRAM PRINT: " << value << endl;
    }

    return;
}

void Control_Unit::Write_Back(Instruction_Data &data, MainMemory &memory,REGISTER_BANK &registers){

    string nameregister = this->map.mp[data.target_register];

    //aqui devem ocorrer qualquer uma das intruções de escrita na RAM
    if(data.op == "SW"){
        //aqui tem de ser feito a escrita na RAM
        int decimal_value = ConvertToDecimalValue(stoul(data.addressRAMResult));
        //cout << decimal_value << endl;
        memory.WriteMem(decimal_value, registers.acessoLeituraRegistradores[nameregister]()) ;
        //cout << "valor da memória RAM: " << memory.ReadMem(decimal_value) << endl;
    }

    return;

}

string Control_Unit::Identificacao_instrucao(uint32_t instruction, REGISTER_BANK &registers){

    string instrucao = bitset<32>(instruction).to_string();
    string string_instruction = instrucao;
    string opcode = "";
    string instruction_type = "";

    for(int i = 0; i < 6; i++){
        opcode += string_instruction[i];
    }
    //cout << string_instruction << endl;
    //instrução do tipo I
    if (opcode == this->instructionMap.at("la")) {              // LOAD from vector
        instruction_type = "LA";
    } else if (opcode == this->instructionMap.at("lw")) {       // LOAD
        instruction_type = "LW";
    } else if (opcode == this->instructionMap.at("j")) {       // JUMP
        instruction_type = "J";
    } else if (opcode == this->instructionMap.at("sw")) {       // STORE
        instruction_type = "SW";
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

    // instruções do tipo R

    if (opcode == this->instructionMap.at("add")) {              
        instruction_type = "ADD";
            //cout << this->instructionMap.at("add")<< "opcode soma:" << opcode << endl;

    } else if (opcode == this->instructionMap.at("sub")) {       
        instruction_type = "SUB";
    } else if (opcode == this->instructionMap.at("mult")) {       
        instruction_type = "MULT";
    } else if (opcode == this->instructionMap.at("div")) {      
        instruction_type = "DIV";
    }

    return instruction_type;
} 

string Control_Unit::Get_immediate(const uint32_t instruction)
{
    string instrucao = bitset<32>(instruction).to_string();
    string copia_instrucao = instrucao;
    string code;
    for(int i = 16; i < 32; i++){
        code += copia_instrucao[i];
    }

    return code;
}

string Control_Unit::Get_destination_Register(const uint32_t instruction){
    string instrucao = bitset<32>(instruction).to_string();
    string copia_instrucao = instrucao;
    string code;
    for(int i = 16; i < 21; i++){
        code += copia_instrucao[i];
    }

    return code;
}

string Control_Unit::Get_target_Register(const uint32_t instruction){
    string instrucao = bitset<32>(instruction).to_string();
    string copia_instrucao = instrucao;
    string code;
    for(int i = 11; i < 16; i++){
        code += copia_instrucao[i];
    }

    return code;
}

string Control_Unit::Get_source_Register(const uint32_t instruction){
    string instrucao = bitset<32>(instruction).to_string();
    string copia_instrucao = instrucao;
    string code;
    for(int i = 6; i < 11; i++){
        code += copia_instrucao[i];
    }

    return code;
}

void Control_Unit::Execute_Aritmetic_Operation(REGISTER_BANK &registers,Instruction_Data &data){

        string nameregistersource = this->map.mp[data.source_register];
        string nametargetregister = this->map.mp[data.target_register];
        string nameregisterdestination = this->map.mp[data.destination_register]; 
        ALU alu;
        if(data.op == "ADD"){
            alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
            alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
            alu.op = ADD;
            alu.calculate();
            //cout << "valor de A:" << alu.A << endl;
            //cout << "valor de B:" << alu.B << endl;
            registers.acessoEscritaRegistradores[nameregisterdestination](alu.result);
            //cout<< "resultado soma:" <<registers.acessoLeituraRegistradores[nameregisterdestination]() << endl;
        }else if(data.op == "SUB"){
            alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
            alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
            alu.op = SUB;
            //cout << "valor de A:" << alu.A << endl;
            //cout << "valor de B:" << alu.B << endl;
            alu.calculate();
            registers.acessoEscritaRegistradores[nameregisterdestination](alu.result);
            //cout << "resultado subtração:" << registers.acessoLeituraRegistradores[nameregisterdestination]() << endl;
        }else if(data.op == "MUL"){
            alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
            alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
            alu.op = MUL;
            alu.calculate();
            registers.acessoEscritaRegistradores[nameregisterdestination](alu.result);
            //cout << "resultado multiplicação:" << registers.acessoLeituraRegistradores[nameregisterdestination]() << endl;
        }else if(data.op == "DIV"){
            alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
            alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
            alu.op = DIV;
            alu.calculate();
            registers.acessoEscritaRegistradores[nameregisterdestination](alu.result);
        }

        return;
}

void Control_Unit::Execute_Loop_Operation(REGISTER_BANK &registers,Instruction_Data &data, int &counter, int& counterForEnd, bool& programEnd, MainMemory& ram){
    
    string nameregistersource = this->map.mp[data.source_register];
    string nametargetregister = this->map.mp[data.target_register];
    string nameregisterdestination = this->map.mp[data.destination_register];
    ALU alu;
    if(data.op == "BEQ"){
        alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
        alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
        alu.op = BEQ;
        alu.calculate();
        if(alu.result == 1){
            int decimal_value = ConvertToDecimalValue(stoul(data.addressRAMResult));
            registers.pc.write(decimal_value);
            registers.ir.write(ram.ReadMem(registers.pc.read()));
            counter = 0;
            counterForEnd = 5;
            programEnd = false;
        }
    }else if(data.op == "BNE"){
        alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
        alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
        alu.op = BNE;
        alu.calculate();
        if(alu.result == 1){
            int decimal_value = ConvertToDecimalValue(stoul(data.addressRAMResult));
            registers.pc.write(decimal_value);
            registers.ir.write(ram.ReadMem(registers.pc.read()));
            counter = 0;
            counterForEnd = 5;
            programEnd = false;
        }
    }else if(data.op == "J"){
        int decimal_value = ConvertToDecimalValue(stoul(data.addressRAMResult));
        registers.pc.write(decimal_value);
        registers.ir.write(ram.ReadMem(registers.pc.read()));

        //cout << "Jump to: " << registers.pc.read();
        counter = 0;
        counterForEnd = 5;
        programEnd = false;
    }else if(data.op == "BLT"){
        alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
        alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
        alu.op = BLT;
        alu.calculate();
        if(alu.result == 1){
            int decimal_value = ConvertToDecimalValue(stoul(data.addressRAMResult));
            registers.pc.write(decimal_value);
            registers.ir.write(ram.ReadMem(registers.pc.read()));
            counter = 0;
            counterForEnd = 5;
            programEnd = false;
        }
    }else if(data.op == "BLTI"){
        alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
        alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
        alu.op = BLTI;
        alu.calculate();
        if(alu.result == 1){
            int decimal_value = ConvertToDecimalValue(stoul(data.addressRAMResult));
            registers.pc.write(decimal_value);
            registers.ir.write(ram.ReadMem(registers.pc.read()));
            counter = 0;
            counterForEnd = 5;
            programEnd = false;
        }
    }else if(data.op == "BGT"){
        alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
        alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
        alu.op = BGT;
        alu.calculate();
        if(alu.result == 1){
            int decimal_value = ConvertToDecimalValue(stoul(data.addressRAMResult));
            registers.pc.write(decimal_value);
            registers.ir.write(ram.ReadMem(registers.pc.read()));
            counter = 0;
            counterForEnd = 5;
            programEnd = false;
        }
    }else if(data.op == "BGTI"){
        alu.A = registers.acessoLeituraRegistradores[nameregistersource]();
        alu.B = registers.acessoLeituraRegistradores[nametargetregister]();
        alu.op = BGTI;
        alu.calculate();
        if(alu.result == 1){
            int decimal_value = ConvertToDecimalValue(stoul(data.addressRAMResult));
            registers.pc.write(decimal_value);
            registers.ir.write(ram.ReadMem(registers.pc.read()));

            counter = 0;
            counterForEnd = 5;
            programEnd = false;
        }
    }
    return;
}

void Control_Unit::Execute_Operation(REGISTER_BANK &registers,Instruction_Data &data){
    string nameregister = this->map.mp[data.target_register];

    if(data.op == "PRINT" && data.target_register != ""){
        cout << "PROGRAM PRINT: " << registers.acessoLeituraRegistradores[nameregister]() << endl;
    }
}

string Control_Unit::Pick_Code_Register_Load(const uint32_t instruction){
    string instrucao = bitset<32>(instruction).to_string();
    string copia_instrucao = instrucao;
    string code;
    for(int i = 11; i < 16; i++){
        code += copia_instrucao[i];
    }

    return code;
}


