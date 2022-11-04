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
  double tss;
  std::vector<double> timeSeries;
  std::vector<double> x;

  void initTimeSeries(std::vector<double> y, std::vector<double> x);
  void set_size();
  void set_tss();
  double calcAverage();
};
