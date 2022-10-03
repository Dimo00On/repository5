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

RegularExpression findComplement(const std::string& str,
                                 const std::unordered_set<char>& alphabet, int AlphabetSize) {
    Parser parser;
    Builder builder(alphabet);
    auto goodStr = parser.infixToPostfix(str);
    builder.createNKA(goodStr);
    auto representer = new RepresenterNKA(builder.result);
    representer->representNKA();
    BuilderPDKA dkaBuilder(&builder, representer);
    dkaBuilder.build();
    delete representer;
    builder.inverseTerminals();
    Minimizer minimizer(&builder, AlphabetSize, alphabet);
    minimizer.minimize();
    minimizer.rebuild();
    auto pdkaRepresenter = new RepresenterPDKA(builder.result);
    pdkaRepresenter->representPDKA();
    Collector collector(pdkaRepresenter);
    RegularExpression answer = collector.collect();
    delete pdkaRepresenter;
    return answer;
}

bool isSameRegularExpressions(const std::string& str1, const std::string& str2,
                              const std::unordered_set<char>& alphabet, int AlphabetSize) {
    std::string goodStr1, goodStr2;
    Parser parser;
    goodStr1 = parser.infixToPostfix(str1);
    goodStr2 = parser.infixToPostfix(str2);
    Builder builder1(alphabet);
    Builder builder2(alphabet);
    builder1.createNKA(goodStr1);
    builder2.createNKA(goodStr2);
    auto representer1 = new RepresenterNKA(builder1.result);
    auto representer2 = new RepresenterNKA(builder2.result);
    representer1->representNKA();
    representer2->representNKA();
    BuilderPDKA dkaBuilder1(&builder1, representer1);
    BuilderPDKA dkaBuilder2(&builder2, representer2);
    dkaBuilder1.build();
    dkaBuilder2.build();
    delete representer1;
    delete representer2;
    Minimizer minimizer1(&builder1, AlphabetSize, alphabet);
    Minimizer minimizer2(&builder2, AlphabetSize, alphabet);
    minimizer1.minimize();
    minimizer2.minimize();
    minimizer1.rebuild();
    minimizer2.rebuild();
    GraphChecker graphChecker;
    return graphChecker.isSameGraphs(minimizer1, minimizer2);
}

int main() {
    std::cout << "Write 1 to find complement,\nWrite 2 to check are regular expressions the same.\n";
    int value = 0;
    std::cin >> value;
    if (value != 1 && value != 2) {
        std::cerr << "Wrong command";
        return 1;
    }
    std::cout << "Write alphabet size:\n";
    int AlphabetSize;
    std::cin >> AlphabetSize;
    std::cout << "Write all letters from alphabet without spaces:\n";
    std::unordered_set<char> alphabet;
    for (int i = 0; i < AlphabetSize; ++i) {
        char letter;
        std::cin >> letter;
        alphabet.insert(letter);
    }
    if (value == 1) {
        std::cout << "Write first regular expression without spaces:\n";
        std::string str;
        std::cin >> str;
        std::cout << "Answer: ";
        std::cout << findComplement(str, alphabet, AlphabetSize);
    }
    if (value == 2) {
        std::cout << "Write first regular expression without spaces:\n";
        std::string str1;
        std::cin >> str1;
        std::cout << "Write second regular expression without spaces:\n";
        std::string str2;
        std::cin >> str2;
        if (isSameRegularExpressions(str1, str2, alphabet, AlphabetSize)) {
            std::cout << "Regular expressions are the same";
        } else {
            std::cout << "Regular expressions are NOT the same";
        }
    }

    return 0;
}
