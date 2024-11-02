/* TODO
- Put end instruction at the end of each label

OPT:
- lw $t0 (offset)$t1) syntax
- jal for function call
- jr for return
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <algorithm>
 
using namespace std;

const unordered_map<string, int> instructionMap = {
    {"add", 0b000000},
    {"and", 0b000001},
    {"div", 0b000010},
    {"mult", 0b000011},
    {"sub", 0b000100},
    {"beq", 0b000101},
    {"bne", 0b000110},
    {"bgt", 0b000111},
    {"bgti", 0b001000},
    {"blt", 0b001001},
    {"blti", 0b001010},
    {"j", 0b001011},
    {"lw", 0b001100},
    {"sw", 0b001101},
    {"li", 0b001110},
    {"la", 0b001111},
    {"print", 0b001000},
    {"end",0b111111}
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

unordered_map<string, vector<int>> dataMap;

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

string encodeIType(string op, int rs, int rt,string immediate) {
    int opcode = instructionMap.at(op);
    bitset<6> opcodeBits(opcode);
    bitset<5> rsBits(rs);
    bitset<5> rtBits(rt);
    bitset<16> immBits;

    try {
        immBits = bitset<16>(stoi(immediate));  // Convert to 16-bit binary
    } // if it's a label just use the name 
    catch (invalid_argument&){
        return (opcodeBits.to_string() + rsBits.to_string() + rtBits.to_string() + immediate);
    }
    
    return (opcodeBits.to_string() + rsBits.to_string() + rtBits.to_string() + immBits.to_string());
}

string encodeJType(string op, string address) {
    int opcode = instructionMap.at(op);
    bitset<6> opcodeBits(opcode);
    bitset<26> addrBits(address);
    return (opcodeBits.to_string() + addrBits.to_string());
}

string cleanRegisterString(const string& reg) {
    string cleaned = reg;
    cleaned.erase(remove(cleaned.begin(), cleaned.end(), ','), cleaned.end()); // Remove commas
    cleaned.erase(remove_if(cleaned.begin(), cleaned.end(),[](unsigned char c) { return isspace(c); }), cleaned.end()); // Remove spaces
    return cleaned;
}

int getRegisterCode(const string &reg) {   
    string cleanedReg = cleanRegisterString(reg);

    if (registerMap.find(cleanedReg) != registerMap.end()) {
        return registerMap.at(cleanedReg);
    }
    cerr << "Error: Invalid register \"" << cleanedReg << "\"" << endl;
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
    bool insideLabel = false;
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
            textSection = false;
            continue;
        }

        if(instruction == ".text"){
            textSection = true;
            dataSection = false;
            continue;
        }

        if(textSection){

            // Output label if present
            size_t colonPos = line.find(':');
            if (colonPos != string::npos) {
                
                if(insideLabel){
                    output += encodeIType("end", 0, 0, std::string(16, '0')); // Add end instruction
                    output += "\n";               
                }
                
                string labelName = line.substr(0, colonPos);
                if (labelName.length() > 16) {
                    cerr << "Error: Label \"" << labelName << "\" exceeds the maximum length of 16 characters." << endl;
                }                
                output += labelName + ":\n"; 
                insideLabel = true;

                continue;
            }
            
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

                } else if (instruction == "beq" || instruction == "bne" || instruction == "bgt" || instruction == "blt") {
                    string rsStr, rtStr, immediate;
                    iss >> rsStr >> rtStr >> immediate; 
                    rs = getRegisterCode(rsStr);
                    rt = getRegisterCode(rtStr);

                    if (rs != -1 && rt != -1) {
                        output += padInstruction(encodeIType(instruction, rs, rt, immediate));
                        output += "\n";
                    }                

                } else if (instruction == "j") {
                    string addrStr;
                   
                    try {
                        iss >> addrStr; 
                        output += padInstruction(encodeJType(instruction, addrStr));
                        output += "\n";                    
                    } catch (invalid_argument&) {
                            cerr << "Error: Invalid address \"" << addrStr << "\" in instruction at line " << lineNum << endl;
                    }                
                } 
                else if (instruction == "li" || instruction == "move" || instruction == "la") {
                    string rtStr, immediate;
                    iss >> rtStr >> immediate; 
                    rt = getRegisterCode(rtStr);
                    if (rt != -1) {
                        output += padInstruction(encodeIType(instruction, 0, rt, immediate)); // rs is not used, set to 0
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
                else if (instruction == "print") {
                    string arg;
                    iss >> arg;
                    // Check if arg is a register or a variable
                    if (getRegisterCode(arg) != -1) {
                        int regCode = getRegisterCode(arg);
                        output += encodeIType("print", 0, regCode, std::string(16,'0')); 
                        output += "\n";
                    } else {
                        output += padInstruction(encodeIType("print", 0, 0, arg)); 
                        output += "\n";
                    }
                }            
            }
            else{
              cerr << "Invalid instruction \"" << instruction << "\" at " << lineNum << endl;
            }
        }
        else{
            // Data section
           
            size_t colonPos = line.find(':'); // Find the colon
            if (colonPos != string::npos) {
                string varName = line.substr(0, colonPos); // Get variable name
                string valueStr = line.substr(colonPos + 1); // Get value part

                // Trim whitespace from value string
                valueStr.erase(remove_if(valueStr.begin(), valueStr.end(),[](unsigned char c) { return isspace(c); }), valueStr.end());

                // vector
                if (valueStr.find(',') != string::npos) {
                    istringstream valueStream(valueStr);
                    string value;
                    vector<int> values;
                    while (getline(valueStream, value, ',')) {
                        try {
                            values.push_back(stoi(value));
                        } catch (invalid_argument&) {
                            cerr << "Error: Invalid value for array \"" << varName << "\" at line " << lineNum << endl;
                            break;
                        }
                    }
                    dataMap[varName] = values; 
                }
                // normal value
                else{
                     try {
                        int varValue = stoi(valueStr);
                        dataMap[varName] = { varValue }; // save as single element vector
                    } catch (invalid_argument&) {
                        cerr << "Error: Invalid variable value for \"" << varName << "\" at line " << lineNum << endl;
                    } catch (out_of_range&) {
                        cerr << "Error: Variable value out of range for \"" << varName << "\" at line " << lineNum << endl;
                    }                      
                }
            } 
            else {
                    cerr << "Error: Invalid variable definition in data section at line " << lineNum << endl;
                }        
            }
                
        lineNum++;
    }
    inFile.close();
}


void writeOutputFile(const string &output, const unordered_map<string, vector<int>> &dataMap) {
    ofstream outFile("output.bin");
   
    for (char bit : output) {
        outFile << bit;
    }
    outFile << encodeIType("end", 0, 0, std::string(16, '0')); // Add end of program
    outFile << endl;
    
    outFile << ".data:" << endl;
    for (const auto &entry : dataMap) {
        outFile << entry.first << ": ";

        for (size_t i = 0; i < entry.second.size(); ++i) {
            outFile << entry.second[i];
            if (i < entry.second.size() - 1) {
                outFile << ","; 
            }
        }
        outFile << endl; 
    }    

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
