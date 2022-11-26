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
    std::unordered_map<std::string, std::string> umap_identifier; // key is token and value is identifier
    std::unordered_map<std::string, std::string> umap_token;      // key is identifier and values is token
    std::unordered_map<std::string, std::string> umap_type;       // key is token and value is datatype
    std::unordered_map<std::string, int> umap_lod;                // key is token and value is lod
    static int TOKEN_COUNT;     // total number of tokens during the compilation

    public:
        bool insert(std::string, std::string, int);  // returns 0 if already exists
        bool lookup(std::string);
        std::string get_token(std::string);
        std::string get_identifier(std::string);
        std::string get_datatype(std::string);
        int get_lod(std::string);
        void show();

        std::string tokenize(std::string);

        static int get_token_count() { return SymbolTable::TOKEN_COUNT; }
        static void increment_token_count() { SymbolTable::TOKEN_COUNT++; }
};

int SymbolTable::TOKEN_COUNT = 0;       // initialization of TOKEN_COUNT

bool SymbolTable::insert(std::string identifier, std::string datatype, int lod) {
    if (this->lookup(identifier)) {
        return false;
    } else {
        std::string tk = this->tokenize(identifier);
        this->umap_identifier.insert(make_pair(tk, identifier));
        this->umap_token.insert(make_pair(identifier, tk));
        this->umap_type.insert(make_pair(tk, datatype));
        this->umap_lod.insert(make_pair(tk, lod));

        return true;
    }
}

bool SymbolTable::lookup(std::string identifier) {
    if (this->umap_token.find(identifier) == this->umap_token.end()) return false;
    
    return true;
}

std::string SymbolTable::get_datatype(std::string token) {
    if (this->lookup(this->get_identifier(token))) return this->umap_type.at(token);
    return "404";
}

int SymbolTable::get_lod(std::string token) {
    if (this->lookup(this->get_identifier(token))) return this->umap_lod.at(token);
    return 0;
}

std::string SymbolTable::get_token(std::string identifier) {
    if (this->lookup(identifier)) return this->umap_token.at(identifier);
    return "404";
}

std::string SymbolTable::get_identifier(std::string token) {
    if (this->umap_identifier.find(token) == this->umap_identifier.end()) {
        return "404";
    } else {
        return this->umap_identifier.at(token);
    }
}

std::string SymbolTable::tokenize(std::string identifier) {
    this->increment_token_count();

    if (ENV.is_readable == true) {
        std::string word = "token" + std::to_string(this->get_token_count());
        return word;    
    }

    std::string token;

    char rndChar = 0;
    while (true) {
        for (int i=0; i<6; i++) {
            rndChar = rand()%(90-65+1)+65; // Generate the number, assign to variable.
            token.push_back(rndChar);
        }

        if(!this->lookup(token)) break;
    }

    return token;
}

SymbolTable ST;