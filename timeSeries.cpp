#include "timeSeries.h"

void TimeSeries::initTimeSeries(std::vector<double> y, std::vector<double> x_) {
  timeSeries = y;
  x = x_;
  set_size();
  set_tss();
}

void TimeSeries::set_size() {
  t = timeSeries.size();
  if (t % 2 == 0) {
    t_2 = t / 2;
  } else {
    t_2 = (t - 1) / 2;
  }
}

void TimeSeries::set_tss() {
  double average = calcAverage();
  double result = 0;
  for (int i = 1; i <= t; i++) {
    result += pow(timeSeries[i] - average, 2);
  }
  tss = result;
}

double TimeSeries::calcAverage() {
  double s = 0;
  for (int i = 1; i <= t; i++) {
    s += timeSeries[i];
  }
  return s / t;
}
