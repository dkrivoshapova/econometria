#ifndef GISTOGRAMWORKER_H
#define GISTOGRAMWORKER_H

#include "facade.h"
#include "qcustomplot.h"

class GistogramWorker
{
public:
    GistogramWorker(Facade *facade);
    void InitGistogramWorker(QCustomPlot *qcustomplot);
    void SetBaseSettingPlots();
private:
 Facade *facade_;
 QCustomPlot *qcustomplot_;
};

#endif // GISTOGRAMWORKER_H
