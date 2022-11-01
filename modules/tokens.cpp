#include <iostream>
#include <string>

class Tokens {
    public:
        bool is_digit (char lexeme) {
            if (lexeme == '0' || lexeme == '1' || lexeme == '2' || lexeme == '3' || lexeme == '4' || lexeme == '5' || lexeme == '6' || lexeme == '7' || lexeme == '8' || lexeme == '9') return true;

            return false;
        }

        bool is_alphabet (char lexeme) {
            if (lexeme == 'a' || lexeme == 'b' || lexeme == 'c' || lexeme == 'd' || lexeme == 'e' || lexeme == 'f' || lexeme == 'g' || lexeme == 'h' || lexeme == 'i' || lexeme == 'j' || lexeme == 'k' || lexeme == 'l' || lexeme == 'm' || lexeme == 'n' || lexeme == 'o' || lexeme == 'p' || lexeme == 'q' || lexeme == 'r' || lexeme == 's' || lexeme == 't' || lexeme == 'u' || lexeme == 'v' || lexeme == 'w' || lexeme == 'x' || lexeme == 'y' || lexeme == 'z') return true;
            if (lexeme == 'A' || lexeme == 'B' || lexeme == 'C' || lexeme == 'D' || lexeme == 'E' || lexeme == 'F' || lexeme == 'G' || lexeme == 'H' || lexeme == 'I' || lexeme == 'J' || lexeme == 'K' || lexeme == 'L' || lexeme == 'M' || lexeme == 'N' || lexeme == 'O' || lexeme == 'P' || lexeme == 'Q' || lexeme == 'R' || lexeme == 'S' || lexeme == 'T' || lexeme == 'U' || lexeme == 'V' || lexeme == 'W' || lexeme == 'X' || lexeme == 'Y' || lexeme == 'Z') return true;
            
            return false;
        }
        
        bool is_operator (char lexeme) {
            if (lexeme == '+' ||  lexeme == '-' || lexeme == '*' || lexeme == '/' || lexeme == '%') return true;
            if (lexeme == '=') return true;
            if (lexeme == '>' || lexeme == '<' || lexeme == '=') return true;

            return false;
        }

        bool is_punctuator (char lexeme) {
            if (lexeme == ',' || lexeme == '(' || lexeme == ')' || lexeme == '[' || lexeme == ']') return true;

            return false;
        }

        bool is_whitespace (char lexeme) {
            if (lexeme == ' ' || lexeme == '\t' || lexeme == '\r') return true;

            return false;
        }
        
        bool is_special_char (char lexeme) {
            if  (lexeme == '#') return true;

            return false;
        }

        bool is_character_set (char lexeme) {
            if (lexeme == this->is_digit(lexeme)) return true;
            if (lexeme == this->is_alphabet(lexeme)) return true;
            if (lexeme == this->is_operator(lexeme)) return true;
            if (lexeme == this->is_punctuator(lexeme)) return true;
            if (lexeme == this->is_whitespace(lexeme)) return true;
            if (lexeme == this->is_special_char(lexeme)) return true;

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
                if (!(
                    lexemes.at(i) == '_' || this->is_digit(lexemes.at(i)) || this->is_alphabet(lexemes.at(i))
                    )) return false; 
            }

            // if is a keyword
            if (this->is_keyword(lexemes)) return false;

            return true;
        }

        /* The keywords in Wiz are;
        if, else, then, and, or, not, end, let, print
        */
        bool is_keyword(std::string lexemes) {
            if (lexemes == "if" || lexemes == "else" || lexemes == "then" || lexemes == "end" || lexemes == "and" || lexemes == "or" || lexemes == "not" || lexemes == "let" || lexemes == "print") {
                return true;
            }

            return false;
        }
};

Tokens TOKEN;