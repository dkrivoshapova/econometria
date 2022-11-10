#include "graphworker.h"

GraphWorker::GraphWorker(Facade *facade) : facade_(facade) {}

GraphWorker::~GraphWorker() {
  if (facade_ != nullptr) delete facade_;
}

void GraphWorker::InitGraphWorker(QCustomPlot *qcustomplot) {
  qcustomplot_ = qcustomplot;
  SetBaseSettingPlots();
}

QPair<bool, QString> GraphWorker::OnExportGraphInFile(const QString &filename) {
  try {
    counterGraphs_ = 0;
    ClearGraphs();
    DrawExportFile(filename);
    return {true, ""};
  } catch (std::invalid_argument &ex) {
    return {false, ex.what()};
  }
}

void GraphWorker::DrawExportFile(QString filename) {
  QPen pen;
  pen.setWidthF(kWidthGraph);
  pen.setColor(colorGraph[counterGraphs_]);
  qcustomplot_->addGraph()->setPen(pen);
  auto pair = facade_->getData(filename.toStdString());
  auto pairQ = VectorToPairQVector(pair.first, pair.second);
  qcustomplot_->graph(0)->addData(pairQ.first, pairQ.second);
  qcustomplot_->rescaleAxes();
  qcustomplot_->replot();
}

QPair<bool, QString> GraphWorker::DrawTrend(bool type, int power) {
  if (counterGraphs_ != 0) {
    qcustomplot_->removeGraph(counterGraphs_);
    counterGraphs_ = 0;
  }
  counterGraphs_ += 1;
  SetPen();
  std::pair<std::vector<double>, std::vector<double>> pair;
  if (type) {
    pair = facade_->getPolinomialTrend(power);
  } else {
    pair = facade_->getExponentialTrend(power);
  }
  auto pairQ = VectorToPairQVector(pair.first, pair.second);
  qcustomplot_->graph(counterGraphs_)->addData(pairQ.first, pairQ.second);
  qcustomplot_->rescaleAxes();
  qcustomplot_->replot();
  return {true, ""};
}

void GraphWorker::DeleteTrend() {
  ClearGraphs();

  counterGraphs_ = 0;
  SetPen();
  auto pair = facade_->getDifference();
  auto pairQ = VectorToPairQVector(pair.first, pair.second);
  qcustomplot_->graph(counterGraphs_)->addData(pairQ.first, pairQ.second);
  qcustomplot_->rescaleAxes();
  qcustomplot_->replot();
}

void GraphWorker::AddHarmonic() {
  if (counterGraphs_ != 0) {
      qcustomplot_->removeGraph(counterGraphs_);
  } else {
      counterGraphs_++;
  }
  SetPen();
  auto pair = facade_->getHarmonic();
  auto pairQ = VectorToPairQVector(pair.first, pair.second);
  qcustomplot_->graph(counterGraphs_)->addData(pairQ.first, pairQ.second);
  qcustomplot_->rescaleAxes();
  qcustomplot_->replot();
}

void GraphWorker::SetBaseSettingPlots() {
  qcustomplot_->setInteraction(QCP::iRangeZoom, true);
  qcustomplot_->setInteraction(QCP::iRangeDrag, true);
  qcustomplot_->setBackground(QColor(235, 234, 230));
  qcustomplot_->legend->setVisible(true);
  qcustomplot_->replot();
}

QPair<QVector<double>, QVector<double>> GraphWorker::VectorToPairQVector(
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

void GraphWorker::ClearGraphs() {
  //    facade_->ClearData();
  qcustomplot_->clearGraphs();
}

void GraphWorker::SetPen() {
  QPen pen;
  pen.setWidthF(kWidthGraph);
  pen.setColor(colorGraph[counterGraphs_]);
  qcustomplot_->addGraph()->setPen(pen);
}
