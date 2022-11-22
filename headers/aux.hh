#ifndef AUX_STRING_HH
#define AUX_STRING_HH


#include <string>
#include <algorithm>


class string : public std::string{

public:
    string(std::string s);

    std::string* str_toupper();

private:

    std::string* str;
};

#endif
