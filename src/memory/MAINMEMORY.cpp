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


void MainMemory::WriteMem(const uint32_t address, const uint32_t data) {
    if (address >= NumOfi * NumOfj) {
        printf("Endereço inválido!\n");
        return;
    }
    int iTarget = address / NumOfj; 
    int jTarget = address % NumOfj; 
    words[iTarget][jTarget].write(data);
}

const uint32_t MainMemory::ReadMem(const uint32_t address) {
    if (address >= NumOfi * NumOfj) {
        printf("Endereço inválido!\n");
        return -1; 
    }
    int iTarget = address / NumOfj; 
    int jTarget = address % NumOfj; 
    
    return words[iTarget][jTarget].read();
}
