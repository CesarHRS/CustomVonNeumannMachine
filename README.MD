# INTRODUÇÃO

O arquivo que está a ser lido, é referente a documentação do 1º Trabalho prático da disciplina de Sistemas Operacionais,
lecionada pelo Professor Mestre, Michel Pires Dias, do 6ªPeriodo regular, de Engenharia de Computação do CEFET-MG Campus
Divinópolis, nele, tem como principal ideia, o desenvolvimento de um processador que utilize-se da arquitetura de Von
Neumann, e é baseado na arquitetura MIPS, porém, o CPU implementado não possui todas funcionalidades de um processador
MIPS, de forma, que é um CPU mais simplificado possível

# CONTEXTO

## Arquitetura de Von Neumann

A Arquitetura de Von Neumann, ou modelo de Von Neumann, ou Arquitetura de Princeton é uma arquitetura de computadores
baseada em descrições do ciêntista Jonh Von Neumann, entre outros, feitas por volta do ano de 1945. Nela, é descrito uma
arquitetura para computadores digitais, que possuia os seguintes componentes:

* Uma unidade de processamento, que continha tanto uma unidade lógica e aritmética (ULA ou em inglês, ALU), uma unidade
  de controle, que continha um registrador de instrução, que possui o endereço de memória da proxima instrução e um
  contador de programa, responsável por marcar qual instrução do código está sendo executada.
* Uma unidade de memória, responsável por armazenar tanto os dados dos programa, quando as instruções do mesmo
* Mecanismos de Input / Output para a realização de uma interface entre o computador e o mundo.

Uma melhor vizualização da arquitetura de Von Neumann pode ser feita por meio da imagem abaixo:
![.][/img/von_neumann_architecture.png "Arquitetura de Von Neumann"]

A arquitetura de Von Neumann ainda é de certo a base das arquiteturas computacionais modernas, como é o caso da MIPS.



## Arquitetura MIPS

Já a arquitetura MIPS, é uma arquiteteura baseada na familia de arquiteturas RISC, desenvolvida pela MIPS Computer
Systems. A arquitetura MIPS foi utilizada por muito tempo, e por esse motivo, possui várias versões. Ele foi utilizada
principalmente dentro da academia, para o estudo, pois é uma das mais simples, que apresenta processadores funcionais e
que posteriormente poderiam ser utilizados, além disso, ela também foi utilizada de basea para acriação de outras
arquiteturas da família RISC, como é o caso da Alpha, porém, atualmente a arquitetura MIPS foi descontinuada, e a atual
dona, MIPS Technologies, esta trabalhando na criação de uma nova arquitetura, desta vez, baseada na familia RISC-V

# CPU

## ALU

### Enum `operation`
Define as operações suportadas pela ALU: ADD, SUB, AND, OR, XOR, NOT_A, PASS_A, SHR, SHL.

### Atributos
- `A`, `B`: Entradas A e B da ALU, que recebem operandos de 32 bits.
- `result`: Resultado da operação (32 bits com sinal).
- `overflow`: Flag de overflow.
- `op`: Operação a ser realizada.

### Métodos
- `calculate()`: Executa a operação especificada.

## CONTROL_UNIT

## REGISTER

### Variáveis
- `value`: Valor de 32 bits armazenado no registrador.

### Funções
- `REGISTER()`: Construtor que inicializa o valor com 0.
- `write(uint32_t new_value)`: Escreve um novo valor no registrador.
- `read() const`: Lê o valor do registrador.
- `reverse_read() const`: Lê o inverso do valor salvo no registrador.

## REGISTER_BANK

### Registradores de Uso Específico
- `pc`: Program Counter
- `mar`: Memory Address Register
- `cr`: Cause Register
- `epc`: Exception Program Counter
- `sr`: Status Register
- `hi`, `lo`: Armazenam resultados de operações de 32 bits
- `ir`: Instruction Register

### Registradores de Uso Geral
- `zero`: Sempre contém 0
- `at`: Reservado para o assembler
- `v0`, `v1`: Contém os valores de retorno de funções
- `a0` - `a3`: Contém os argumentos necessários para as chamadas de função
- `t0` - `t9`: Registradores temporários
- `s0` - `s7`: Registradores salvos
- `k0`, `k1`: Reservados para o sistema operacional
- `gp`, `sp`, `fp`, `ra`: Global Pointer, Stack Pointer, Frame Pointer, Return Address

### Funções
- `REGISTER_BANK()`: Construtor que inicializa o banco de registradores.
- `print_registers() const`: Imprime os valores de todos registradores do banco.

## SECONDARY_MEMORY

### Variáveis
- `storage`: Vetor de 32 bits que simula a memória secundária.

### Funções
- `SECONDARY_MEMORY(size_t size)`: Construtor que inicializa a memória com o tamanho especificado e define todos os valores como 0x0000.

- `write(size_t position, uint32_t value)`: Escreve um valor de 32 bits no endereço especificado.

- `read(size_t position) const`: Retorna o valor armazenado na posição especificada. Retorna 1 em caso de posição inválida.
