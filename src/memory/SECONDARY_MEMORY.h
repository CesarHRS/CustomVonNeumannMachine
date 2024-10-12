#ifndef SECONDARY_MEMORY_H
#define SECONDARY_MEMORY_H

#include <cinttypes>
#include <iostream>
#include <vector>

using namespace std;

struct SECONDARY_MEMORY {
    vector<uint32_t> storage;
    
    SECONDARY_MEMORY(size_t size) : storage(size, 0x0000) {}
    
    void write(size_t position, uint32_t value);
    uint32_t read(size_t position) const;
};

#endif
