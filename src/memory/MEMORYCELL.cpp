#include "MEMORYCELL.h"

void MemoryCell::write(const uint32_t new_value) {
    this->value = new_value;
}

uint32_t MemoryCell::read() const{
    return value;
}

uint32_t MemoryCell::reverse_read() const{
    return ~value;
}
