#include "Interface.h"
#include <set>
#include <vector>
#include <stack>

Interface::Interface(std::istream& in, std::ostream& out, std::ostream& err) :
    in(in), out(out), err(err) {}

bool Interface::checkSymbols(std::string& str) {
    bool ok = true;
    std::set<char> symbols = {'a', 'b', 'c', '1', '+', '.', '*'};
    for (int i = 0; i < str.length(); ++i) {
        if (!symbols.count(str[i])) {
            err << "Read error: unknown symbol " << str[i] << " at position " << i << ".\n";
            ok = false;
        }
    }
    return ok;
}

bool Interface::checkPolishNotation(std::string& str) {
    int sum = 0;
    std::set<char> operations = {'+', '.', '*'};
    for (int i = 0; i < str.length(); ++i) {
        if (operations.count(str[i])) {
            if (str[i] == '*') {
                if (sum <= 0) {
                    err << "Read error: string is not in reverse polish notation.\n";
                    err << "Not enough letters for operation \'";
                    err << str[i] << "\' at position " << i << ".\n";
                    return false;
                }
            } else {
                --sum;
            }
        } else {
            ++sum;
        }
        if (sum <= 0) {
            err << "Read error: string is not in reverse polish notation.\n";
            err << "Not enough letters for operation \'";
            err << str[i] << "\' at position " << i << ".\n";
            return false;
        }
    }
    if (sum > 1) {
        err << "Read error: string is not in reverse polish notation.\nNot enough operations for letters.\n";
        return false;
    }
    return true;
}

bool Interface::checkLetter(char letter) {
    std::set<char> symbols = {'a', 'b', 'c'};
    return symbols.count(letter);
}

bool Interface::checkLength(int length) {
    if (length < 0) {
        err << "Read error: given length is less than 0.\n";
        return false;
    }
    return true;
}

int Interface::start() {
    std::string str;
    in >> str;
    if (!checkSymbols(str)) {
        return 1;
    }
    if (!checkPolishNotation(str)) {
        return 2;
    }
    char letter;
    in >> letter;
    int length;
    in >> length;
    if (!checkLength(length)) {
        return 3;
    }
    if (length == 0) {
        out << "YES\n";
        return 0;
    } else {
        if (!checkLetter(letter)) {
            out << "NO\n";
            return 0;
        }
    }
    std::vector<int> maxPrefix(str.length(), 0);
    std::vector<int> maxSuffix(str.length(), 0);
    std::vector<int> maxWord(str.length(), 0);
    std::vector<int> maxSubstring(str.length(), 0);
    std::set<char> alphabet = {'a', 'b', 'c', '1'};
    std::stack<int> indexes;
    for (int i = 0; i < str.length(); ++i) {
        if (alphabet.count(str[i])) {
            if (str[i] == letter) {
                maxPrefix[i] = 1;
                maxSuffix[i] = 1;
                maxWord[i] = 1;
                maxSubstring[i] = 1;
            } else {
                if (str[i] == '1') {
                    maxPrefix[i] = 0;
                    maxSuffix[i] = 0;
                    maxWord[i] = 0;
                    maxSubstring[i] = 0;
                } else {
                    maxPrefix[i] = 0;
                    maxSuffix[i] = 0;
                    maxWord[i] = -1;
                    maxSubstring[i] = 0;
                }
            }
        } else {
            int first = indexes.top();
            indexes.pop();
            if (str[i] == '*') {
                if (maxWord[first] > 0) {
                    maxPrefix[i] = kInfinity;
                    maxSuffix[i] = kInfinity;
                    maxWord[i] = kInfinity;
                    maxSubstring[i] = kInfinity;
                } else {
                    maxPrefix[i] = maxPrefix[first];
                    maxSuffix[i] = maxSuffix[first];
                    maxWord[i] = 0;
                    maxSubstring[i] = maxSubstring[first];
                }
            } else {
                int second = indexes.top();
                indexes.pop();
                if (str[i] == '+') {
                    maxPrefix[i] = std::max(maxPrefix[first], maxPrefix[second]);
                    maxSuffix[i] = std::max(maxSuffix[first], maxSuffix[second]);
                    maxWord[i] = std::max(maxWord[first], maxWord[second]);
                    maxSubstring[i] = std::max(maxSubstring[first], maxSubstring[second]);
                }
                if (str[i] == '.') {
                    //stack: second, first <-top
                    maxPrefix[i] = maxPrefix[second];
                    if (maxWord[second] >= 0) {
                        maxPrefix[i] = std::max(maxPrefix[i], maxWord[second] + maxPrefix[first]);
                    }
                    maxSuffix[i] = maxSuffix[first];
                    if (maxWord[first] >= 0) {
                        maxSuffix[i] = std::max(maxSuffix[i], maxSuffix[second] + maxWord[first]);
                    }
                    if (maxWord[first] >= 0 && maxWord[second] >= 0) {
                        maxWord[i] = maxWord[first] + maxWord[second];
                    } else {
                        //хотя бы в одном из языков нет слова только из этих букв
                        maxWord[i] = -1;
                    }
                    maxSubstring[i] = std::max(std::max(maxSubstring[second], maxSubstring[first]),
                                               maxSuffix[second] + maxPrefix[first]);
                }
            }
        }
        indexes.push(i);
    }
    if (maxSubstring[str.length() - 1] >= length) {
        out << "YES\n";
    } else {
        out << "NO\n";
    }
    return 0;
}