#include <iostream>
#include "Interface.h"

int main() {
    Interface interface(std::cin, std::cout, std::cerr);
    return interface.start();
}
