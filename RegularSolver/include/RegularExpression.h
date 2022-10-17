#include <string>
#pragma once

class RegularExpression {
public:
    std::string word;
    bool isSum = false;

    RegularExpression();
    RegularExpression(std::string word);
    RegularExpression(const char* word);
    explicit operator std::string() const;

    RegularExpression& operator+=(const RegularExpression& other);
    RegularExpression& operator=(const RegularExpression& other);
    bool operator==(const RegularExpression& other) const;
    bool operator!=(const RegularExpression& other) const;
    int length() const;
};

std::ostream& operator<<(std::ostream& out, const RegularExpression& expr);