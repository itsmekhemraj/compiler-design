#include <iostream>
#include <bits/stdc++.h>

#include "./modules/misc.cpp"
#include "./modules/error_handler/error_handler.cpp"
#include "./modules/env.cpp"
#include "./modules/symbol_table/symbol_table.cpp"
#include "./modules/tokens.cpp"
#include "./modules/frontend/lexer.cpp"
#include "./modules/frontend/parser.cpp"

// the main function can also take arguments from the terminal
int main(int argc, char*argv[]) { 
    bool green = true;                      // stores the condition of compiler
    green = ENV.set_info(argc, argv);       // setting up the environment confifguration
    if (!green) { ENV.abort(); return 0;}

    srand(time(NULL));              // seeds the time

    green = LEXER.parse(ENV.inputfile);     // Lexical analysis starts here and creates a file `wiz.lex`
    LEXER.kill();
    // if there is syntax or semantic errors abort the process
    if (!green) { ENV.abort(); return 0; }
    
    green = PARSER.parse("wiz.lex");        // Syntax and semantic analysis starts her and the output is true if are correct else false
    
    // if there is syntax or semantic errors abort the process
    if (!green) { ENV.abort(); return 0; }

    return 0;   
}