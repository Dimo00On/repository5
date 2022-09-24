#include "RegularExpression.h"
#include <utility>

RegularExpression::RegularExpression() = default;

RegularExpression::RegularExpression(std::string newWord) : word(std::move(newWord)) {
    if (word == "+") {
        isSum = true;
    }
    newWord = "";
}

RegularExpression::RegularExpression(const char* word) : RegularExpression(std::string(word)) {}

RegularExpression& RegularExpression::operator+=(const RegularExpression& other) {
    word += other.word;
    isSum |= other.isSum;
    return *this;
}

RegularExpression& RegularExpression::operator=(const RegularExpression& other) = default;

bool RegularExpression::operator==(const RegularExpression& other) const {
    return word == other.word;
}

bool RegularExpression::operator!=(const RegularExpression& other) const {
    return word != other.word;
}

int RegularExpression::length() const {
    return static_cast<int>(word.length());
}

std::ostream& operator<<(std::ostream& out, const RegularExpression& expr) {
    out << expr.word;
    return out;
}