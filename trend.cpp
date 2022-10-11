#include "trend.h"

void DetermineTrend::getTrend() {
  Fisher fisher;
  fisher.parseFile("parser/table.csv");
  Trend* polynomialTrend = findPowerOfTrend(&fisher, true);
  Trend* exponentialTrend = findPowerOfTrend(&fisher, false);
  deleteTrend(polynomialTrend, exponentialTrend);
}

Trend* DetermineTrend::findPowerOfTrend(Fisher* fisher, bool check) {
  Trend* trend;
  for (size_t i = 1; i < 6; i++) {
    if (check) {
      trend = new PolynomialTrend(timeSeries, i);
    } else {
      trend = new ExponentialTrend(timeSeries, i);
    }
    trend->parameterEstimation();
    if (trend->fTest(fisher)) {
      break;
    }
    delete trend;
  }
  return trend;
}

void deleteTrend(Trend* one, Trend* two) {
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
  double fTabular = 0;
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
  double tss = 0;
  for (size_t i = 0; i < timeSeries->t; i++) {
    double difference = timeSeries->timeSeries[i] - yEstimated[i];
    ess += pow(difference, 2);
  }
  r = 1 - (ess / tss);
}

void Trend::setYEstimated(S21Matrix x, S21Matrix coef) {
  S21Matrix result = x * coef;
  for (int i = 0; i < coef.getRows(); i++) {
    yEstimated.push_back(coef(i, 0));
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
    y(i, 0) = log(timeSeries->timeSeries[i]);
  }
  return y;
}
