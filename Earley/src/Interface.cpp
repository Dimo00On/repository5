#include "Interface.h"
#include "Earley.h"
#include <string>

Interface::Interface(std::istream& in, std::ostream& out, std::ostream& err) :
    in(in), out(out), err(err) {}

int Interface::start() {
  out << "Напишите количество правил: ";
  int amount;
  in >> amount;
  out << "Напишите стартовый нетерминал: ";
  std::string c_start;
  in >> c_start;
  int start;
  start = c_start[0] - kNonTerminalAlphabetStart;
  out << "Напишите правила грамматики в виде \"A BcDe\" (для правила A->BcDe, по 1 правилу на строке, пустое слово обозначается 0):\n";
  std::unordered_set<Rule*> rules;
  std::unordered_map<int, int> max_length;
  for (int i = 0; i < amount; ++i) {
    std::string c_from;
    std::string str;
    in >> c_from >> str;
    std::vector<int> to;
    if (str != "0") {
      for (auto &letter: str) {
        if (letter > kTerminalAlphabetStart) {
          to.push_back(kTerminalAlphabetStart - letter);
        } else {
          to.push_back(letter - kNonTerminalAlphabetStart);
        }
      }
    }
    auto new_rule = new Rule(c_from[0] - kNonTerminalAlphabetStart, to, 0);
    rules.insert(new_rule);
  }
  Earley earley;
  earley.Create(rules, start);
  while (true) {
    out << "Напишите 0, чтобы завершить работу, или 1, чтобы проверить, распознаётся ли слово грамматикой: ";
    int command;
    in >> command;
    if (command == 0) {
      break;
    }
    out << "Напишите слово(0 для пустого слова): ";
    std::string c_word;
    in >> c_word;
    std::vector<int> word;
    if (c_word != "0") {
      for (char letter: c_word) {
        word.push_back(kTerminalAlphabetStart - letter);
      }
    }
    if (earley.Check(word)) {
      out << "Да, распознаётся.\n";
    } else {
      out << "Нет, не распознаётся.\n";
    }
  }
  for (auto& rule : rules) {
    delete rule;
  }
  return 0;
}