#include <iostream>
#include <string>
#include <unordered_map>

class ErrorLog  {
    std::unordered_map<int, std::string> emap_code;
    std::unordered_map<int, int> emap_line;

    int current_error_id;       // stores current error id

    public:
        ErrorLog () { current_error_id = 0; }

        void set_error(std::string, int);
        void show_errors();
};

void ErrorLog::set_error(std::string err_type, int line) {
    this->emap_code.insert(std::make_pair(this->current_error_id, err_type));
    this->emap_line.insert(std::make_pair(this->current_error_id, line));
    this->current_error_id++;
}

void ErrorLog::show_errors () {
    for (int i=0; i<this->current_error_id; i++) {
        std::string err = this->emap_code.at(i);
        std::cout<<std::endl<<"On line number "<<this->emap_line.at(i)<<", ";

        if (err == "404") std::cout<<"the file was not found."<<std::endl; 
        if (err == "403") std::cout<<"incompatible file type."<<std::endl; 
        if (err == "405") std::cout<<"illegal character encountered."<<std::endl; 
        if (err == "406") std::cout<<"illegal value."<<std::endl; 
    }
}

ErrorLog ERROR;
