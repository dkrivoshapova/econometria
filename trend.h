#pragma once

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <regex>
#include <sstream>
#include <vector>

#include "fisher.h"
#include "matrix.h"
#include "timeSeries.h"

class Trend {
 public:
  std::vector<double> coefficients;
  TimeSeries *timeSeries;
  Fisher *fisher;
  std::vector<double> yEstimated;
  std::vector<double> difference;
  int power;
  double r;

  Trend() {}
  Trend(TimeSeries *series, int pow) : power(pow) {
    fisher = new Fisher();
    this->timeSeries = series;
  }
  ~Trend() { delete fisher; }

  void setCoefficients(S21Matrix coefficients);
  std::pair<double, double> fTest();

  void parameterEstimation();

  void setR();

  // std::string getEquation();

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

// class DetermineTrend {
//  public:
//   TimeSeries *timeSeries;

//   DetermineTrend(TimeSeries *series) { this->timeSeries = series; }
//   ~DetermineTrend() = default;

// Trend *getPolinomialTrend(int power);
// Trend *getExponentialTrend(int power);

//   void deleteTrend(Trend *one, Trend *two);
// };
