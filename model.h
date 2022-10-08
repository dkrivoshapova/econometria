#pragma once

#include <cmath>
#include <iostream>
#include <ostream>
#include <regex>
#include <vector>

class Model {
 public:
  int t;
  int t_2;
  double Alpha;
  double Betta;
  double R;
  double W;
  double O;
  std::vector<double> timeSeries;
  std::vector<double> alphaCoefs;
  std::vector<double> bettaCoefs;
  void calc(std::string str);
  void string_to_vector(std::string str);

  double calcAlpha(int j);
  double calcBetta(int j);
  void calcParams(int j);

  std::vector<double> getCoordinates();
};