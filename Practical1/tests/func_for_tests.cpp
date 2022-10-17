#include "func_for_tests.h"


void prepare(std::ofstream& out, std::ofstream& err, std::ifstream& in,  const std::string& testString) {
    std::ofstream fout("tempin.txt");
    fout << testString;
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

bool makeTest(const std::string& testString, bool answerType) {
    std::ofstream out;
    std::ofstream err;
    std::ifstream in;
    prepare(out, err, in, testString);
    Interface interface(in, out, err);
    interface.start();
    close(out, err, in);
    std::ifstream fin("tempout.txt");
    std::string answer;
    fin >> answer;
    fin.close();
    clear();
    if (answerType) {
        return answer == "YES";
    } else {
        return answer == "NO";
    }
}

int makeErrorTest(const std::string& testString) {
    std::ofstream out;
    std::ofstream err;
    std::ifstream in;
    prepare(out, err, in, testString);
    Interface interface(in, out, err);
    int answer = interface.start();
    close(out, err, in);
    clear();
    return answer;
}