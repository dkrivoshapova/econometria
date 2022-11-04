#pragma once

#include "fisher.h"
#include "harmonic.h"
#include "timeSeries.h"
#include "trend.h"

class Facade {
 public:
  Facade(Parser *parser);
  ~Facade() { delete trend_; };

  std::pair<std::vector<double>, std::vector<double>> getData(
      std::string fileName);
  std::pair<std::vector<double>, std::vector<double>> getPolinomialTrend(
      int power);
  std::pair<std::vector<double>, std::vector<double>> getExponentialTrend(
      int power);
  std::pair<std::vector<double>, std::vector<double>> getDifference();
  std::pair<std::vector<double>, std::vector<double>> getHarmonic();
  std::string getTrendEquation();
  std::string getF();
  std::string getR2();

 private:
  Parser *parser_;
  TimeSeries *timeSeries_;
  TimeSeries *difference_;
  Trend *trend_;
  std::vector<double> harmonic;

  void setHarmonicVector(std::vector<double> vec);
};

std::string to_string(double number);
std::string to_string(int number);
