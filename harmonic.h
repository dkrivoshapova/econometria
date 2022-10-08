#pragma once

#include <cmath>
#include <iostream>
#include <ostream>
#include <regex>
#include <vector>
#include "timeSeries.h"

class Harmonic {
 public:
  double Alpha;
  double Betta;
  double R;
  double W;
  double O;
  TimeSeries *timeSeries;
  Harmonic(TimeSeries *series):timeSeries(series) {}

  double calcAlpha(int j);
  double calcBetta(int j);
  void calcParams(int j);

  std::vector<double> getCoordinates();
};
