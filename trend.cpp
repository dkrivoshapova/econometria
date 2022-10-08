#include "trend.h"

void PolynomialTrend::parameterEstimation() {
  S21Matrix x = getX();
  S21Matrix y = getY();
  S21Matrix xTransposed = x.transpose();

  S21Matrix resultTransposed = xTransposed * x;
  S21Matrix result = resultTransposed.inverse_matrix();
  result *= xTransposed;
  result *= y;
  setCoefficients(result);
}

S21Matrix PolynomialTrend::getX() {
  S21Matrix x(timeSeries->t, power + 1);
  for (int i = 0; i < x.getRows(); i++) {
    for (int j = 0; j < x.getCols(); j++) {
      x(i, j) = pow(timeSeries->x[i], j);
    }
  }
  return x;
}

S21Matrix PolynomialTrend::getY() {
  S21Matrix y(timeSeries->t, 1);
  for (int i = 0; i < y.getRows(); i++) {
    y(i, 0) = timeSeries->timeSeries[i];
  }
  return y;
}
void Trend::setCoefficients(S21Matrix coef) {
  for (int i = 0; i < coef.getRows(); i++) {
    coefficients.push_back(coef(i, 0));
  }
}
