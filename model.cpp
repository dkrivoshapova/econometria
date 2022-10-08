#include "model.h"
void Model::calc(std::string str) {
  string_to_vector(str);
  for (int i = 0; i < timeSeries.size(); i++) {
    std::cout << timeSeries[i] << " ";
  }
  std::cout << "\n\n";
  calcParams(1);
  std::vector<double> res = getCoordinates();
  for (int i = 0; i < res.size(); i++) {
    std::cout << res[i] << " ";
  }
  std::cout << "\n\n";
  calcParams(2);
  res = getCoordinates();
  for (int i = 0; i < res.size(); i++) {
    std::cout << res[i] << " ";
  }
}

void Model::string_to_vector(std::string str) {
  std::regex e("[0-9]*[.,]?[0-9]+(?:[eE][-+]?[0-9]+)?");
  std::regex_iterator<std::string::iterator> rit(str.begin(), str.end(), e);
  std::regex_iterator<std::string::iterator> rend;
  int previous = 0;
  for (; rit != rend; ++rit) {
    timeSeries.push_back(std::stod(rit->str()));
  }
}

double Model::calcAlpha(int j) {
  double sum = 0;
  if (j == t_2) {
    for (int i = 0; i < t; i++) {
      sum += pow(-1, i + 1) * timeSeries[i];
    }
    return sum / t;
  }
  if (j == 0) {
    for (int i = 0; i < t; i++) {
      sum += timeSeries[i];
    }
    return sum / t;
  }
  if (j < t_2) {
    for (int i = 0; i < t; i++) {
      sum += timeSeries[i] * cos(2 * M_PI * j * (i + 1) / t);
    }
    return 2 * sum / t;
  } else {
    throw std::invalid_argument("ERROR");
  }
}

double Model::calcBetta(int j) {
  double sum = 0;
  for (int i = 0; i < t; i++) {
    sum += timeSeries[i] * sin(2 * M_PI * j * (i + 1) / t);
  }
  return 2 * sum / t;
}

void Model::calcParams(int j) {
  t = timeSeries.size();
  if (t % 2 == 0) {
    t_2 = t / 2;
  } else {
    t_2 = (t - 1) / 2;
  }
  Alpha = calcAlpha(j);
  Betta = calcBetta(j);
  R = pow(pow(Alpha, 2) + pow(Betta, 2), 0.5);
  W = 2 * M_PI * j / t;
  O = tan(Betta / Alpha);
  std::cout << Alpha << "\n";
  std::cout << Betta << "\n";
  std::cout << R << "\n";
  std::cout << W << "\n";
  std::cout << O << "\n";
}

std::vector<double> Model::getCoordinates() {
  std::vector<double> result;
  for (int i = 1; i <= t; i++) {
    result.push_back(R * cos(W * i - O));
  }
  return result;
}