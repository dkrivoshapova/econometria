#ifndef GISTOGRAMWORKER_H
#define GISTOGRAMWORKER_H

#include "facade.h"
#include "qcustomplot.h"

class GistogramWorker {
 public:
  GistogramWorker(Facade *facade);
  ~GistogramWorker() = default;

  void InitGistogramWorker(QCustomPlot *qcustomplot);
  void SetBaseSettingPlots();
  void AddHarmonic();
  QPair<QVector<double>, QVector<double>> VectorToPairQVector(
      std::vector<double> first, std::vector<double> second);

 private:
  Facade *facade_;
  QCustomPlot *qcustomplot_;
  QCPBars *fossil;
  bool check;
};

#endif  // GISTOGRAMWORKER_H
