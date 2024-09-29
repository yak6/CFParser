# CF parser
CFParser is a configuration file parser with a slightly strange syntax. It is compatible with the C++11 standard and above.
This is a very simple header file that is not for professional use!
## Installation
Download **[cfp.hpp](https://github.com/yak6/configparser/blob/main/cfp.hpp)** header file and include it.
```cpp
#include "cfp.hpp"
```

## Reading file, loading variable values
Initialize parser object and load the file:
```cpp
CFParser parser;
parser.load("file.cf");
```
After loading the file, it's content is saved to 'cf' variable (map) in this object. For example, to access 'name', in section 'stats' you will have to:  
```cpp
std::string enemy = parser.cf["stats"]["name"];
```
That's how you can save 'name' to enemy variable.
## Updating/Writing
You can update/write in 3 different ways:
### 1. Manipulating the 'cf' dictionary 
```cpp
parser.cf["stats"]["hair_color"] = "black"; // adding/replacing 'hair_color' to 'stats' section in 'cf' variable 
parser.update(); // the function dumps the contents of 'cf' to previously loaded file
```
### 2. Easy update function 
```cpp
parser.e_update("stats", "name", "John"); // to previously loaded file update 'name' value with 'John' in 'stats' section
```
### 3. Full update function
```cpp
std::map<std::string, std::map<std::string, std::string>> dict; // define a dictionary
dict["stats"]["name"] = "Mark"; // write some content into the 'dict' dictionary
parser.f_update(dict); // update previously loaded file with 'dict' varible
```
### If you don't enjoy it's syntax, feel free to change it by editing
```cpp
const char sectionChar = '.';
const char defvarChar = ':';
```
