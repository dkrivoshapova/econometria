#include "timeSeries.h"
#include "trend.h"
int main(int argc, char* argv[]) {
  TimeSeries f;
  std::string d = "4 7 9 3 7 3 10 2 3 3";
  f.calc(d);
  DetermineTrend trendd(&f);
  Trend* trend = trendd.getTrend();

  // for (int i = 0; i < trend->coefficients.size(); i++) {
  //   std::cout << trend->coefficients[i] << " ";
  // }
}
