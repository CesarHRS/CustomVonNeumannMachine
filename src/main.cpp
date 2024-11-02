#include<iostream>
#include<fstream>
//#include"./cpu/REGISTER_BANK.h"
//#include"./cpu/CONTROL_UNIT.h"
//#include"./cpu/HashRegister.h"
#include"./memory/MAINMEMORY.h"

using namespace std;

int main(){




		//~~===~~===~~===~~===~~~===~~~=== TESTE DE MEMÓRIA ~~===~~===~~===~~===~~===~~===~~===~~===~~~===~~===
    MainMemory a = MainMemory(2048,2048);				//  1º  Cria-se uma variável do tipo MainMemory com 2048 linhas e 2048 colunas.
    a.WriteMem(333, 200);						//  2º  Escrevesse no endereço 333 o valor 200.
    uint32_t DataRead = a.ReadMem(333);					//  3º  A leitura do endereço 333 retorna o valor armazenado no mesmo para a variável DataRead
    printf("Data: %d", DataRead );					//  4º Tudo é mostrado na tela pelo printf.
		//~~===~~===~~===~~===~~===~~===~~===~~===~~===~~===~~===~~===~~===~~===~~===~~===~~~===~~===~~===~~===






    //variaveis


        // int counter = 0;
        // ifstream file("programa.txt"); //tem de ler o programa inteiro e jogar na RAM
        // string line;
        // REGISTER_BANK registers;
        // Control_Unit UC;
        // bool endProgram = false;
        // int counterForEnd = 5;
        // int clock = 0;

    /*tem de haver uma chamada da memória antes de chamar a unidade de controle para começar a operar no programa escrito
    Ou seja, vou ler o programa da memória do emulador e não do arquivo do meu computador
    */

    //é apenas uma ideia, não significa que vai ser aqui que isso deve ocorrer:

    //     while(counterForEnd > 0){
    //         if(counter >= 0 && counterForEnd == 5){
    //             //chamar a instrução de fetch da unidade de controle
    //             UC.Fetch(registers, endProgram);
    //         }
    //         if(counter >= 1 && counterForEnd >= 4){
    //             //chamar a instrução de decode da unidade de controle
    //             UC.Decode(registers, UC.data[counter]);
    //         }
    //         if(counter >= 2 && counterForEnd >= 3){
    //             //chamar a instrução de execução da unidade de controle
    //             UC.Execute(registers,UC.data[counter - 1], counter);
    //         }
    //         if(counter >= 3 && counterForEnd >= 2){
    //             //chamar a instrução de memory_acess da unidade de controle
    //             UC.Memory_Acess(registers, UC.data[counter - 2]);
    //         }
    //         if(counter >= 4 && counterForEnd >= 1){
    //             //chamar a instrução de write back
    //             UC.Write_Back(UC.data[counter - 3]);
    //         }
    //         counter =+ 1;
    //         clock =+ 1;
    //         if(endProgram == true){
    //             counterForEnd =- 1;
    //         }
    //     }
        
       
    // return 0;
}
