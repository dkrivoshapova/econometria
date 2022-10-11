#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <ostream>
#include <regex>
#include <vector>

#include "matrix.h"
#include "timeSeries.h"

class Trend {
 public:
  std::vector<double> coefficients;
  TimeSeries *timeSeries;
  void setCoefficients(S21Matrix coefficients);
};

class PolynomialTrend : public Trend {
 private:
  int power;

 public:
  PolynomialTrend(TimeSeries *series, int pow) : power(pow) {
    this->timeSeries = series;
  }
  ~PolynomialTrend() = default;

  void parameterEstimation();
  S21Matrix getX();
  S21Matrix getY();
};

class ExponentialTrend : public Trend {
 private:
  int power;

 public:
  ExponentialTrend(TimeSeries *series, int pow) : power(pow) {
    this->timeSeries = series;
  }
  ~ExponentialTrend() = default;

  void parameterEstimation();
  S21Matrix getX();
  S21Matrix getY();
};
