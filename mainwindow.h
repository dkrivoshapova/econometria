#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "graphworker.h"
#include "gistogramworker.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_load_file_btn_clicked();

  void on_trend_btn_clicked();

  void on_delete_trend_btn_clicked();

  void on_add_harmonic_btn_clicked();

  void on_addAllbtn_clicked();

  void ex_code();

private:
  Ui::MainWindow *ui;
  GraphWorker *graphWorker_;
  GistogramWorker *gistogramWorker_;
  Parser *parser_;
  Facade *facade_;
  int cnt_;
  void showMessageBox(QWidget *parent, QString message);
};
#endif  // MAINWINDOW_H
