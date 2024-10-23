#include<iostream>
#include<fstream>
#include"./cpu/REGISTER_BANK.h"
#include"./cpu/CONTROL_UNIT.h"
#include"./cpu/HashRegister.h"


using namespace std;

int main(){

    
    //variaveis
        bool key = true;
        int counter = 0;
        ifstream file("programa.txt"); //tem de ler o programa inteiro e jogar na RAM
        string line;
        REGISTER_BANK registers;
        Control_Unit UC;

    /*tem de haver uma chamada da memória antes de chamar a unidade de controle para começar a operar no programa escrito
    Ou seja, vou ler o programa da memória do emulador e não do arquivo do meu computador
    */

    //é apenas uma ideia, não significa que vai ser aqui que isso deve ocorrer:
        while(key == true){
            if(counter >= 0){
                //chamar a instrução de fetch da unidade de controle
                UC.Fetch(registers);
            }
            if(counter >= 1){
                //chamar a instrução de decode da unidade de controle
                UC.Decode(registers, UC.data[counter]);
            }
            if(counter >= 2){
                //chamar a instrução de execução da unidade de controle
                UC.Execute(registers,UC.data[counter - 1]);
            }
            if(counter >= 3){
                //chamar a instrução de memory_acess da unidade de controle
                UC.Memory_Acess();
            }
            if(counter >= 4){
                //chamar a instrução de write back
                UC.Write_Back();
            }
            counter =+ 1;
        }
    
    return 0;
}