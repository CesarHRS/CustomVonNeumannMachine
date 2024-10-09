# Construir um CPU com a arquitetura de Von Neumann

CPU + Memória principal + cache + memoria secundaria + periféricos

* Pipeline de 4 estágios
* Os periféricos podem ser valores booleanos
* Primeiro buscar na cache e depois na RAM


# CPU

## Especificação
* A CPU terá multiplos núcleos, onde cada core possui seu proprio conjunto de registradores
* O ISA, Cache e Pipline é compartilhado entre os cores

## Planejamento
* O processador será um vetor de n posições, onde n é a quantidade de cores
* Os registradores serão definidos dentro de uma estrutura de dados chamada banco de registradores, da seguinte forma:


# CPU
## Unidade Lógica Aritmética
* A ULA será um switch grande, da mesma forma que é representada em HDLs, e suas operações serão definidas em um ENUM
```
enum operation {
    ADD,     
    SUB,      
    AND,      
    OR,       
    XOR,      
    NOT,      // NOT A
    SLT,      //(A < B)
    A,
    B,
};
```

```
uint64_t ULA(uint64_t A, uint64_t B, operation op) {
    uint64_t result = 0;

    switch(op) {
        case ADD:
            result = A + B;
            break;
        case SUB:
            result = A - B;
            break;
        case AND:
            result = A & B;
            break;
        case OR:
            result = A | B;
            break;
        case XOR:
            result = A ^ B;
            break;
        case NOT:
            result = ~A; 
            break;
        case SLT:
            result = (A < B) ? 1 : 0;
            break;
        case A:
            result = A;
            break;
        case B:
            result = B;
            break;            
        default:
            cerr << "ULA:INVALID OPERATION!" << endl;
    }
    return result;
}
```


## Banco de Registradores
* A estrutura geral do banco, será da seguinte forma:
```
struct register_bank {
    //registradores de uso especifico
    register pc;
    register mar;
    //registradores de uso geral
    register zero;  
    register at;    
    register v0, v1;  
    register a0, a1, a2, a3;  
    register t0, t1, t2, t3, t4, t5, t6, t7;  
    register s0, s1, s2, s3, s4, s5, s6, s7;  
    register t8, t9;  
    register k0, k1;  
    register gp, sp, fp, ra;  

    void print_registers() const {
        ::cout << hex << setfill('0');
        cout << "$zero: " << setw(8) << zero.read() << endl;
        cout << "$at:   " << setw(8) << at.read() << endl;
        cout << "$v0:   " << setw(8) << v0.read() << endl;
        cout << "$v1:   " << setw(8) << v1.read() << endl;
        cout << "$a0:   " << setw(8) << a0.read() << endl;
        cout << "$a1:   " << setw(8) << a1.read() << endl;
        cout << "$a2:   " << setw(8) << a2.read() << endl;
        cout << "$a3:   " << setw(8) << a3.read() << endl;
        cout << "$t0:   " << setw(8) << t0.read() << endl;
        cout << "$t1:   " << setw(8) << t1.read() << endl;
        cout << "$t2:   " << setw(8) << t2.read() << endl;
        cout << "$t3:   " << setw(8) << t3.read() << endl;
        cout << "$t4:   " << setw(8) << t4.read() << endl;
        cout << "$t5:   " << setw(8) << t5.read() << endl;
        cout << "$t6:   " << setw(8) << t6.read() << endl;
        cout << "$t7:   " << setw(8) << t7.read() << endl;
        cout << "$s0:   " << setw(8) << s0.read() << endl;
        cout << "$s1:   " << setw(8) << s1.read() << endl;
        cout << "$s2:   " << setw(8) << s2.read() << endl;
        cout << "$s3:   " << setw(8) << s3.read() << endl;
        cout << "$s4:   " << setw(8) << s4.read() << endl;
        cout << "$s5:   " << setw(8) << s5.read() << endl;
        cout << "$s6:   " << setw(8) << s6.read() << endl;
        cout << "$s7:   " << setw(8) << s7.read() << endl;
        cout << "$t8:   " << setw(8) << t8.read() << endl;
        cout << "$t9:   " << setw(8) << t9.read() << endl;
        cout << "$k0:   " << setw(8) << k0.read() << endl;
        cout << "$k1:   " << setw(8) << k1.read() << endl;
        cout << "$gp:   " << setw(8) << gp.read() << endl;
        cout << "$sp:   " << setw(8) << sp.read() << endl;
        cout << "$fp:   " << setw(8) << fp.read() << endl;
        cout << "$ra:   " << setw(8) << ra.read() << endl;
    }
};
```
* A estrutura interna de cada registrador, será da seguinte forma, onde é possível escrever um valor no registrador, ler
o valor armazenado, e ler o inverso do falor armazenado, como em um flip flop do tipo D, que temos a saída convencional
e a saída barrada:
```
struct register {
    uint32_t value;

    mips_register() : value(0x0000) {}

    void write(uint32_t new_value) {
        value = new_value;
    }

    uint32_t read() const {
        return value;
    }

    uint32_t read~() const {
        return ~value;
    }
    
};

```
## Unidade de Controle

* Incrementar o program counter após cada instrução
```
void increment_pc(uint64_t &pc) {
    pc += 1;  
}
```
* Definição da instrução
```
struct instruction {
    operation op;
    uint64_t operand1;
    uint64_t operand2;
    uint64_t result;
    uint8_t destination_register;
    bool memory_access;   
    bool write_back;     
};
```


## Memória Cache
* A memória cache será uma tabela hash, que não contém a cópia de um conteúdo da memória RAM, ou seja, é ela é 
independente. A cache também deve ser compartilhada entre todos Cores da CPU, da mesma forma que funciona a cache L3 nos 
processadores modernos
* Vale a pena lembrar que para um valor da memória cache ser utilizado, ele deve ser movido da cache para algum
registrador de uso geral, para que a ULA opere sobre ele depois, ele deve ser armazena em um registrador e depois de
volta a cache... 
* Deve ser capaz de armazenar 4 bytes em hexa em cada posição, exemplo: 0x0000

## Memória Principal
* De mesmo modo que a cache, visando ser parecida com a RAM, seu conteúdo será salvo numa tabela hash, ela se comunicará
com o CPU e com a memória secundária, cada espaço dela, deve ser capaz de armazenar 4 bytes em hexa como a cache
* Aqui, é necessário que a comunicação entre a memória principal e a cache, seja mais larga do que uma mensagem por vez

## Memória Secundária
* Será representada por um vector, a fim de simular um disco rígido que só faz leitura sequencial, o processador poderá
escrever diretamente nela.
* Vai ser preciso criar funções de, ir para o início do vetor, ir para o final, encontrar o dado desejado, ler e 
escrever.

