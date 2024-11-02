#ifndef MAINMEMORY_H
#define MAINMEMORY_H

#include "MEMORYCELL.h"
#include "stdbool.h"

using namespace std;

struct MainMemory{
	int NumOfj;
	int NumOfi;
	MemoryCell **words;

	MainMemory() : NumOfj(2048), NumOfi(2048), words(NULL) {}

	MainMemory(int NumOfj, int NumOfi) {

		this->NumOfi = NumOfi;
		this->NumOfj = NumOfj;
		words =  (MemoryCell**)malloc( sizeof(MemoryCell*) * this->NumOfi);

		for(uint32_t k = 0; k<NumOfi ; k++)
		{
			words[k] = (MemoryCell*)malloc(sizeof(MemoryCell) * this->NumOfj);
		
			
		}

		for(uint32_t i = 0 ; i < NumOfi ; i++ )
			for(uint32_t j = 0 ; j< NumOfj ; j++)
				words[i][j].write(0);
		
	}

        void InsertData(const uint32_t data, int iTarget, int jTarget);
	void EraseData(int iTarget, int jTarget);
	bool EmptyLine(int i) const;
	void WriteMem(const uint32_t address, const uint32_t data);
	const uint32_t ReadMem(const uint32_t address);

//	void ShowBit(int NumOfj, int NumOfi);
//	void WriteBit(REGISTER value, int iTarget, int jTarget);

};
#endif
