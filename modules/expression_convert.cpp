/*
This part of the program is responsible for the conversion of Prefix expression to full parthensized infix notation.
*/

#include <string>
#include <stack>


// function `is_valid_operator()` is used to determine whether the given character is an valid operator or not
bool is_valid_operator (char op) {
    if (op == '+' || op == '-' || op == '*' || op == '/') return true;
    
    return false;
}

bool is_valid_token (char op) {
    if (int(op)>=65 && int(op)<=90) return true;
    if  (is_valid_operator(op)) return true;

    return false;
}
// function to_infix() is used to convert Prefix expression to Infix Expression (2 operands = 1 Operator)
std::string to_infix(std::string input) {
    std::string output; 
    
    std::stack<std::string> opstack;     // opstack temporary holds the characters in the input
    int head = input.length() - 1;  // head is responsible to point to the current position of the input and is initialized to the last index of string

    // looping from right to left of input 
    for (head; head>=0; head--) {
        // if the current character is a non-terminal
        if (is_valid_token(input.at(head)) && !is_valid_operator(input.at(head))) {
            opstack.push(std::string(1, input.at(head)));
            continue;
        }

        // if the current character is a operator
        if (is_valid_operator(input.at(head))) {
            std::string str1 = opstack.top();    opstack.pop();
            std::string str2 = opstack.top();    opstack.pop();

            opstack.push("("+str1+input.at(head)+str2+")");
        }
    }
    
    return opstack.top();
}

// function to_full_prefix() is used to convert Prefix expression into form 2 Operands = 1 Operator
// Example; (+ A B C D) becomes +++ A B C D