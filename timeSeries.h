#pragma once

#include <cmath>
#include <iostream>
#include <ostream>
#include <regex>
#include <vector>

class TimeSeries {
 public:
  int t;
  int t_2;

  std::vector<double> timeSeries;
  std::vector<int> x;
  void calc(std::string str);
  void string_to_vector(std::string str);
  void set_size();
  void set_x();

};
