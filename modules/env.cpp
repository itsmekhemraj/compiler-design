// class `CompilerEnvironemnt` is responsible to take the argumens from terminal from user and set up the environment from the compiler
class CompilerEnvironment {
    public:
        bool is_readable;
        bool is_lexer_only;

        CompilerEnvironment() {
            this->is_readable = false;
            this->is_lexer_only = false; 
        }

        void set_info(int argc, char*argv[]);
};

// function `set_info()` is used to interact with the data members of `CompilerEnvironment`
void CompilerEnvironment::set_info(int argc, char*argv[]) {
    for(int i=0; i<argc; i++) {
        if (std::string(argv[i]) == "--lexer-only") this->is_lexer_only = true;
        if (std::string(argv[i]) == "--readable") this->is_readable = true;
    }
}


CompilerEnvironment ENV;