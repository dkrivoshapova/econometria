#ifndef GRAPHWORKER_H
#define GRAPHWORKER_H

#include "facade.h"
#include "qcustomplot.h"

constexpr int kWidthGraph = 3;
constexpr int kWidthDot = 5;
constexpr int kMaxGraphs = 5;
constexpr int kMinGraphs = 0;
constexpr long kShiftTime = 864000;
constexpr long kShiftY = 10;

class GraphWorker
{
public:
    GraphWorker(Facade *facade);
    ~GraphWorker();

    void InitGraphWorker(QCustomPlot *qcustomplot);
    QPair<bool, QString>  OnExportGraphInFile(const QString &filename);
    QPair<bool, QString> DrawTrend();
    void DeleteTrend();
    void AddHarmonic();

private:
    Facade *facade_;
    QCustomPlot *qcustomplot_;
    QVector<QColor> colorGraph = {QColor(255, 81, 60), QColor(32, 178, 170), QColor(70, 130, 180), QColor(244, 175, 96), QColor(255, 192, 203), QColor(107, 91, 149)};
    int counterGraphs_;
    void SetBaseSettingPlots();
    void DrawExportFile(QString filename);
    void ClearGraphs();
    QPair<QVector<double>, QVector<double>> VectorToPairQVector(std::vector<double> first, std::vector<double> second);
    void SetPen();
};

#endif // GRAPHWORKER_H
