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
  delete gistogramWorker_;
}

void MainWindow::on_load_file_btn_clicked() {
  cnt_ = 0;
  QString fileName = QFileDialog::getOpenFileName(this, ("Open the file"),
                                                  QDir::homePath(), "*.csv");
  if (fileName.isEmpty()) {
    return;
  }
  auto pair = graphWorker_->OnExportGraphInFile(fileName);
  if (!pair.first) {
    showMessageBox(this, pair.second);
  }
}

void MainWindow::on_trend_btn_clicked() {
  int power = ui->power_box->value();
  auto pair = graphWorker_->DrawTrend(ui->polinomial->isChecked(), power);
  if (!pair.first) {
      showMessageBox(this, pair.second);
  }
  ui->set_eq_lbl->setText(QString::fromStdString(facade_->getTrendEquation()));
  ui->set_fstatistic_lbl->setText(QString::fromStdString(facade_->getF()));
  ui->set_red_lbl->setText(QString::fromStdString(facade_->getR2()));
}

void MainWindow::on_delete_trend_btn_clicked() {
    graphWorker_->DeleteTrend();
}

void MainWindow::on_add_harmonic_btn_clicked() {
    graphWorker_->AddHarmonic();
    gistogramWorker_->AddHarmonic();
}


void MainWindow::on_addAllbtn_clicked() {
    QTimer::singleShot(300, this, SLOT(ex_code()));
}

void MainWindow::ex_code() {
    on_add_harmonic_btn_clicked();
    if (cnt_ == facade_->getHarmonicCount()) {
        return;
    }
    cnt_++;
    QTimer::singleShot(300, this, SLOT(ex_code()));
}

void MainWindow::showMessageBox(QWidget *parent, QString message) {
    QMessageBox msg_box(parent);
    msg_box.setStyleSheet("background-color: #171923;");
    QPushButton *btn = msg_box.addButton("Ok, sorry!", QMessageBox::ActionRole);
    msg_box.setText(message);
    msg_box.exec();
}
