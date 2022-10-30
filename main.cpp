#include <iostream>

#include "./modules/env.cpp"
#include "./modules/symbol_table/symbol_table.cpp"
#include "./modules/tokens.cpp"

// the main function can also take arguments from the terminal
int main(int argc, char*argv[]) { 
    ENV.set_info(argc, argv);
    
    return 0;   
}