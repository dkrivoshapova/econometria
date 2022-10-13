#pragma once

#include <iostream>
#include <map>
#include <vector>

constexpr char kComma = ',';
constexpr int kRows = 0;

class Parser {
 public:
  void parseFile(std::string filename);
  std::vector<double>& getY();
  std::vector<double> getX();

 private:
  std::vector<double> y_;
};

class Fisher {
 public:
  void parseFile(std::string filename);
  double getQuantile(int row, int col);

 private:
  std::map<double, std::vector<double>> fisherTable_;
};
