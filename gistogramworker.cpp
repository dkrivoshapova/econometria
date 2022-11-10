#include "gistogramworker.h"

GistogramWorker::GistogramWorker(Facade *facade) : facade_(facade) {}

void GistogramWorker::InitGistogramWorker(QCustomPlot *qcustomplot) {
  qcustomplot_ = qcustomplot;
  SetBaseSettingPlots();
}

void GistogramWorker::SetBaseSettingPlots() {
    qcustomplot_->setInteraction(QCP::iRangeZoom, true);
    qcustomplot_->setInteraction(QCP::iRangeDrag, true);
    qcustomplot_->setBackground(QColor(235, 234, 230));
    qcustomplot_->replot();
}

void GistogramWorker::AddHarmonic() {
     auto pair = facade_->getPeriodogram();
     auto pairQ = VectorToPairQVector(pair.first, pair.second);
     if (!check) {
         int minKey = *(min_element(std::begin(pair.first),
                           std::end(pair.first)));
         int maxKey = *(max_element(std::begin(pair.first),
                           std::end(pair.first)));
         int minValue = *(min_element(std::begin(pair.second), std::end(pair.second)));
         int maxValue = *(max_element(std::begin(pair.second), std::end(pair.second)));
          qcustomplot_->xAxis->setRange(minKey, maxKey);
          qcustomplot_->yAxis->setRange(minValue, maxValue);
          fossil = new QCPBars(qcustomplot_->xAxis, qcustomplot_->yAxis);
          check = true;
     }
      fossil->setData(pairQ.first, pairQ.second);
      qcustomplot_->replot();
}

QPair<QVector<double>, QVector<double>> GistogramWorker::VectorToPairQVector(
    std::vector<double> first, std::vector<double> second) {
  QVector<double> x(first.size());
  QVector<double> y(second.size());
  QPair<QVector<QCPGraphData>, QVector<double>> pair;
  for (unsigned long i = 0; i < first.size(); i++) {
    x[i] = first[i];
    y[i] = second[i];
  }
  return {x, y};
}
