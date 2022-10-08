#include "harmonic.h"

double Harmonic::calcAlpha(int j) {
  double sum = 0;
  if (j == timeSeries->t_2) {
    for (int i = 0; i < timeSeries->t; i++) {
      sum += pow(-1, i + 1) * timeSeries->timeSeries[i];
    }
    return sum / timeSeries->t;
  }
  if (j == 0) {
    for (int i = 0; i < timeSeries->t; i++) {
      sum += timeSeries->timeSeries[i];
    }
    return sum / timeSeries->t;
  }
  if (j < timeSeries->t_2) {
    for (int i = 0; i < timeSeries->t; i++) {
      sum += timeSeries->timeSeries[i] * cos(2 * M_PI * j * (i + 1) / timeSeries->t);
    }
    return 2 * sum / timeSeries->t;
  } else {
    throw std::invalid_argument("ERROR");
  }
}

double Harmonic::calcBetta(int j) {
  double sum = 0;
  if (j == 0 || j > (timeSeries->t - 1.0) / 2.0) {
    return 0;
  }
    
  for (int i = 0; i < timeSeries->t; i++) {
    sum += timeSeries->timeSeries[i] * sin(2 * M_PI * j * (i + 1) / timeSeries->t);
  }
  return 2 * sum / timeSeries->t;
}

void Harmonic::calcParams(int j) {
  
  if (j <= timeSeries->t_2) {
  Alpha = calcAlpha(j);
  Betta = calcBetta(j);
  R = pow(pow(Alpha, 2) + pow(Betta, 2), 0.5);
  W = 2 * M_PI * j / timeSeries->t;
  O = tan(Betta / Alpha);
  std::cout << Alpha << " Alpha\n";
  std::cout << Betta << " Betta\n";
  std::cout << R << " R\n";
  std::cout << W << " W\n";
  std::cout << O << " O\n";
}
}

std::vector<double> Harmonic::getCoordinates() {
  std::vector<double> result;
  for (int i = 1; i <= timeSeries->t; i++) {
    result.push_back(R * cos(W * i - O));
  }
  return result;
}
