// The purpose of this file is to show how to use the cf parser properly
#include "parser.hpp"

int main() 
{
    Parser parser; // Initialize parser object
    parser.read("file.dictionary"); // read the file (parse file content into a dictionary)

    // Defining a variable with 'name' value:
    std::string name = parser.dictionary["stats"]["name"];

    // Manipulating the cf variable:
    parser.dictionary["stats"]["age"] = "93"; // after parsing the file, data is saved to the cf dictionary
    parser.update(); // After manipulating cf var, you got to update it 

    // Using the e_update function
    parser.e_update("stats", "name", "John");

    // Using the f_update function
    std::map<std::string, std::map<std::string, std::string>> dict; // define a dictionary
    dict["stats"]["name"] = "Mark"; // add 'stats' section, value name and finally the value
    parser.f_update(dict);
    
}
