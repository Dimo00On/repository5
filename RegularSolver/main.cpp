#include <iostream>
#include "basic_classes.h"
#include "Builder.h"
#include "Parser.h"
#include "RepresenterNKA.h"
#include "BuilderPDKA.h"
#include "RepresenterPDKA.h"
#include "Collector.h"

int main() {
    int AlphabetSize;
    std::cin >> AlphabetSize;
    std::unordered_set<char> alphabet;
    for (int i = 0; i < AlphabetSize; ++i) {
        char letter;
        std::cin >> letter;
        alphabet.insert(letter);
    }
    std::string str;
    std::cin >> str;
    Parser parser;
    Builder builder(alphabet);
    str = parser.infixToPostfix(str);
    builder.createNKA(str);
    auto representer = new RepresenterNKA(builder.result);
    representer->representNKA();
    BuilderPDKA dkaBuilder(&builder, representer);
    dkaBuilder.build();
    delete representer;
    builder.inverseTerminals();
    auto pdkaRepresenter = new RepresenterPDKA(builder.result);
    pdkaRepresenter->representPDKA();
    Collector collector(pdkaRepresenter);
    std::cout << collector.collect();
    delete pdkaRepresenter;
    return 0;
}
