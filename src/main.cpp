#include"./cpu/REGISTER_BANK.h"
#include"./cpu/CONTROL_UNIT.h"
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
    int clock = 0;
    bool endProgram = false;
    Instruction_Data data;

  loadProgram(argv[1],ram);


            while(counterForEnd > 0){
                if(counter >= 4 && counterForEnd >= 1){
                    //chamar a instrução de write back
                    UC.Write_Back(UC.data[counter - 4],ram,registers);
                }
                if(counter >= 3 && counterForEnd >= 2){
                    //chamar a instrução de memory_acess da unidade de controle
                    UC.Memory_Acess(registers, UC.data[counter - 3],ram);
                }
                if(counter >= 2 && counterForEnd >= 3){
                    //chamar a instrução de execução da unidade de controle
                    UC.Execute(registers,UC.data[counter - 2], counter);
                }
                if(counter >= 1 && counterForEnd >= 4){
                    //chamar a instrução de decode da unidade de controle
                    UC.Decode(registers, UC.data[counter-1]);
                }
                if(counter >= 0 && counterForEnd == 5){
                    //chamar a instrução de fetch da unidade de controle
                    UC.data.push_back(data) ;
                    UC.Fetch(registers, endProgram,ram);
                }
                counter += 1;
                clock += 1;
                if(endProgram == true){
                    counterForEnd =- 1;
                }
            }
        
      
       
    return 0;
}
