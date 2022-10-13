#include "facade.h"

Facade::Facade(Parser *parser) : parser_(parser) {
  timeSeries_ = new TimeSeries();
  difference_ = new TimeSeries();
}

std::pair<std::vector<double>, std::vector<double>> Facade::getData(
    std::string fileName) {
  parser_->parseFile(fileName);
  auto y = parser_->getY();
  auto x = parser_->getX();
  timeSeries_->calc(y, x);
  return {x, y};
}

std::pair<std::vector<double>, std::vector<double>> Facade::getTrend() {
  DetermineTrend trendd(timeSeries_);
  trend_ = trendd.getTrend();
  auto vec = trend_->yEstimated;
  return {parser_->getX(), vec};
}

std::pair<std::vector<double>, std::vector<double>> Facade::getDifference() {
  difference_->calc(trend_->difference, parser_->getX());
  for (auto i = 0; i < timeSeries_->t;i++) {
      harmonic.push_back(0);
  }
  auto vec = trend_->difference;
  return {parser_->getX(), vec};
}

std::pair<std::vector<double>, std::vector<double>> Facade::getHarmonic() {
  HarmonicAnalys harmonicAnalys_(difference_);
  std::vector<double> hbe = harmonicAnalys_.getYBest();
  setHarmonicVector(hbe);
  return {parser_->getX(), harmonic};
}

void Facade::setHarmonicVector(std::vector<double> vec) {
    for (int i = 0; i < harmonic.size();i++) {
        harmonic[i] += vec[i];
    }
}
