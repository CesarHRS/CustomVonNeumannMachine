/* TODO
- Create label table

OPT:
- lw $t0 (offset)$t1) syntax
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <bitset>

using namespace std;

const unordered_map<string, int> instructionMap = {
    {"add", 0b100000},
    {"and", 0b100100},
    {"div", 0b011010},
    {"mult", 0b011000},
    {"sub", 0b100010},
    {"beq", 0b000100},
    {"bne", 0b000101},
    {"bgtz", 0b000111},
    {"bltz", 0b000110},
    {"j", 0b001000},
    {"lw", 0b100011},
    {"sw", 0b101011},
    {"li", 0b101100},
    {"move", 0b101101},
    {"la", 0b101110}
};

const unordered_map<string, int> registerMap = {
    {"$zero", 0b00000}, // Constant zero
    {"$ra", 0b00001},  // Return address
    {"$at", 0b00010},   // Assembler temporary
    {"$v0", 0b00011},   // Value 0
    {"$v1", 0b00100},   // Value 1
    {"$a0", 0b00101},   // Argument 0
    {"$a1", 0b00110},   // Argument 1
    {"$a2", 0b00111},   // Argument 2
    {"$a3", 0b01000},   // Argument 3
    {"$t0", 0b01001},   // Temporary 0
    {"$t1", 0b01010},   // Temporary 1
    {"$t2", 0b01011},   // Temporary 2
    {"$t3", 0b01100},   // Temporary 3
    {"$t4", 0b01101},   // Temporary 4
    {"$t5", 0b01110},   // Temporary 5
    {"$t6", 0b01111},   // Temporary 6
    {"$t7", 0b10000},   // Temporary 7
    {"$s0", 0b10001},   // Saved 0
    {"$s1", 0b10010},   // Saved 1
    {"$s2", 0b10011},   // Saved 2
    {"$s3", 0b10100},   // Saved 3
    {"$s4", 0b10101},   // Saved 4
    {"$s5", 0b10110},   // Saved 5
    {"$s6", 0b10111},   // Saved 6
    {"$s7", 0b11000},   // Saved 7
    {"$t8", 0b11001},   // Temporary 8
    {"$t9", 0b11010},   // Temporary 9
    {"$k0", 0b11011},   // Kernel 0
    {"$k1", 0b11100},   // Kernel 1
    {"$gp", 0b11101},   // Global pointer
    {"$sp", 0b11110},   // Stack pointer
    {"$fp", 0b11111},   // Frame pointer
    {"$s8", 0b10000}    // Saved 8 (also $f0 in floating point)
};

unordered_map<string, string> dataMap;

string encodeRType(string op, int rs, int rt, int rd, int shamt) {
    int funct = instructionMap.at(op);
    bitset<6> opcode(0); // R-type has opcode 0
    bitset<5> rsBits(rs);
    bitset<5> rtBits(rt);
    bitset<5> rdBits(rd);
    bitset<5> shamtBits(shamt);
    bitset<6> functBits(funct);
    return (opcode.to_string() + rsBits.to_string() + rtBits.to_string() + 
            rdBits.to_string() + shamtBits.to_string() + functBits.to_string());
}

string encodeIType(string op, int rs, int rt, int immediate) {
    int opcode = instructionMap.at(op);
    bitset<6> opcodeBits(opcode);
    bitset<5> rsBits(rs);
    bitset<5> rtBits(rt);
    bitset<16> immBits(immediate);
    return (opcodeBits.to_string() + rsBits.to_string() + rtBits.to_string() + immBits.to_string());
}

string encodeJType(string op, int address) {
    int opcode = instructionMap.at(op);
    bitset<6> opcodeBits(opcode);
    bitset<26> addrBits(address);
    return (opcodeBits.to_string() + addrBits.to_string());
}

int getRegisterCode(const string &reg) {
    if (registerMap.find(reg) != registerMap.end()) {
        return registerMap.at(reg);
    }
    cerr << "Error: Invalid register \"" << reg << "\"" << endl;
    return -1; 
}


string padInstruction(const string& instruction) {
    if (instruction.length() < 32) {
        return instruction + string(32 - instruction.length(), '#'); // Pad with '#'s
    }
    return instruction; 
}

string removeComments(const string &line) {
    size_t commentPos = line.find('#');
    if (commentPos != string::npos) {
        return line.substr(0, commentPos); 
    }
    return line; 
}
void processAssemblyFile(const string &filename, string &output) {
    ifstream inFile(filename);
    string line;
    bool textSection = false;
    bool dataSection = false;
    int lineNum = 0;
    
    if (!inFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    while (getline(inFile, line)) {

        line = removeComments(line); 

        if (line.empty()) {
            continue; 
        }

        istringstream iss(line);
        string instruction;
        iss >> instruction;


        if (instruction == ".data") {
            dataSection = true;
        }

        if(instruction == ".text"){
            textSection = true;
            dataSection = false;
        }

        if(textSection){
            int rs = 0, rt = 0, rd = 0, immediate = 0;
            if (instructionMap.find(instruction) != instructionMap.end()) {
                if (instruction == "add" || instruction == "sub" || instruction == "div" || instruction == "mult") {

                    string rdStr, rsStr, rtStr;
                    iss >> rdStr >> rsStr >> rtStr; 
                    rd = getRegisterCode(rdStr);
                    rs = getRegisterCode(rsStr);
                    rt = getRegisterCode(rtStr);

                    if (rd != -1 && rs != -1 && rt != -1) {
                        output += encodeRType(instruction, rs, rt, rd, 0);
                        output += "\n";
                    }                

                } else if (instruction == "beq" || instruction == "bne" || instruction == "bgtz" || instruction == "bltz") {
                    string rsStr, rtStr;
                    iss >> rsStr >> rtStr >> immediate; 
                    rs = getRegisterCode(rsStr);
                    rt = getRegisterCode(rtStr);

                    if (rs != -1 && rt != -1) {
                        output += encodeIType(instruction, rs, rt, immediate);
                        output += "\n";
                    }                

                } else if (instruction == "j") {
                    string rsStr;
                    iss >> rsStr; 
                    rs = getRegisterCode(rsStr);
                    output += encodeJType(instruction, rs);
                    output += "\n";
                } 
                else if (instruction == "li" || instruction == "move" || instruction == "la") {
                    string rtStr;
                    iss >> rtStr >> immediate; 
                    rt = getRegisterCode(rtStr);
                    if (rt != -1) {
                        output += encodeIType(instruction, 0, rt, immediate); // rs is not used, set to 0
                        output += "\n";
                    }

                }
                
                else if (instruction == "lw" || instruction == "sw") {
                    string rsStr, varName;
                    iss >> rsStr >> varName; 
                    rs = getRegisterCode(rsStr);

                    if (rs != -1 ) {
                        if (dataMap.find(varName) != dataMap.end()) {
                            output += padInstruction(encodeIType(instruction, rs, 0, varName));
                            output += "\n";
                        } else {
                            cerr << "Error: Variable \"" << varName << "\" not found in data section." << endl;
                        }
                    }
                }            
            }
            else{
              cerr << "Invalid instruction \"" << instruction << "\" at " << lineNum << endl;
            }
        }
        else{

            string varName;
            int varValue;
            iss >> varName >> varValue; // assuming format: varName: value
            dataMap[varName] = varValue 
        }
        
        lineNum++;
    }
    inFile.close();
}


void writeOutputFile(const string &output, const unordered_map<string, string> &dataMap) {
    ofstream outFile("output.bin");
    
    outFile << ".data{" << endl;
    for (const auto &entry : dataMap) {
        outFile << entry.first << ":" << entry.second << endl;
    }
    outFile << "}" << endl;

    for (char bit : output) {
        outFile << bit;
    }
    outFile << endl;

    outFile.close();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename.asm>" << endl;
        return 1;
    }

    string output;
    processAssemblyFile(argv[1], output);
    writeOutputFile(output, dataMap);

    cout << "Assembly completed. Output written to output.bin" << endl;
    return 0;
}
