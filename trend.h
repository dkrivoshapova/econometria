#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <ostream>
#include <regex>
#include <vector>

#include "matrix.h"
#include "parser/fisher.h"
#include "timeSeries.h"

class Trend {
 public:
  std::vector<double> coefficients;
  TimeSeries *timeSeries;
  std::vector<double> yEstimated;
  int power;
  double r;

  Trend() {}
  Trend(TimeSeries *series, int pow) : power(pow) { this->timeSeries = series; }
  ~Trend() = default;

  void setCoefficients(S21Matrix coefficients);
  bool fTest(Fisher *fisher);

  void parameterEstimation();

  void setR();

  S21Matrix getX();
  virtual S21Matrix getY() = 0;
  virtual void setYEstimated(S21Matrix x, S21Matrix coef) = 0;
};

class PolynomialTrend : public Trend {
 public:
  TimeSeries *timeSeries;
  int power;
  PolynomialTrend(TimeSeries *series, int pow)
      : Trend(series, pow), power(pow) {
    this->timeSeries = series;
  }
  ~PolynomialTrend() = default;

  S21Matrix getY();
  void setYEstimated(S21Matrix x, S21Matrix coef);
};

class ExponentialTrend : public Trend {
 public:
  TimeSeries *timeSeries;
  int power;
  ExponentialTrend(TimeSeries *series, int pow)
      : Trend(series, pow), power(pow) {
    this->timeSeries = series;
  }
  ~ExponentialTrend() = default;

  S21Matrix getY();
  void setYEstimated(S21Matrix x, S21Matrix coef);
};

class DetermineTrend {
 public:
  TimeSeries *timeSeries;

  DetermineTrend(TimeSeries *series) { this->timeSeries = series; }
  ~DetermineTrend() = default;

  Trend *getTrend();
  Trend *findPowerOfTrend(Fisher *fisher, bool check);

  void deleteTrend(Trend *one, Trend *two);
};
