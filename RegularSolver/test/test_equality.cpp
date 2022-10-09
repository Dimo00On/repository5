#include <gtest/gtest.h>
#include "Interface.h"

class InterfaceMock : Interface {
public:
    bool equality(const std::string& str1, const std::string& str2,
                  const std::unordered_set<char>& alphabet, int AlphabetSize) {
        return isSameRegularExpressions(str1, str2, alphabet, AlphabetSize);
    }
};

TEST(test_equality, test1) {
    int alphabetSize = 1;
    std::unordered_set<char> alphabet = {'a'};
    std::string str1 = "a";
    std::string str2 = "aa";
    InterfaceMock interface;
    auto answer = interface.equality(str1, str2, alphabet, alphabetSize);
    ASSERT_FALSE(answer);
}

TEST(test_equality, test2) {
    int alphabetSize = 2;
    std::unordered_set<char> alphabet = {'a', 'b'};
    std::string str1 = "(ab+ba+bb+aa)*(1+a+b)";
    std::string str2 = "(a+b)*";
    InterfaceMock interface;
    auto answer = interface.equality(str1, str2, alphabet, alphabetSize);
    ASSERT_TRUE(answer);
}

TEST(test_equality, test3) {
    int alphabetSize = 2;
    std::unordered_set<char> alphabet = {'a', 'b'};
    std::string str1 = "b(a+1)+a(1+b)";
    std::string str2 = "a+b+ba+ab";
    InterfaceMock interface;
    auto answer = interface.equality(str1, str2, alphabet, alphabetSize);
    ASSERT_TRUE(answer);
}

TEST(test_equality, test4) {
    int alphabetSize = 3;
    std::unordered_set<char> alphabet = {'a', 'b', 'c'};
    std::string str1 = "(a+b)*(b+c)*";
    std::string str2 = "(a+b+c)*(ab+bc+ca)";
    InterfaceMock interface;
    auto answer = interface.equality(str1, str2, alphabet, alphabetSize);
    ASSERT_FALSE(answer);
}