#pragma once

#include "fisher.h"
#include "harmonic.h"
#include "timeSeries.h"
#include "trend.h"

class Facade {
 public:
  Facade(Parser *parser);
  ~Facade(){
  };

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
  std::pair<std::vector<double>, std::vector<double>> getPeriodogram();
  int getHarmonicCount();

 private:
  Parser *parser_;
  TimeSeries *timeSeries_;
  TimeSeries *difference_;
  Trend *trend_;
  HarmonicAnalys *harmonicAnalys_;
  std::vector<double> harmonic;

  void setHarmonicVector(std::vector<double> vec);
  void clear();
};

std::string to_string(double number);
std::string to_string(int number);
