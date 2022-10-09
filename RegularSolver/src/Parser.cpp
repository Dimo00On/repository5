#include "Parser.h"

std::string Parser::infixToPostfix(const std::string& str) {
    bool prevWasLetter = false;
    std::string ans;
    std::stack<char> letters;
    std::stack<char> operations;
    std::map<char, int> priority;
    priority['('] = 0;
    priority['+'] = 1;
    priority['.'] = 2;
    priority['*'] = 3;
    for (auto i : str) {
        if (i == ')') {
            char operation = operations.top();
            operations.pop();
            while (operation != '(') {
                ans += operation;
                operation = operations.top();
                operations.pop();
            }
            prevWasLetter = true; //(a+b)(c+d) -> должно быть умножение
            continue;
        }
        if (priority.count(i) || prevWasLetter) {
            char temp = '\n';
            if (prevWasLetter && i != '+' && i != '.' && i != '*') {
                temp =  i;
                i = '.';
            }
            if (i != '(') {
                while (!operations.empty()) {
                    char operation = operations.top();
                    if (priority[operation] <= priority[i]) {
                        break;
                    }
                    operations.pop();
                    ans += operation;
                }
            }
            operations.push(i);
            prevWasLetter = false;
            if (i == '*') {
                prevWasLetter = true; //a*b= (a*).b
            }
            if (temp != '\n') {
                if (temp == '(') {
                    operations.push(temp);
                    prevWasLetter = false;
                } else {
                    prevWasLetter = true;
                    ans += temp;
                }
            }
        } else {
            prevWasLetter = true;
            ans += i;
        }
    }
    while (!operations.empty()) {
        char operation = operations.top();
        operations.pop();
        ans += operation;
    }
    return ans;
}