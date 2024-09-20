# CFParser
CFParser is a config parser header for C++

## Usage
#### Include header and initialize parser object:
```cpp
#include "cfp.hpp"

int main() {
  CFParser parser;
}
```
#### Read values:
```cpp
#include "cfp.hpp"

int main() {
  CFParser parser;
  parser.read("file.cf"); // read config file
  std::string name = parser.cf["stats"]["name"]; // cf dictionary in parser object holds parsed content from 'file.cf'
  std::cout << "My name is " << name << std::endl; // print out
}
```
#### Update, create values:
```cpp
#include "cfp.hpp"

int main() {
    CFParser parser; // Initialize parser object
    parser.read("file.cf"); // read the file (parse file content into a dictionary)

    // Update or add by manipulating the cf variable:
    parser.cf["stats"]["age"] = "93"; // after parsing the file, data is saved to the cf dictionary
    parser.update(); // After manipulating cf var, you got to update it

    // The e_update function
    parser.e_update("stats", "name", "John");

    // The f_update function
    std::map<std::string, std::map<std::string, std::string>> dict; // define a dictionary
    dict["stats"]["name"] = "Mark"; // add 'stats' section, value name and finally the value
    parser.f_update(dict);
    
}
```
