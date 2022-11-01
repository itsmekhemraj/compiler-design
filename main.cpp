#include <iostream>

#include "./modules/env.cpp"
#include "./modules/symbol_table/symbol_table.cpp"
#include "./modules/tokens.cpp"
#include "./modules/frontend/lexer.cpp"

// the main function can also take arguments from the terminal
int main(int argc, char*argv[]) { 
    ENV.set_info(argc, argv);       // setting up the environment ocnfifguration

    LEXER.parse(ENV.inputfile);     // Lexical analysis starts here and creates a file `out.lex`
    return 0;   
}