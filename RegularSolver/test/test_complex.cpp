#include <gtest/gtest.h>
#include "Interface.h"

class InterfaceMock : Interface {
public:
    bool equality(const std::string& str1, const std::string& str2,
                  const std::unordered_set<char>& alphabet, int AlphabetSize) {
        return isSameRegularExpressions(str1, str2, alphabet, AlphabetSize);
    }
    RegularExpression complement(const std::string& str,
                                 const std::unordered_set<char>& alphabet, int AlphabetSize) {
        return findComplement(str, alphabet, AlphabetSize);
    }
};

TEST(test_complex, test1) {
    int alphabetSize = 3;
    std::unordered_set<char> alphabet = {'a', 'b', 'c'};
    InterfaceMock interface;
    std::string str1 = "(a+b)*cc(b+c)*+bb(a+c)*";
    std::string str2 = static_cast<std::string>(interface.complement(str1, alphabet, alphabetSize));
    auto answer = interface.equality(str1, str2, alphabet, alphabetSize);
    ASSERT_FALSE(answer);
}

TEST(test_complex, test2) {
    int alphabetSize = 3;
    std::unordered_set<char> alphabet = {'a', 'b', 'c'};
    InterfaceMock interface;
    std::string str1 = "(a+b)*cc(b+c)*+bb(a+c)*";
    std::string str2 = static_cast<std::string>(interface.complement(str1, alphabet, alphabetSize));
    std::string str3 = static_cast<std::string>(interface.complement(str2, alphabet, alphabetSize));
    auto answer = interface.equality(str1, str3, alphabet, alphabetSize);
    ASSERT_TRUE(answer);
}