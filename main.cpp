#include "timeSeries.h"
#include "trend.h"
int main(int argc, char *argv[]) {
  TimeSeries f;
  std::string d = "3 1 2 2";
  f.calc(d);
  ExponentialTrend trend(&f, 1);
  trend.parameterEstimation();
  for (int i = 0; i < trend.coefficients.size(); i++) {
    std::cout << trend.coefficients[i] << " ";
  }
}
