#include "timeSeries.h"
void TimeSeries::calc(std::string str) {
  string_to_vector(str);
  set_size();
  set_x();
  set_tss();

  // for (int i = 0; i < timeSeries.size(); i++) {
  //   std::cout << timeSeries[i] << " ";
  // }
  // std::cout << "\n\n";
}

void TimeSeries::set_size() {
  t = timeSeries.size();
  if (t % 2 == 0) {
    t_2 = t / 2;
  } else {
    t_2 = (t - 1) / 2;
  }
}

void TimeSeries::set_x() {
  for (int i = 1; i <= t; i++) {
    x.push_back(i);
  }
}

void TimeSeries::string_to_vector(std::string str) {
  std::regex e("[0-9]*[.,]?[0-9]+(?:[eE][-+]?[0-9]+)?");
  std::regex_iterator<std::string::iterator> rit(str.begin(), str.end(), e);
  std::regex_iterator<std::string::iterator> rend;
  int previous = 0;
  for (; rit != rend; ++rit) {
    timeSeries.push_back(std::stod(rit->str()));
  }
}

void TimeSeries::set_tss() {
  double average = calcAverage();
  // std::cout << "среднее " << average << "\n";
  double result = 0;
  for (int i = 1; i <= t; i++) {
    result += pow(timeSeries[i] - average, 2);
  }
  // std::cout << "tss " << result << "\n";
  tss = result;
}

double TimeSeries::calcAverage() {
  double s = 0;
  for (int i = 1; i <= t; i++) {
    s += timeSeries[i];
  }
  // std::cout << "сумма " << s << "\n";
  return s / t;
}
