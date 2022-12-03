#include <iostream>
#pragma once

const int kNonTerminalAlphabetStart = 64;
const int kTerminalAlphabetStart = 96;

class Interface {
public:
  Interface(std::istream& in, std::ostream& out, std::ostream& err);
  int start();

protected:
  std::istream& in;
  std::ostream& out;
  std::ostream& err;
};
