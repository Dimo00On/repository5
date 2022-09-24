/*#include "Cleaner.h"
#include <queue>

void clear(std::queue<char> &q ) {
    std::queue<char> empty;
    std::swap( q, empty );
}

std::string Cleaner::clean(const std::string& str) const {
    //хочу s+w(w)*s -> (w)*s; (s+w(w)*s) -> (w)*s
    std::queue<char> first;
    std::queue<char> second;

    for (int firstLength = 1; firstLength < 6; ++firstLength) {
        for (int secondLength = 1; secondLength < 6; ++secondLength) {
            for (int i = 0; i < str.length(); ++i) {
                if (first.size() < firstLength) {
                    if (str[i] == '+' || str[i] == '(' || str[i] == '*' || str[i] == ')') {
                        clear(first);
                        continue;
                    }
                    first.push(str[i]);
                    continue;
                }
                if (str[i] != '+' && str[i] != '(' && str[i] != '*' && str[i] != ')') {
                    first.pop();
                    first.push(str[i]);
                    continue;
                }
                bool startWithBracket = false; // s+(w)(w)*s
                bool successfulSecondWord = true;
                bool startWithBracketSecond = false;
                bool successfulSecondWordSecond = true;
                bool startWithBracketFirst = false;
                bool successfulFirstWord = true;
                bool starFound = false;
                std::queue<char> copyFirst;
                std::queue<char> copySecond;
                for (int k = 1; k < str.length() - i; ++k) {
                    if (second.size() < secondLength) {
                        if (str[i + k] == '+' || str[i + k] == '*' || str[i + k] == ')') {
                            break;
                        }
                        if (str[i + k] == '(') {
                            startWithBracket = true;
                            successfulSecondWord = false;
                            continue;
                        }
                        second.push(str[i + k]);
                    }
                    if (startWithBracket && !successfulSecondWord) {
                        if (str[i + k] != ')') {
                            break;
                        }
                        successfulSecondWord = true;
                        continue;
                    }
                    if (copySecond.size() < secondLength) {
                        if (str[i + k] == '+' || str[i + k] == '*' || str[i + k] == ')') {
                            break;
                        }
                        if (str[i + k] == '(') {
                            startWithBracketSecond = true;
                            successfulSecondWordSecond = false;
                            continue;
                        }
                        copySecond.push(str[i + k]);
                    }
                    if (startWithBracketSecond && !successfulSecondWordSecond) {
                        if (str[i + k] != ')') {
                            break;
                        }
                        successfulSecondWordSecond = true;
                        continue;
                    }
                    if (!starFound) {
                        if (str[i + k] != '*') {
                            break;
                        }
                        starFound = true;
                        continue;
                    }
                    if (copyFirst.size() < firstLength) {
                        if (str[i + k] == '+' || str[i + k] == '*' || str[i + k] == ')') {
                            break;
                        }
                        if (str[i + k] == '(') {
                            startWithBracketFirst = true;
                            successfulFirstWord = false;
                            continue;
                        }
                        copyFirst.push(str[i + k]);
                    }
                    if (startWithBracketFirst && !successfulFirstWord) {
                        if (str[i + k] != ')') {
                            break;
                        }
                        successfulFirstWord = true;
                        continue;
                    }
                    if (str[i + k] == '+' || str[i + k] == ')') {
                        if (first == copyFirst && second == copySecond) {
                            str = str.substr(0, i - firstLength)








                        }
                    }
                }
            }
        }
    }
}*/
//может лучше просто grepом? в bash scripte написать