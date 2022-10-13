#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphworker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_load_file_btn_clicked();

    void on_trend_btn_clicked();

    void on_delete_trend_btn_clicked();

    void on_add_harmonic_btn_clicked();

private:
    Ui::MainWindow *ui;
    GraphWorker *graphWorker_;
};
#endif // MAINWINDOW_H
