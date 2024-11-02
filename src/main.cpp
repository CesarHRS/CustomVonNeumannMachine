#include"./cpu/REGISTER_BANK.h"
#include"./cpu/CONTROL_UNIT.h"
#include"./cpu/HashRegister.h"
#include"./memory/MAINMEMORY.h"
#include"./loader.h"

using namespace std;

int main(int argc, char* argv[]){

  if (argc != 2) {
      std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
      return 1;
  }

  MainMemory ram = MainMemory(2048,2048);				//  1º  Cria-se uma variável do tipo MainMemory com 2048 linhas e 2048 colunas.
  REGISTER_BANK registers;
  Control_Unit UC;
  int counterForEnd = 5;
  int counter = 0;
  bool endProgram = false;
  int clock = 0;

  loadProgram(argv[1],ram);


    /*tem de haver uma chamada da memória antes de chamar a unidade de controle para começar a operar no programa escrito
    Ou seja, vou ler o programa da memória do emulador e não do arquivo do meu computador
    */

        while(counterForEnd > 0){
            if(counter >= 0 && counterForEnd == 5){
                //chamar a instrução de fetch da unidade de controle
                UC.Fetch(registers, endProgram,ram);

            }
            if(counter >= 1 && counterForEnd >= 4){
                //chamar a instrução de decode da unidade de controle
                UC.Decode(registers, UC.data[counter]);
            }
            if(counter >= 2 && counterForEnd >= 3){
                //chamar a instrução de execução da unidade de controle
                UC.Execute(registers,UC.data[counter - 1], counter);
            }
            if(counter >= 3 && counterForEnd >= 2){
                //chamar a instrução de memory_acess da unidade de controle
                UC.Memory_Acess(registers, UC.data[counter - 2],ram);
            }
            if(counter >= 4 && counterForEnd >= 1){
                //chamar a instrução de write back
                UC.Write_Back(UC.data[counter - 3],ram,registers);
            }
            counter =+ 1;
            clock =+ 1;
            if(endProgram == true){
                counterForEnd =- 1;
            }
        }
        
       
    return 0;
}
