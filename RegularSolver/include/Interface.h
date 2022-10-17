#include <iostream>
#include "basic_classes.h"
#include "Builder.h"
#include "Parser.h"
#include "RepresenterNKA.h"
#include "BuilderPDKA.h"
#include "RepresenterPDKA.h"
#include "Collector.h"
#include "Minimizer.h"
#include "GraphChecker.h"
#pragma once

class Interface {
protected:
    RegularExpression findComplement(const std::string& str,
                                     const std::unordered_set<char>& alphabet, int AlphabetSize);
    bool isSameRegularExpressions(const std::string& str1, const std::string& str2,
                                  const std::unordered_set<char>& alphabet, int AlphabetSize);
public:
    int start(std::istream& in, std::ostream& out, std::ostream& err);
};

