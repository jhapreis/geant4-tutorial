#include "aux.hh"

string::string(std::string s){

    str = new std::string(s);
}

std::string* string::str_toupper() {

    std::transform(str->begin(), str->end(), str->begin(),
                [](unsigned char c){ return std::toupper(c); } // correct
                );
    return str;
}
