#include "CONTROL_UNIT.h"

//PIPELINE

void Control_Unit::Fetch(REGISTER_BANK &registers){
    //Aqui são as ações para colocar a próxima instrução de prontidão
    registers.mar.write(registers.pc.value);
    //chamar a memória com a posição do pc e inserir em um registrador
    //registers.ir.write(aqui tem de ser passado a instrução que estiver na RAM);
    registers.pc.write(registers.pc.value += 1);//incrementando o pc  
}

void Control_Unit::Decode(REGISTER_BANK &registers){
    //Daqui vai ter de ser identificado o que fazer

    const uint32_t instruction = registers.ir.read();
    // tenho de converte o valor de 32 bits para binario e separar cada uma das partes para fazer a análise


    Identificacao_instrucao(instruction,registers);

}

void Control_Unit::Execute(){
    /*Daqui tem de ser chamado o que tiver de ser chamado, 
    aqui tem de ser consultado a instrução que será feita,
    para saber se por exemplo vai ser feita uma multiplicação ou divisão*/
}

void Control_Unit::Memory_Acess(){

}

void Control_Unit::Write_Back(){

}

void Control_Unit::Identificacao_instrucao(const uint32_t instruction, REGISTER_BANK &registers){


    //instrução do tipo j
        string string_instruction = to_string(instruction);
        char first_check = 'x'; // → indica que tem endereço na instrução
        char second_check = 'v'; // → indica que tem endereço na instrução
        
        if(string_instruction.find(first_check) != string::npos){
            //instrução do tipo j
            if(string_instruction.find(second_check) != string::npos){
                // LOAD de vetor
            }
            else if(string_instruction.find("100011") != string::npos){
                // LOAD
            }else{
                // STORE
            }
        }

    //identificação das instruções do tipo R

    unsigned long long int opcode = instruction & 0b11111100000000000000000000111111;

    switch (opcode)
    {
    case 0b00000000000000000000000000100000:
        //instrução de ADD
        break;

    case 0b00000000000000000000000000100010:
        //instrução de SUB
        break;

    case 0b00000000000000000000000000011000:
        //instrução de MUL
        break;


    case 0b00000000000000000000000000100101:
        //instrução de AND
        break;

    case 0b00000000000000000000000000100100:
        //instrução de OR
        break;

    case 0b00000000000000000000000000100110:
        //instrução de XOR
        break;

    case 0b00000000000000000000000000011010:
        //instrução de DIV, neste caso teremos registradores especificos a serem usados
        break;

    default:

        // instruções do tipo J → a única no nosso caso é a instrução de JUMP    
               
        break;
    }


} 

void Load(REGISTER_BANK &registers){

}