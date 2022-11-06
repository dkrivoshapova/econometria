#pragma once

#include <cmath>
#include <iostream>
#include <ostream>
#include <regex>
#include <vector>
#include <QDebug>

#include "timeSeries.h"

class Harmonic {
 public:
  double Alpha;
  double Betta;
  double R;
  double W;
  double O;
  TimeSeries *timeSeries;
  Harmonic(TimeSeries *series) : timeSeries(series) {}

  double calcAlpha(int j);
  double calcBetta(int j);
  void calcParams(int j);

  std::vector<double> getCoordinates();
};

class HarmonicAnalys {
 public:
  TimeSeries *timeSeries;
  std::vector<Harmonic> harmonics;
  HarmonicAnalys(TimeSeries *series) : timeSeries(series) {}

  std::vector<double> getYBest() {
    initHarmonics();
    double max = 0;
    Harmonic best(timeSeries);
    for (auto &i : harmonics) {
      if (i.R > max) {
        max = i.R;
        best = i;
      }
    }
//    qDebug() << "bef getYBest TimeSeries" << timeSeries->timeSeries;
    replaceY(best);
    qDebug() << "удалили гармонику TimeSeries" << timeSeries->timeSeries;
    return best.getCoordinates();
  }

  void replaceY(Harmonic best) {
    std::vector<double> coordinates = best.getCoordinates();
    for (auto i = 0; i < timeSeries->t; i++) {
      timeSeries->timeSeries[i] -= coordinates[i];
    }
  }

  void initHarmonics() {
    harmonics.clear();
    for (int i = 0; i <= timeSeries->t_2; i++) {
      Harmonic h(timeSeries);
      h.calcParams(i);
      harmonics.push_back(h);
    }
  }
};
