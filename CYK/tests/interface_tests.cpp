#include <gtest/gtest.h>
#include "Interface.h"
#include <fstream>

void prepare(std::ofstream& out, std::ofstream& err, std::ifstream& in,  const std::string& test_string) {
  std::ofstream fout("tempin.txt");
  fout << test_string;
  fout.close();
  in = std::ifstream("tempin.txt");
  out = std::ofstream("tempout.txt");
  err = std::ofstream("temperr.txt");
}

void close(std::ofstream& out, std::ofstream& err, std::ifstream& in) {
  out.close();
  err.close();
  in.close();
}

void clear() {
  remove("tempin.txt");
  remove("tempout.txt");
  remove("temperr.txt");
}

bool MakeTest(const std::string& test_string, const std::string& ans_file_name) {
  std::ofstream out;
  std::ofstream err;
  std::ifstream in;
  prepare(out, err, in, test_string);
  Interface interface(in, out, err);
  interface.start();
  for (int i = 0; i < 100; ++i) {
    out << "##########";
  }
  close(out, err, in);
  std::ifstream fin1("tempout.txt");
  std::ifstream fin2(ans_file_name);
  char x = '0';
  char y = '0';
  bool answer = true;
  while (x != '#') {
    fin1 >> x;
    fin2 >> y;
    if (x != y) {
      answer = false;
    }
  }
  if (x != y) {
    answer = false;
  }
  fin1.close();
  fin2.close();
  clear();
  return answer;
}

TEST(test_interface, test1) {
  ASSERT_TRUE(MakeTest("2\nS\nS 0\nS aSbS\n1\nab\n1\nba\n1\n0\n0", "tests/ans_interface_test1"));
}
