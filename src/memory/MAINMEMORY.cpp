#include "MAINMEMORY.h"


bool MainMemory::EmptyLine(int i) const
{
//      if(words[i] == NULL) return 1;
        for (int j = 0 ;j < NumOfj; j++)
        {
                if(words[i][j].read() != 0)
                        return false;
        }
        return true;

        //      else return 0;
}

void MainMemory::InsertData(const uint32_t data, int iTarget, int jTarget)
{
        bool hA = iTarget<NumOfi && jTarget<NumOfj;
        bool hB = iTarget>=0 && jTarget>=0;


        if (hA && hB)  words[iTarget][jTarget].write(data);

        else printf("Os valores de inserção de i e j são muito grandes!!");

}

void MainMemory::EraseData(int iTarget, int jTarget)
{
        bool hA = iTarget<NumOfi && jTarget<NumOfj;
        bool hB = iTarget>=0 && jTarget>=0;

        if (hA && hB) words[iTarget][jTarget].write(0);

        else printf("Os valores para deleção de i e j são muito grandes!!");
}

uint32_t MainMemory::GetData(int iTarget, int jTarget) const {
    if (iTarget < NumOfi && jTarget < NumOfj && iTarget >= 0 && jTarget >= 0) {
        return words[iTarget][jTarget].read();
    } else {
        printf("Valores de i e j fora dos limites!\n");
        return 0; // Valor padrão ou código de erro
    }
}
