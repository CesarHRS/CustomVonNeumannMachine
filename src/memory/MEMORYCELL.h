#ifndef MEMORYCELL_HPP
#define MEMORYCELL_HPP

#include <iostream>
#include <string>
#include "../cpu/REGISTER.h"

struct MemoryCell
{
    uint32_t value;
    MemoryCell *next;
    MemoryCell() : value(0x0000) {}

    void write(const uint32_t new_value);

    [[nodiscard]] uint32_t read() const;
    [[nodiscard]] uint32_t reverse_read() const;

};
#endif
