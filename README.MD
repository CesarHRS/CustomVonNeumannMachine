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
que posteriormente poderiam ser utilizados, além disso, ela também foi utilizada de base para a criação de outras
arquiteturas da família RISC, como é o caso da Alpha, porém, atualmente a arquitetura MIPS foi descontinuada, e a atual
dona, MIPS Technologies, esta trabalhando na criação de uma nova arquitetura, desta vez, baseada na familia RISC-V

# CPU
A CPU é composta por 3 blocos principais: ULA (ou ALU em inglês), Unidade de Controle, Registradores. É o principal componente 
responsável por processar todas as instruções e realizar operações fundamentais para o funcionamento dos programas e do sistema operacional. 
A CPU executa essa tarefa através de um ciclo constante de busca, decodificação e execução de instruções, conhecido como o ciclo de instrução.
O ciclo de instruções da CPU é dividido em:

- `IF (Instruction Fetch): ` A CPU obtém a próxima instrução da memória, que é indicada pelo Contador de Programa (PC), e a carrega no Registrador de Instrução (IR).
- `ID (Instruction Decode): ` A Unidade de Controle interpreta a instrução no IR e determina quais componentes internos e operações são necessários para executá-la, carregando os operandos nos registradores.
- `EX (Execute): `  ULA realiza operações aritméticas ou lógicas que foram passadas nas instruções.
- `MEM (Memory Access): ` Vai efetuar a escrita ou leitura da memoria principal.
- `WB (Write Back): ` O registrador especificado vai armazenar o resultado da operação.


O **Pipeline** é um técnica que vai permitir que executemos essas instruções ao mesmo tempo em estagio diferentes, aumentando a eficiência da CPU. Exemplo:
Enquanto uma instrução está sendo buscada, outras podem estar sendo decodificadas ou ate memso executadas.


## ULA ou ALU

A Unidade Lógica e Aritmética é responsável por realizar operações 
matemáticas e lógicas . Ela é essencial para o processamento de dados, já que executa operações sobre os 
números e dados binários que a CPU manipula. A ULA, junto com os registradores e a unidade de controle, constitui 
o núcleo da CPU. A ULA também pode retornar sinais de estado e flags, nesta ULA implementada temos a flag de **overflow**
onde, caso o resultado ultrapasse a capacidade de representação da ULA, essa flag vai assumir _True_.


### Operações Implementadas

1. **ADD (Soma)**  
   - **Descrição**: Soma dois operandos e armazena o resultado.
   - **Tipo**: Aritmética.

2. **SUB (Subtração)**  
   - **Descrição**: Subtrai o segundo operando do primeiro.
   - **Tipo**: Aritmética.

3. **MUL (Multiplicação)**  
   - **Descrição**: Multiplica dois operandos.
   - **Tipo**: Aritmética.

4. **DIV (Divisão)**  
   - **Descrição**: Divide o primeiro operando pelo segundo.
   - **Tipo**: Aritmética.

5. **BEQ (Branch if Equal)**  
   - **Descrição**: Salta para uma instrução específica se os operandos forem iguais.
   - **Tipo**: Controle de fluxo.

6. **BNE (Branch if Not Equal)**  
   - **Descrição**: Salta para uma instrução específica se os operandos forem diferentes.
   - **Tipo**: Controle de fluxo.

7. **BLT (Branch if Less Than)**  
   - **Descrição**: Salta para uma instrução específica se o primeiro operando for menor que o segundo.
   - **Tipo**: Controle de fluxo.

8. **BGT (Branch if Greater Than)**  
   - **Descrição**: Salta para uma instrução específica se o primeiro operando for maior que o segundo.
   - **Tipo**: Controle de fluxo.

9. **BGTI (Branch if Greater Than Immediate)**  
   - **Descrição**: Salta se o operando for maior que um valor imediato.
   - **Tipo**: Controle de fluxo.

10. **BLTI (Branch if Less Than Immediate)**  
    - **Descrição**: Salta se o operando for menor que um valor imediato.
    - **Tipo**: Controle de fluxo.

11. **LW (Load Word)**  
    - **Descrição**: Carrega um valor da memória para um registrador.
    - **Tipo**: Transferência de dados.

12. **LA (Load Address)**  
    - **Descrição**: Carrega um endereço de memória para um registrador.
    - **Tipo**: Transferência de dados.

13. **ST (Store)**  
    - **Descrição**: Armazena o valor de um registrador em uma posição de memória.
    - **Tipo**: Transferência de dados.

### Estruturação

### Atributos
- `A`, `B`: Entradas A e B da ALU, que recebem operandos de 32 bits.
- `result`: Resultado da operação (32 bits com sinal).
- `overflow`: Flag de overflow.
- `op`: Operação a ser realizada.

### Funções
- `calculate()`: Executa a operação especificada.


## CONTROL_UNIT
A Unidade de Controle é uma parte essencial da CPU que coordena e gerencia a execução de instruções no processador. Ela 
atua como o "cérebro" da CPU, determinando quais operações devem ser realizadas, em qual ordem e com quais dados. As instruções 
citadas no ciclo da CPU são realizadas aqui, definidas em que ordem vão ser executadas e os operandos dessas instruções.  

### Estruturação

#### Instruction_Data

- `source_register`: Variavel String
- `target_register`: Variavel String
- `destination_register`: Variavel String
- `op`: Variavel String
- `addressRAMResult`: Variavel String

#### Control_Unit

