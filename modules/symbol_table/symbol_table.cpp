/******************************************************************************************************
*   Program name: Symbol Table,
*   Author name: Niyoj Oli (https://github.com/niyoj), 
*   Created Path: ./modules/symbol_table/symbol_table.cpp,
*   Created Date: 19 Jul 2022, 08:41:24 (DD MON YYYY, HH:MM:SS),
*   Description: This  program file is responsible to create a symbol table which is used by compiler to store the tokens.
*******************************************************************************************************/

#include <unordered_map>        // undordered map is the implementation of hash table data structures in C++ STL
#include <string>               // requires C++ string library
#include <time.h>
/* DOCUMENTATION SECTION ABOUT UNORDERED MAP

Here are some guides about unordered map in C++,
- Unordered map is a simple table like data structure that contains two columns one for key another for values.
- And each uniue key maps to a value.
- The syntax to delcare unordered map is std::unordered_map<datatype1, datatype2> umapName; Here, datatype1 is the datatype of key and datatype2 is the datatype of value.
    Example; std::unordered_map<std::string, int> umap;     // creates a blank hash table

- To insert a row we use, insert member funcion and pass the pair of values as umap.insert(std::make_pair("apple", 1));
Then, the hash table becomes;

+-------------------+---------------+
| string (key)      | int (value)   |
+-------------------+---------------+
| apple             | 1             |
+-------------------+---------------+

- umap.insert(std::make_pair("orange", 2)); umap.insert(std::make_pair("melon", 3));

+------------------+----------------+
| string (key)     | int (value)    |
+------------------+----------------+
| apple            | 1              |
+------------------+----------------+
| orange           | 2              |
+------------------+----------------+
| melon            | 3              |
+------------------+----------------+

- To get the value, with the key we have member function at(KEY);
std::cout<<umap.at("apple");         // outputs 1

*/

// class `SymbolTable` is the symbol table for the compiler. which stores token number as key and identifier as value
class SymbolTable {
    std::unordered_map<std::string, std::string> umap;
    static int TOKEN_COUNT;     // total number of tokens during the compilation

    public:
        void insert(std::string, std::string);
        std::string lookup(std::string);
        std::string tokenize(std::string);

        static int get_token_count() {
            return SymbolTable::TOKEN_COUNT;
        }

        static void increment_token_count() {
            SymbolTable::TOKEN_COUNT++;
        }
};

int SymbolTable::TOKEN_COUNT = 0;       // initialization of TOKEN_COUNT

// function `insert()` is used to make an entry in the symbol table
void SymbolTable::insert(std::string token, std::string identifier) {
    this->umap.insert(std::make_pair(token, identifier));
}

// function `lookup()` is used to lookup an entry in the symbol table and returns #404# if the token is not found
std::string SymbolTable::lookup(std::string token) {
    if (this->umap.find(token) == this->umap.end()) return "#404#";
    return this->umap.at(token);
}

std::string SymbolTable::tokenize(std::string identifier) {
    // checking whether the identifier has been previously tokenized or not
    for (const auto&[key, value]: this->umap) {
        if (value == identifier) return key;
    }

    this->increment_token_count();

    if (ENV.is_readable == true) {
        std::string word = "token" + std::to_string(this->get_token_count());
        return word;    
    }

    std::string token;
    srand(time(NULL)); // seeds the time
    char rndChar = 0;

    while (true) {
        for (int i=0; i<6; i++) {
            rndChar = rand()%(90-65+1)+65; // Generate the number, assign to variable.
            token.push_back(rndChar);
        }

        if(this->lookup(token) == "#404#") break;
    }

    return token;
}

SymbolTable ST;