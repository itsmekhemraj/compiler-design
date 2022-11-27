#include <iostream>
#include <string>
#include <unordered_map>

class Tokens {
    std::unordered_map<std::string, std::string> index;
    public:
        Tokens () {
            index.insert(std::make_pair("if", "IF"));
            index.insert(std::make_pair("else", "ELSE"));
            index.insert(std::make_pair("then", "THEN"));
            index.insert(std::make_pair("end", "END"));
            index.insert(std::make_pair("and", "AND"));
            index.insert(std::make_pair("or", "OR"));
            index.insert(std::make_pair("not", "NOT"));
            index.insert(std::make_pair("let", "LET"));
            index.insert(std::make_pair("input", "INPUT"));
            index.insert(std::make_pair("output", "OUTPUT"));

            index.insert(std::make_pair(">", "GT"));
            index.insert(std::make_pair("<", "LT"));
            index.insert(std::make_pair(">=", "GE"));
            index.insert(std::make_pair("<=", "LE"));
            index.insert(std::make_pair("=", "EQ"));
            index.insert(std::make_pair("!=", "NE"));

            index.insert(std::make_pair("+", "ADD"));
            index.insert(std::make_pair("-", "SUB"));
            index.insert(std::make_pair("/", "DIV"));
            index.insert(std::make_pair("*", "MUL"));
            index.insert(std::make_pair("%", "MOD"));
        }

        bool is_digit (char lexeme) {
            if (lexeme == '0' || lexeme == '1' || lexeme == '2' || lexeme == '3' || lexeme == '4' || lexeme == '5' || lexeme == '6' || lexeme == '7' || lexeme == '8' || lexeme == '9') return true;

            return false;
        }

        bool is_alphabet (char lexeme) {
            if (lexeme == 'a' || lexeme == 'b' || lexeme == 'c' || lexeme == 'd' || lexeme == 'e' || lexeme == 'f' || lexeme == 'g' || lexeme == 'h' || lexeme == 'i' || lexeme == 'j' || lexeme == 'k' || lexeme == 'l' || lexeme == 'm' || lexeme == 'n' || lexeme == 'o' || lexeme == 'p' || lexeme == 'q' || lexeme == 'r' || lexeme == 's' || lexeme == 't' || lexeme == 'u' || lexeme == 'v' || lexeme == 'w' || lexeme == 'x' || lexeme == 'y' || lexeme == 'z') return true;
            if (lexeme == 'A' || lexeme == 'B' || lexeme == 'C' || lexeme == 'D' || lexeme == 'E' || lexeme == 'F' || lexeme == 'G' || lexeme == 'H' || lexeme == 'I' || lexeme == 'J' || lexeme == 'K' || lexeme == 'L' || lexeme == 'M' || lexeme == 'N' || lexeme == 'O' || lexeme == 'P' || lexeme == 'Q' || lexeme == 'R' || lexeme == 'S' || lexeme == 'T' || lexeme == 'U' || lexeme == 'V' || lexeme == 'W' || lexeme == 'X' || lexeme == 'Y' || lexeme == 'Z') return true;
            
            return false;
        }
        
        bool is_alphanumeric (char lexeme) {
            if (this->is_digit(lexeme) || this->is_alphabet(lexeme) || lexeme == '_') return true;
            
            return false;
        }

        bool is_operator (char lexeme) {
            // arithmetic operators here
            if (lexeme == '+' ||  lexeme == '-' || lexeme == '*' || lexeme == '/' || lexeme == '%') return true;
            // assignment operators here
            if (lexeme == '=') return true;
            // relational operator
            if (lexeme == '>' || lexeme == '<' || lexeme == '=') return true;

            return false;
        }

        bool is_punctuator (char lexeme) {
            if (lexeme == ',' || lexeme == '(' || lexeme == ')' || lexeme == '{' || lexeme == '}' || lexeme == '"' ) return true;

            return false;
        }

        bool is_whitespace (char lexeme) {
            if (lexeme == ' ' || lexeme == '\t' || lexeme == '\r' || lexeme == '\n') return true;

            return false;
        }
        
        bool is_special_char (char lexeme) {
            if  (lexeme == '#' || lexeme == '\\') return true;

            return false;
        }

        bool is_character_set (char lexeme) {
            if (this->is_digit(lexeme)) return true;
            if (this->is_alphabet(lexeme)) return true;
            if (this->is_operator(lexeme)) return true;
            if (this->is_punctuator(lexeme)) return true;
            if (this->is_whitespace(lexeme)) return true;
            if (this->is_special_char(lexeme)) return true;

            return false;
        }

        /* In Wiz, the rules for the valid identifier are as follows;
        - The identifier must start with alphabet or an underscore,
        - Should only contain alphanumeric characters,
        - It must not be a keyword
        */
        bool is_valid_identifier(std::string lexemes) {
            // if starts with number
            if (this->is_digit(lexemes.at(0))) return false;

            // if is not alphanumeric
            for (int i=0; i<lexemes.length(); i++) {
                if (!is_alphanumeric(lexemes.at(i))) return false; 
            }

            // if is a keyword
            if (this->is_keyword(lexemes)) return false;

            return true;
        }

        /* The keywords in Wiz are;
        if, else, then, and, or, not, end, let, print
        */
        bool is_keyword(std::string lexemes) {
            if (lexemes == "if" || lexemes == "else" || lexemes == "then" || lexemes == "end" || lexemes == "and" || lexemes == "or" || lexemes == "not" || lexemes == "let" || lexemes == "input" || lexemes == "output") {
                return true;
            }

            return false;
        }

        std::string get_token(std::string lexeme) {
            if (this->index.find(lexeme) == this->index.end()) {
                return lexeme;
            } else {
                return index.at(lexeme);
            }
        }
};

Tokens TOKEN;