- `op`: Variavel do tipo operação
- `data`: Vetor de Instruções
- `InstructionMap`: Map de operação e seu opcode

#### Funções 

- `Get_immediate`: 
- `Pick_Code_Register_Load`: 
- `Get_destination_Register`:
- `Get_target_Register`:
- `Get_source_Register`:
- `Identificacao_instrucao`:
- `Fetch`:
- `Decode`:
- `Execute_Aritmetic_Operation`:
- `Execute_Operation`:
- `Execute_Loop_Operation`:
- `Execute`:
- `Memory_Acess`:
- `Write_Back`: 


## REGISTER
Unidade individual de armazenamento, usado para armazenar dados temporários, 
endereços de memória ou informações de controle.

### Variáveis
- `value`: Valor de 32 bits armazenado no registrador.

### Funções
- `REGISTER()`: Construtor que inicializa o valor com 0.
- `write(uint32_t new_value)`: Escreve um novo valor no registrador.
- `read() const`: Lê o valor do registrador.
- `reverse_read() const`: Lê o inverso do valor salvo no registrador.


## REGISTER_BANK
Conjunto de registradores, proporcionando armazenamento temporário para múltiplos dados. Há registradores 
especificos e de uso geral nesssa implementação:

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


# MEMORY 

## MEMORYCELL
A menor unidade de armazenamento, foi implementada uma estrutura dinâmica, cada celula de memoria
possúi endereço único. 

### Atributos
- `value`: O valor armazenado em memória será um inteiro sem sinal de 32 bits. 
- `next`: Um ponteiro usado para  criar uma estrutura dinâmica com o struct.

### Métodos
- `write(const uint32_t new_value)`: Grava o valor de new_value na variável value. 
- `read()`: Lê o valor armazenado no atributo **value**.
- `reverse_read()`: Lê o inverso do valor armazenado em memória pelo atributo **value**.

## MAINMEMORY
É usada para armazenar dados voláteis, como instruções em uso pelo CPU. (RAM)

### Atributos
- `NumOfi`: Nùmero de linhas da estrutura de dados. 
- `NumOfj`: Número de colunas da estrutura de dados.
- `MemoryCell`: Um ponteiro de ponteiro que define a estrutura de dados.

### Métodos
- `InsertData`: Função de adiciona um valor na estrutura de dados.
- `EraseData`: Apaga os dados na estrutura de dados.
- `EmptyLine`: Verifica se a estrutura está vazia em uma das linhas. 

## SECONDARY_MEMORY
Memoria utilizada para guardar programas e dados á longo prazo.
### Variáveis
- `storage`: Vetor de 32 bits que simula a memória secundária.

### Funções
- `SECONDARY_MEMORY(size_t size)`: Construtor que inicializa a memória com o tamanho especificado e define todos os valores como 0x0000.

- `write(size_t position, uint32_t value)`: Escreve um valor de 32 bits no endereço especificado.

- `read(size_t position) const`: Retorna o valor armazenado na posição especificada. Retorna 1 em caso de posição inválida.

# Programação

As instruções supportadas pela a arquitetura são as seguintes:

- `add`: Realiza a soma de dois operandos e armazena o resultado.
- `div`: Realiza a divisão de dois operandos e armazena o resultado no terceito.
- `mult`: Multiplica dois operandos e armazena o resultado no terceito.
- `sub`: Realiza a subtração de dois operandos e armazena o resultado no terceito.
- `beq`: Realiza um desvio condicional se os dois operandos forem iguais.
- `bne`: Realiza um desvio condicional se os dois operandos forem diferentes.
- `bgt`: Desvia se o primeiro operando for maior que o segundo.
- `bgti`: Desvio condicional se o primeiro operando for maior ou igual o segundo.
- `blt`: Desvia se o primeiro operando for menor que o segundo.
- `blti`: Desvio condicional se o primeiro operando for menor ou igal o segundo.
- `j`: Desvio incondicional para a label.
- `lw`: Carrega uma palavra da memória para um registrador.
- `sw`: Armazena uma palavra de um registrador na memória.
- `li`: Carrega um valor imediato em um registrador.
- `la`: Carrega o endereço de uma variável em um registrador.
- `print`: Exibe o valor de um registrador ou uma variável na saída padrão.

Além disso são suportados a declaração de varíaveis inteiras e vetores, juntamente com o labels para controle de fluxo.
Exemplo de programa simples:
```
main:
li $t0 0
li $t1 10
li $t3 100
j loop

loop:
print $t0
add $t0 $zero $t1
blt $t0 $t3 loop

```

# Compilação e Execução

<p>
    <i>Este código possui um arquivo CmakeLists.txt</br>As diretrizes de execução deste Cmake são:<i>
    <table border="1">
      <tr><td><u>cmake CMakeLists.txt</u></td> <td>Apaga a última compilação realizada contida na pasta build</td></tr>
      <tr><td><u>make</u></td> <td>Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build.</td></tr>
      <tr><td><u>./Assembler testes/example.asm</td></tr>
      <tr><td><u>mv output.bin testes</td></tr>
      <tr><td><u>./CustomVonNeumannMachine testes/output.bin </u></td> <td>Executa com programa da pasta teste </td></tr>
    </table>
</p>

# Autores

Frank Leite Lemos <br>
Getulio Santos Mendes <br>
Cesar Henrrique Soares <br>
João Pedro Freitas de Paula Dias <br>
Joao Gustavo Silva Guimarães <br>
Leandro Sousa Costa <br>
