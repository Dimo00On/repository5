#include "Interface.h"

RegularExpression Interface::findComplement(const std::string& str,
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

bool Interface::isSameRegularExpressions(const std::string& str1, const std::string& str2,
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

int Interface::start(std::istream& in, std::ostream& out, std::ostream& err) {
    out << "Write 1 to find complement,\nWrite 2 to check are regular expressions the same.\n";
    int value = 0;
    in >> value;
    if (value != 1 && value != 2) {
        err << "Wrong command";
        return 1;
    }
    out << "Write alphabet size:\n";
    int AlphabetSize;
    in >> AlphabetSize;
    out << "Write all letters from alphabet without spaces:\n";
    std::unordered_set<char> alphabet;
    for (int i = 0; i < AlphabetSize; ++i) {
        char letter;
        in >> letter;
        alphabet.insert(letter);
    }
    if (value == 1) {
        out << "Write regular expression without spaces:\n";
        std::string str;
        in >> str;
        out << "Answer: ";
        out << findComplement(str, alphabet, AlphabetSize);
    }
    if (value == 2) {
        out << "Write first regular expression without spaces:\n";
        std::string str1;
        in >> str1;
        out << "Write second regular expression without spaces:\n";
        std::string str2;
        in >> str2;
        if (isSameRegularExpressions(str1, str2, alphabet, AlphabetSize)) {
            out << "Regular expressions are the same";
        } else {
            out << "Regular expressions are NOT the same";
        }
    }
    return 0;
}