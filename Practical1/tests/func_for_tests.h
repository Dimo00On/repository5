#include <gtest/gtest.h>
#include "Interface.h"
#include <fstream>
#pragma once

void prepare(std::ofstream& out, std::ofstream& err, std::ifstream& in,  const std::string& testString);
void close(std::ofstream& out, std::ofstream& err, std::ifstream& in);
void clear();
bool makeTest(const std::string& testString, bool answerType);
int makeErrorTest(const std::string& testString);