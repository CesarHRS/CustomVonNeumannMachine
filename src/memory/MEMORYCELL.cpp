
#include "MEMORYCELL.h"

void MemoryCell::write(const uint32_t new_value) {
    this->value.write(new_value);
}

REGISTER MemoryCell::read() const{
    return value;
}

REGISTER MemoryCell::reverse_read() const{
    return value;
}
