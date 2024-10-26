/* TODO
- Check if the register are correctly translated to binary
- Create label table
- Make the correct parsing of the syntax: lw $t var | lw $t, i($s) 
    - if not loading based on register pad the var with #
    - This syntax is invalid: lw $t, i(var)
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <bitset>

using namespace std;

const unordered_map<string, int> instructionMap = {
    {"add", 0b100000}, {"and", 0b100100}, {"div", 0b011010}, {"mult", 0b011000}, {"nor", 0b100111},
    {"or", 0b100101}, {"sll", 0b000000}, {"sra", 0b000011}, {"sub", 0b100010}, {"xor", 0b100110},
    {"slt", 0b101010}, {"beq", 0b000100}, {"bne", 0b000101}, {"jr", 0b001000}, {"lb", 0b100000},
    {"lw", 0b100011}, {"sb", 0b101000}, {"sw", 0b101011}
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
                    iss >> rd >> rs >> rt; // rd, rs, rt
                    output += encodeRType(instruction, rs, rt, rd, 0);
                } else if (instruction == "beq" || instruction == "bne") {
                    iss >> rs >> rt >> immediate; // rs, rt, immediate
                    output += encodeIType(instruction, rs, rt, immediate);
                } else if (instruction == "jr") {
                    iss >> rs; // rs
                    output += encodeJType(instruction, rs);
                }
                // Add handling for other instructions similarly
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
