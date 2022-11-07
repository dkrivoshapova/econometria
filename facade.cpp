#include "facade.h"

#include <QDebug>

Facade::Facade(Parser *parser) : parser_(parser) {
  timeSeries_ = new TimeSeries();
  difference_ = new TimeSeries();
}

std::pair<std::vector<double>, std::vector<double>> Facade::getData(
    std::string fileName) {
  parser_->parseFile(fileName);
  auto y = parser_->getY();
  auto x = parser_->getX();
  timeSeries_->initTimeSeries(y, x);
  return {x, y};
}

std::pair<std::vector<double>, std::vector<double>> Facade::getPolinomialTrend(
    int power) {
  trend_ = new PolynomialTrend(timeSeries_, power);
  trend_->parameterEstimation();
  auto vec = trend_->yEstimated;
  return {parser_->getX(), vec};
}

std::pair<std::vector<double>, std::vector<double>> Facade::getExponentialTrend(
    int power) {
  trend_ = new ExponentialTrend(timeSeries_, power);
  trend_->parameterEstimation();
  auto vec = trend_->yEstimated;
  return {parser_->getX(), vec};
}

std::pair<std::vector<double>, std::vector<double>> Facade::getDifference() {
  difference_->initTimeSeries(trend_->difference, parser_->getX());
  for (auto i = 0; i < timeSeries_->t; i++) {
    harmonic.push_back(0);
  }
  auto vec = trend_->difference;
  return {parser_->getX(), vec};
}

std::pair<std::vector<double>, std::vector<double>> Facade::getHarmonic() {
  qDebug() << "differanse" << difference_->timeSeries;
  // HarmonicAnalys harmonicAnalys_(difference_);
  harmonicAnalys_ = new HarmonicAnalys(difference_);
  std::vector<double> hbe = harmonicAnalys_->getYBest();
  qDebug() << "hbe " << hbe;
  setHarmonicVector(hbe);
  qDebug() << "harmonic " << harmonic;
  return {parser_->getX(), harmonic};
}

std::pair<std::vector<double>, std::vector<double>> Facade::getPeriodogram() {
  std::vector<double> res;
  for (auto i = 0; i <= timeSeries_->t_2; i++) {
    res.push_back(i);
  }
  return {res, harmonicAnalys_->periodogramCoordinates()};
}

void Facade::setHarmonicVector(std::vector<double> vec) {
  for (int i = 0; i < vec.size(); i++) {
    harmonic[i] += vec[i];
  }
}

std::string Facade::getTrendEquation() {
  std::string result = "";
  for (int i = trend_->coefficients.size() - 1; i > 0; i--) {
    result += to_string(trend_->coefficients[i]) + "t^" + to_string(i) + " ";
    if (trend_->coefficients[i - 1] > 0) result += "+";
  }
  result += to_string(trend_->coefficients[0]);
  return result;
}

std::string Facade::getF() {
  std::string result = "";
  std::pair<double, double> f = trend_->fTest();
  if (f.first > f.second) {
    result =
        to_string(f.first) + " > " + to_string(f.second) + " регрессия значима";
  } else {
    result = to_string(f.first) + " <= " + to_string(f.second) +
             "регрессия не значима";
  }
  return result;
}

std::string Facade::getR2() { return to_string(trend_->r); }

std::string to_string(double number) {
  std::string result;
  std::stringstream ss;
  ss << result << std::fixed << std::setprecision(2) << number;
  result = ss.str();
  return result;
}

std::string to_string(int number) {
  std::string result;
  std::stringstream ss;
  ss << result << std::fixed << std::setprecision(0) << number;
  result = ss.str();
  return result;
}
