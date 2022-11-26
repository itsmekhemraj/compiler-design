#include <fstream>      // used for file handling
/*
The arguments for wiz compiler is explained below;
NAME: WIZ - Used for compileing the files written in wiz programming language (*.wiz)

SYNOPSIS: wiz FILE_PATH [--lexer-only] [--readable] [--output FILENAME]

*/

// class `CompilerEnvironemnt` is responsible to take the argumens from terminal from user and set up the environment from the compiler
class CompilerEnvironment {
    public:
        bool is_readable;
        bool is_lexer_only;
        std::string inputfile;          // the path of the input file              
        std::string outputfile;         // the path of the output file

        CompilerEnvironment() {
            this->is_readable = false;
            this->is_lexer_only = false; 
            this->inputfile = "";
            this->outputfile = "";
        }

        bool set_info(int argc, char*argv[]);
        void abort();
};

// function `set_info()` is used to interact with the data members of `CompilerEnvironment`
bool CompilerEnvironment::set_info(int argc, char*argv[]) {
    bool has_error = false;
    for(int i=1; i<argc; i++) {
        
        // if the command arguments has options signified by word followed by double hyphen (--)
        if (std::string(argv[i]).at(0) == '-' && std::string(argv[i]).at(1) == '-') {
            if (std::string(argv[i]) == "--lexer-only") this->is_lexer_only = true;
            if (std::string(argv[i]) == "--readable") this->is_readable = true;
            
            // if --output argument is encountered than it must be followed by the file name
            if (std::string(argv[i]) == "--output") {
                this->outputfile = std::string(argv[i+1]);
                i++;
                continue;
            }

            // if none then throw error
        } else {
            this->inputfile = std::string(argv[i]);

            // checking if the path exists or not
            std::ifstream file;
            file.open(this->inputfile);

            if(file) {
                int len = this->inputfile.length();
                std::string filename = this->inputfile;

                // if does not contain .wiz extension
                if (len<=4) {
                    ERROR.set_error("403", 0);
                    has_error = true;
                } else {
                    if (!(filename.at(len-1) == 'z' && filename.at(len-2) == 'i' && filename.at(len-3) == 'w' && filename.at(len-4) == '.')) {
                        ERROR.set_error("403", 0);
                        has_error = true;
                    }
                }
            } else {
                ERROR.set_error("404", 0);
                has_error = true;
            }

            file.close();
        }
    }

    if (has_error) return false; else return true;
}

void CompilerEnvironment::abort() { ERROR.show_errors(); }

CompilerEnvironment ENV;