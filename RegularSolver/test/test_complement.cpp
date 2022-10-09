#include <gtest/gtest.h>
#include "Interface.h"

class InterfaceMock : Interface {
public:
    RegularExpression complement(const std::string& str,
                                 const std::unordered_set<char>& alphabet, int AlphabetSize) {
        return findComplement(str, alphabet, AlphabetSize);
    }
};

TEST(test_complement, test1) {
    int alphabetSize = 2;
    std::unordered_set<char> alphabet = {'a', 'b'};
    std::string str = "0";
    InterfaceMock interface;
    auto answer = interface.complement(str, alphabet, alphabetSize);
    ASSERT_TRUE( answer == "(a+b)*" || answer == "(b+a)*");
}

TEST(test_complement, test2) {
    int alphabetSize = 2;
    std::unordered_set<char> alphabet = {'a', 'b'};
    std::string str = "(a+b)*";
    InterfaceMock interface;
    auto answer = interface.complement(str, alphabet, alphabetSize);
    ASSERT_TRUE( answer == "0");
}

TEST(test_complement, test3) {
    int alphabetSize = 2;
    std::unordered_set<char> alphabet = {'a', 'b'};
    std::string str = "(b+a)*";
    InterfaceMock interface;
    auto answer = interface.complement(str, alphabet, alphabetSize);
    ASSERT_TRUE( answer == "0");
}

TEST(test_complement, test4) {
    int alphabetSize = 1;
    std::unordered_set<char> alphabet = {'a'};
    std::string str = "a";
    InterfaceMock interface;
    auto answer = interface.complement(str, alphabet, alphabetSize);
    ASSERT_TRUE( answer == "1+aaa*" || answer == "1+aa*a" || answer == "1+a*aa" ||
                         answer == "aaa*+1" || answer == "aa*a+1" || answer == "a*aa+1");
}

TEST(test_complement, test5) {
    int alphabetSize = 1;
    std::unordered_set<char> alphabet = {'a'};
    std::string str = "aa*a+1";
    InterfaceMock interface;
    auto answer = interface.complement(str, alphabet, alphabetSize);
    ASSERT_TRUE( answer == "a");
}