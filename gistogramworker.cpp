#include "gistogramworker.h"

GistogramWorker::GistogramWorker(Facade *facade) : facade_(facade) {}

void GistogramWorker::InitGistogramWorker(QCustomPlot *qcustomplot) {
  qcustomplot_ = qcustomplot;
  SetBaseSettingPlots();
}

void GistogramWorker::SetBaseSettingPlots() {
    QCPAxis *keyAxis = qcustomplot_->xAxis;
    QCPAxis *valueAxis = qcustomplot_->yAxis;
    QCPBars * fossil = new QCPBars (keyAxis, valueAxis); // Используйте xAxis в качестве ключевой оси гистограммы и yAxis в качестве оси значений

     fossil-> setAntialiased (false); // Для лучшего эффекта границы отключите сглаживание
     fossil-> setName ("Ископаемое топливо"); // Устанавливаем имя гистограммы, которое может отображаться в легенде
     fossil-> setPen (QPen (QColor (0, 168, 140) .lighter (130))); // Устанавливаем цвет границы гистограммы
     fossil-> setBrush (QColor (0, 168, 140)); // Устанавливаем цвет кисти гистограммы

     // Устанавливаем ключевую ось текстового типа для гистограммы, галочки определяют диапазон оси, а метки определяют отображение текста шкалы оси
     QVector<double> ticks;
//     QVector<QString> labels;
     ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7;
//     labels << "USA" << "Japan" << "Germany" << "France" << "UK" << "Italy" << "Canada";
//     QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
//     textTicker->addTicks(ticks, labels);

//      keyAxis-> setTicker (textTicker); // Установить как текстовую ось
//      keyAxis-> setTickLabelRotation (60); // Текст шкалы оси поворачивается на 60 градусов
//       keyAxis-> setSubTicks (false); // Не отображать субтики
//       keyAxis-> setTickLength (0, 4); // Длина внутренней и внешней шкалы оси 0, 4 соответственно, то есть деления на оси не отображаются
       keyAxis-> setRange (0, 20); // устанавливаем диапазон
       keyAxis->setTicks(false);
//      keyAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

      valueAxis->setRange(0, 50);
//       valueAxis-> setPadding (1); // Внутреннее поле оси, вы можете перейти к началу QCustomPlot (1), чтобы увидеть диаграмму
//      valueAxis->setLabel("Power Consumption in\nKilowatts per Capita (2007)");
//      valueAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
      QVector<double> fossilData;
      fossilData  << 0.86*10.5 << 0.83*5.5 << 0.84*5.5 << 0.52*5.8 << 0.89*5.2 << 0.90*4.2 << 0.67*11.2;
      fossil->setData(ticks, fossilData);

}
