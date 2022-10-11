#include "timeSeries.h"
#include "trend.h"
int main(int argc, char *argv[]) {
  TimeSeries f;
  std::string d = "3 7 4 9 5 10 9 11 15 16";
  f.calc(d);
  Trend *trend = new ExponentialTrend(&f, 1);
  trend->parameterEstimation();
  for (int i = 0; i < trend->coefficients.size(); i++) {
    std::cout << trend->coefficients[i] << " ";
  }
}
