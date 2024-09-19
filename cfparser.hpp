#ifndef CFPARSER_HPP
#define CFPARSER_HPP

#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>


class CFParser {
private: 
    char sectionChar = '.';
    char defvarChar = ':';

    std::string FILENAME;

    std::string removeSectionChar(std::string &str) {
        std::string result;
        for (char c : str) {
            if (c != sectionChar) {
                result += c;  
            }
        }
        str = result;  
        return result;
    }

    std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> result;
        std::string current;
        
        for (char ch : str) {
            if (ch == delimiter) {
                if (!current.empty()) {
                    result.push_back(current);
                    current.clear();
                }
            } else {
                current += ch;
            }
        }
        if (!current.empty()) {
            result.push_back(current);
        }
        
        return result;
    }

public:
    std::map<std::string, std::map<std::string, std::string>> Dict;

    void read(const std::string& filename) {
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "" << filename << std::endl;
            return;
        }
        else if (file.is_open()) {
            FILENAME = filename;
        }
        std::string line;
        std::string currentSection;

        while (std::getline(file, line)) {
            
            if (!line.empty() && line[0] == sectionChar) {
                
                currentSection = removeSectionChar(line);
                Dict[currentSection] = {{}};
                continue;
            }

            std::vector<std::string>data = split(line, defvarChar);
            Dict[currentSection][data[0]] = data[1];
        }
        file.close();
    }

    void e_update(std::string section, std::string valuename, std::string value) { // easy update (section, valuename, value)
        std::map<std::string, std::map<std::string, std::string>> tempDict;
        tempDict[section] = {{valuename, value}};
        f_update(tempDict);
    }

    void f_update(const std::map<std::string, std::map<std::string, std::string>>& UpdatedDict) { // full update (with map)
        std::ifstream infile(FILENAME);
        if (!infile.is_open()) {
            std::cerr << "Couldn't open file: " << FILENAME << std::endl;
            return;
        }

        std::stringstream buffer;
        buffer << infile.rdbuf();
        infile.close();

        std::string content = buffer.str();
        std::string currentSection;

        if (!content.empty() && content.back() != '\n') {
            content += '\n';
        }

        for (const auto& Section : UpdatedDict) {
            std::size_t sectionPos = content.find(sectionChar + Section.first);
            if (sectionPos == std::string::npos) {
                content += sectionChar + Section.first + "\n";
                for (const auto& Pair : Section.second) {
                    Dict[Section.first] = {{Pair.first, Pair.second}};
                    content += Pair.first + defvarChar + Pair.second + "\n";
                }
            } else {
                currentSection = Section.first;
                std::size_t nextSectionPos = content.find(sectionChar, sectionPos + 1); 
                
                for (const auto& Pair : Section.second) {
                    std::size_t varPos = content.find(Pair.first + defvarChar, sectionPos);
                    
                    if (varPos == std::string::npos || (nextSectionPos != std::string::npos && varPos > nextSectionPos)) {
                        if (nextSectionPos == std::string::npos) {
                            content += Pair.first + defvarChar + Pair.second + "\n";
                        } else {
                            content.insert(nextSectionPos, Pair.first + defvarChar + Pair.second + "\n");
                        }
                    } else {
                        std::size_t endPos = content.find("\n", varPos);
                        content.replace(varPos, endPos - varPos, Pair.first + defvarChar + Pair.second);
                    }
                }
            }
        }

        std::ofstream outfile(FILENAME);
        if (!outfile.is_open()) {
            std::cerr << "Couldn't open file: " << FILENAME << std::endl;
            return;
        }
        outfile << content;
        outfile.close();
    }
};

#endif // CFPARSER_HPP