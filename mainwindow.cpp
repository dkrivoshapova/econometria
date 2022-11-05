#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  parser_ = new Parser();
  facade_ = new Facade(parser_);
  graphWorker_ = new GraphWorker(facade_);
  graphWorker_->InitGraphWorker(ui->graphWidget);
  gistogramWorker_ = new GistogramWorker(facade_);
  gistogramWorker_->InitGistogramWorker(ui->diagramWidget);

}

MainWindow::~MainWindow() {
  delete ui;
  delete graphWorker_;
  delete parser_;
//  delete facade_;
}

void MainWindow::on_load_file_btn_clicked() {
  QString fileName = QFileDialog::getOpenFileName(this, ("Open the file"),
                                                  QDir::homePath(), "*.csv");
  if (fileName.isEmpty()) {
    return;
  }
  auto pair = graphWorker_->OnExportGraphInFile(fileName);
  if (pair.first) {
    //        s21::Assistant::SetFilename(ui->fileLineEdit, fileName);
  } else {
    //        s21::Assistant::ShowMessageBox(this, pair.second);
  }
}

void MainWindow::on_trend_btn_clicked() {
  int power = ui->power_box->value();
  auto pair = graphWorker_->DrawTrend(ui->polinomial->isChecked(), power);
  ui->set_eq_lbl->setText(QString::fromStdString(facade_->getTrendEquation()));
  ui->set_fstatistic_lbl->setText(QString::fromStdString(facade_->getF()));
  ui->set_red_lbl->setText(QString::fromStdString(facade_->getR2()));

  //     if (!pair.first) {
  //         s21::Assistant::ShowMessageBox(this, pair.second);
  //     }
}

void MainWindow::on_delete_trend_btn_clicked() { graphWorker_->DeleteTrend(); }

void MainWindow::on_add_harmonic_btn_clicked() { graphWorker_->AddHarmonic(); }
