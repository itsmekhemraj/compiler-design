// including essentials libraries starts here
#include <iostream>
#include <string>
#include <fstream>
// including essentials libraries ends here

class Parser {
    std::ifstream fptr_left;
    std::ifstream fptr_right;
    std::ofstream fptr_output;

    // used to store the position of both file pointers
    int leftptr_pos;
    int rightptr_pos;

    public:
        Parser () {
            this->fptr_output.open("wiz.cpp");
            this->fptr_output<<"#include <iostream>\nusing namespace std;\n\nint main(void) {\n";

            leftptr_pos = 0;
            rightptr_pos = 0;
        }

        ~Parser () {
            this->fptr_output<<"\treturn 0; \n}";
            this->fptr_output.close();
            this->fptr_left.close();
            this->fptr_right.close();
        }

        void move_left_ptr(bool);
        void move_right_ptr();
        char read_left_ptr();
        char read_right_ptr();
        std::string get_token_prefix(std::string);
        bool parse(std::string);
        void update(std::string);
        std::string get_word(char);
};

void Parser::move_left_ptr(bool is_toright = false) {
    if (is_toright) {
        this->fptr_left.seekg(this->rightptr_pos);
        this->leftptr_pos = this->rightptr_pos;
    } else {
        this->leftptr_pos++;
        this->fptr_left.seekg(this->leftptr_pos);
    }
}

char Parser::read_left_ptr() {
    char c = this->fptr_left.get();
    this->fptr_left.seekg(this->leftptr_pos);
    return c;
}

void Parser::move_right_ptr() {
    this->rightptr_pos++;
    this->fptr_right.seekg(this->rightptr_pos);
}

char Parser::read_right_ptr() {
    char c = this->fptr_right.get();
    this->fptr_right.seekg(this->rightptr_pos);
    return c;
}

void Parser::update(std::string line) {
    while (TOKEN.is_whitespace(line.back())) line.pop_back();
    if (line.length() > 1) {
        this->fptr_output<<'\t'<<line<<';'<<'\n';
    } 
}

std::string Parser::get_word(char c) {
    std::string word = "";

    char lchar = this->read_left_ptr();
    char rchar = this->read_right_ptr();

    if (c == 'f') {
        if ((this->read_left_ptr() == ' ' && this->read_right_ptr() == ' ') || (this->read_right_ptr() == '\n')) {
            this->move_left_ptr();
            this->move_right_ptr();
        }

        while (true) {
            word.push_back(this->read_right_ptr());
            this->move_right_ptr();

            if (this->read_right_ptr() == ' ' ) break;
            if (this->read_right_ptr() == '\n' ) break;
            if (this->read_right_ptr() == '\t' ) break;
            if (this->read_right_ptr() == EOF ) break;
        }

        this->move_left_ptr(true);

        return word;
    }

    return word;        
}

bool Parser::parse(std::string infile) {
    bool has_error = false;
    int line = 1;

    bool init = false;

    // setting up the file pointers
    this->fptr_left.open(infile);
    this->fptr_right.open(infile);

    std::string lexeme;         // stores the token it reads
    std::string stmt;           // stores the parsed statement

    while (true) {
        lexeme = this->get_word('f');
        
        if (lexeme.at(0) == '\n') lexeme = "LET";
        
        if (lexeme == "LET") {
            std::string varname;
            if (ST.lookup(ST.get_identifier((lexeme = this->get_word('f'))))) varname = lexeme;

            if ((lexeme = this->get_word('f')) == "EQ") {
                lexeme = this->get_word('f');

                bool is_legal = true;
                for (int i=0; i<lexeme.length(); i++) {
                    if (!TOKEN.is_digit(lexeme.at(i))) {
                        ERROR.set_error("406", 6);
                        has_error = true;
                        is_legal = false;
                        break;
                    }
                }

                if (is_legal) stmt = "float "+varname+" = "+lexeme;
            } else {
                stmt = "float "+varname+" = 0";
            }

            this->update(stmt);
            stmt.clear();
        }

        if (ST.lookup(ST.get_identifier(lexeme))) {
            stmt = lexeme;

            if (this->get_word('f') == "EQ") {
                stmt = stmt + " = ";

                lexeme = this->get_word('f');
                if (ST.lookup(ST.get_identifier(lexeme))) {
                    stmt = stmt + lexeme;
                } else if (true) {
                    bool is_legal = true;
                    for (int i=0; i<lexeme.length(); i++) {
                        if (!TOKEN.is_digit(lexeme.at(i))) {
                            ERROR.set_error("406", 6);
                            has_error = true;
                            is_legal = false;
                            break;
                        }
                    }

                    if (is_legal) stmt = stmt + lexeme;
                }

            lexeme = this->get_word('f');
            if (lexeme == "ADD" || lexeme == "SUB" || lexeme == "MUL" || lexeme == "DIV") {
                if (lexeme == "ADD") {
                    stmt = stmt + "+";
                } else if (lexeme == "SUB") {
                    stmt = stmt + "-";
                } else if (lexeme == "MUL") {
                    stmt = stmt + "*";
                } else if (lexeme == "DIV") {
                    stmt = stmt + "/";
                } else {
                    ERROR.set_error("406", 10);
                }

                lexeme = this->get_word('f');
                if (ST.lookup(ST.get_identifier(lexeme))) {
                    stmt = stmt + lexeme;
                } else if (true) {
                    bool is_legal = true;
                    for (int i=0; i<lexeme.length(); i++) {
                        if (!TOKEN.is_digit(lexeme.at(i))) {
                            ERROR.set_error("406", 6);
                            has_error = true;
                            is_legal = false;
                            break;
                        }
                    }

                    if (is_legal) stmt = stmt + lexeme;
                }
                
                }
            }

        }
if (lexeme == "INPUT") {
                stmt = "cin>>";
                
                lexeme = this->get_word('f');
                if (ST.lookup(ST.get_identifier(lexeme))) {
                    stmt = stmt + lexeme;
                } else {
                    ERROR.set_error("406", 225);
                }
            }

        if (lexeme == "OUTPUT") {
                stmt = "cout<<";
                
                lexeme = this->get_word('f');
                if (ST.lookup(ST.get_identifier(lexeme))) {
                    if (ST.get_datatype(lexeme) == "string") {
                        stmt = stmt + ST.get_identifier(lexeme);
                    } else {

                    stmt = stmt + lexeme;}
                } else if (true) {
                    bool is_legal = true;
                    for (int i=0; i<lexeme.length(); i++) {
                        if (!TOKEN.is_digit(lexeme.at(i))) {
                            ERROR.set_error("406", 6);
                            has_error = true;
                            is_legal = false;
                            break;
                        }
                    }

                    if (is_legal) stmt = stmt + lexeme;
                } else {
                    ERROR.set_error("406", 225);
                }
            }

        this->update(stmt);
        if (this->read_right_ptr() == EOF) break;
        lexeme.clear();
        stmt.clear();
    }
    if (has_error) return false; else return true;
}

Parser PARSER;