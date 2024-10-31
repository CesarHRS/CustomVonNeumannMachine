// TODO
// Handle vector at data
// Fix convertion error adn check values

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <cstdint>
#include <algorithm>

//const int MEMORY_SIZE = 65536; // 16-bit address space
const int MEMORY_SIZE = 128; // 16-bit address space

std::string padName(const std::string& name) {
    return name + std::string(16 - name.length(), '#');
}

void loadProgram(const std::string& inputFile) {
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::unordered_map<std::string, int> labelAddresses;
    std::unordered_map<std::string, int> variableAddresses;
    std::vector<std::string> instructions;
    std::vector<uint32_t> memory(MEMORY_SIZE, 0); // Initialize memory
    int dataAddress = 0;
    int memAddr = 0;
    
    std::string line;
    int address = 0;

    // Read instructions and data
    while (std::getline(file, line)) {
      std::string trimmedLine = line;
      trimmedLine.erase(trimmedLine.find_last_not_of(" \n\r\t") + 1);
        
      // data section
      if (trimmedLine.find(".data") != std::string::npos) {
        while (std::getline(file, line)) {
          std::cout << line << std::endl;
          std::istringstream dataStream(line);
          std::string variableName;
          int value;
          
          // Extract variable name and value from the format "var: value"
          if (dataStream >> variableName) {
            size_t colonPos = variableName.find(':');
            if (colonPos != std::string::npos) {
              variableName = variableName.substr(0, colonPos); 
              dataStream >> value; 
                  
              variableAddresses[padName(variableName)] = dataAddress; 
              memory[dataAddress] = value; 
              dataAddress += 1; 
            }
          }    
        }
      
      // break if at the end of the data section
      break; 
    }
    // Check for labels
    else if (trimmedLine.find(":") != std::string::npos) {
        size_t colonPos = trimmedLine.find(":");
        std::string label = trimmedLine.substr(0, colonPos);
        labelAddresses[padName(label)] = address; 

        if (std::getline(file, line)) {
          std::cout << label << std::endl;
          instructions.push_back(line); // Store instruction
          address += 1; 
        }
    }
      // Regular instruction
    else {
        instructions.push_back(trimmedLine);
        address += 1; 
      }
    }

    // Substitute addresses in instructions
    for (auto instruction : instructions) {
        for (const auto& [label, addr] : labelAddresses) {
            size_t pos = instruction.find(label);
            if (pos != std::string::npos) {
                // Substitute label with address
                instruction.replace(pos, label.length(), std::bitset<16>(addr).to_string());
            }
        }
        for (const auto& [varName, addr] : variableAddresses) {
            size_t pos = instruction.find(varName);
            if (pos != std::string::npos) {
                // Substitute variable with address
                instruction.replace(pos, varName.length(), std::bitset<16>(addr).to_string());
            }
        }
        
        size_t pos = instruction.find("#");
        if (pos != std::string::npos) {
            std::cerr << "Can't resolve symbol at instruction: " << instruction << std::endl; 
        }

        // Convert instruction string to binary and store in memory
        try {
            memory[memAddr++] = std::stoul(instruction, nullptr, 2);
            std::cout << "Unsigned long value: " << instruction << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Conversion error: " << e.what() << std::endl;
        }
        memAddr++;
    }

    // Output the loaded memory for verification
    for (size_t i = 0; i < memory.size(); ++i) {
        std::cout << "Address " << (i) << ": " << std::bitset<32>(memory[i]) << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    loadProgram(argv[1]);
    return 0;
}
