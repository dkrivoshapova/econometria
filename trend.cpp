#include "trend.h"

Trend* DetermineTrend::getPolinomialTrend(int power) {
  Fisher fisher;
  fisher.parseFile();
  Trend* polynomialTrend = new PolynomialTrend(timeSeries, power);
  return polynomialTrend;
}

Trend* DetermineTrend::getExponentialTrend(int power) {
  Fisher fisher;
  fisher.parseFile();
  Trend* exponentialTrend = new ExponentialTrend(timeSeries, power);

  return exponentialTrend;
}

void DetermineTrend::deleteTrend(Trend* one, Trend* two) {
  delete one;
  delete two;
}

void Trend::setCoefficients(S21Matrix coef) {
  for (int i = 0; i < coef.getRows(); i++) {
    coefficients.push_back(coef(i, 0));
  }
}

bool Trend::fTest(Fisher* fisher) {
  double k = power + 1;
  double fEstimated = (r / (k - 1)) / ((1 - r) / (timeSeries->t - k));
  double fTabular = fisher->getQuantile(k - 1, timeSeries->t - k);
  // std::cout << fEstimated << " " << fTabular << " " << r << "\n";
  return fEstimated >= fTabular;
}

void Trend::parameterEstimation() {
  S21Matrix x = getX();
  S21Matrix y = getY();
  S21Matrix xTransposed = x.transpose();

  S21Matrix resultTransposed = xTransposed * x;
  S21Matrix result = resultTransposed.inverse_matrix();
  result *= xTransposed;
  result *= y;
  setYEstimated(x, result);
  setCoefficients(result);
  setR();
}

void Trend::setR() {
  double ess = 0;
  for (size_t i = 0; i < timeSeries->t; i++) {
    double dif = timeSeries->timeSeries[i] - yEstimated[i];
    ess += pow(dif, 2);
    difference.push_back(dif);
  }
  r = 1 - (ess / timeSeries->tss);
}

void PolynomialTrend::setYEstimated(S21Matrix x, S21Matrix coef) {
  S21Matrix result = x * coef;
  for (int i = 0; i < result.getRows(); i++) {
    yEstimated.push_back(result(i, 0));
  }
}

void ExponentialTrend::setYEstimated(S21Matrix x, S21Matrix coef) {
  S21Matrix result = x * coef;
  for (int i = 0; i < result.getRows(); i++) {
    yEstimated.push_back(pow(M_E, result(i, 0)));
  }
}

S21Matrix Trend::getX() {
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

S21Matrix ExponentialTrend::getY() {
  S21Matrix y(timeSeries->t, 1);
  for (int i = 0; i < y.getRows(); i++) {
    if (timeSeries->timeSeries[i] == 0) {
      y(i, 0) = log(0.1);
    } else {
      y(i, 0) = log(timeSeries->timeSeries[i]);
    }
  }
  return y;
}
