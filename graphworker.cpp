#include "graphworker.h"

GraphWorker::GraphWorker(Facade *facade) : facade_(facade){}

GraphWorker::~GraphWorker() {
    if (facade_ != nullptr) delete facade_;
}

void GraphWorker::InitGraphWorker(QCustomPlot *qcustomplot) {
    qcustomplot_ = qcustomplot;
    SetBaseSettingPlots();
}

QPair<bool, QString>  GraphWorker::OnExportGraphInFile(const QString &filename) {
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
    qcustomplot_->replot();
}

QPair<bool, QString> GraphWorker::DrawTrend() {
    counterGraphs_ += 1;
    SetPen();
    auto pair = facade_->getTrend();
    auto pairQ = VectorToPairQVector(pair.first, pair.second);
    qcustomplot_->graph(counterGraphs_)->addData(pairQ.first, pairQ.second);
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
    qcustomplot_->replot();
}

void GraphWorker::AddHarmonic() {
    counterGraphs_ += 1;
    SetPen();
    auto pair = facade_->getHarmonic();
    for (auto &i :pair.first) {
        qDebug() << i << "\n";
    }
    for (auto &i :pair.second) {
        qDebug() << i << "\n";
    }
    auto pairQ = VectorToPairQVector(pair.first, pair.second);
    qcustomplot_->graph(counterGraphs_)->addData(pairQ.first, pairQ.second);
    qcustomplot_->replot();
}

void GraphWorker::SetBaseSettingPlots() {
    qcustomplot_->setInteraction(QCP::iRangeZoom, true);
    qcustomplot_->setInteraction(QCP::iRangeDrag, true);
    qcustomplot_->setBackground(QColor(235, 234, 230));
    qcustomplot_->legend->setVisible(true);
    qcustomplot_->replot();
}

QPair<QVector<double>, QVector<double>> GraphWorker::VectorToPairQVector(std::vector<double> first, std::vector<double> second) {
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