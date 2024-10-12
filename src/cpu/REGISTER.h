//
// Created by czarhrs on 10/10/24.
//

#ifndef REGISTER_H
#define REGISTER_H

#include <cinttypes>

struct REGISTER {
    uint32_t value;

    REGISTER() : value(0x0000) {}

    void write(uint32_t new_value);

    // [[nodiscard]]: proibe a pesoa de discartar o valor de retorno da função
    [[nodiscard]] uint32_t read() const;
    [[nodiscard]] uint32_t reverse_read() const;
};


#endif //REGISTER_H
