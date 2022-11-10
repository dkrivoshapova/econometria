#include "fisher.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::string> strip(const std::string& str, char pattern) {
  std::vector<std::string> list;
  std::istringstream iss(str);
  std::string token;
  while (std::getline(iss, token, pattern)) {
    list.push_back(token);
  }
  return list;
}

void Fisher::parseFile() {
  std::string filename = "/Users/darakrivosapova/econometria/table.csv";
  std::string line;
  std::ifstream in(filename);
  if (!in.is_open()) {
    throw std::invalid_argument("Error:" + filename + " dont exist!");
  }
  while (getline(in, line)) {
    auto list = strip(line, kComma);
    std::vector<double> value(list.size() - 1);
    int key = 0;
    for (int i = 0; i < list.size(); i++) {
      if (i == 0) {
        key = std::stoi(list[i]);
        continue;
      }
      value[i - 1] = std::stod(list[i]);
    }
    fisherTable_[key] = value;
  }
}

double Fisher::getQuantile(int row, int col) {
  int position = fisherTable_[kRows].size() - 1;
  for (int i = 0; i < fisherTable_[kRows].size(); i++) {
    if (i == fisherTable_[kRows].size() - 1) {
      break;
    }
    if (col < fisherTable_[kRows][i]) {
      position = i - 1;
      break;
    }
  }
  // std::cout << position << "\n";
  return fisherTable_[row][position];
}

void Parser::parseFile(std::string filename) {
  std::string line;
  std::ifstream in(filename);
  if (!in.is_open()) {
    throw std::invalid_argument("Error:" + filename + " dont exist!");
  }
  while (getline(in, line)) {
    y_.push_back(std::stoi(line));
  }
}

std::vector<double>& Parser::getY() { return y_; }

std::vector<double> Parser::getX() {
  std::vector<double> x;
  for (int i = 1; i <= y_.size(); i++) {
    x.push_back(i);
  }
  return x;
}
