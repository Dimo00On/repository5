#include <fstream>
#pragma once

const int kInfinity = 1e9;

class Interface {
public:
    Interface(std::istream& in, std::ostream& out, std::ostream& err);
    int start();
    bool checkSymbols(std::string& str);
    bool checkPolishNotation(std::string& str);
    bool checkLetter(char letter);
    bool checkLength(int length);

private:
    std::istream& in;
    std::ostream& out;
    std::ostream& err;
};
