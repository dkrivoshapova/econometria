#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    graphWorker_ = new GraphWorker(new Facade(new Parser));
    graphWorker_->InitGraphWorker(ui->graphWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete graphWorker_;
}


void MainWindow::on_load_file_btn_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, ("Open the file"),  QDir::homePath(), "*.csv");
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
     auto pair = graphWorker_->DrawTrend();
//     if (!pair.first) {
//         s21::Assistant::ShowMessageBox(this, pair.second);
//     }
}


void MainWindow::on_delete_trend_btn_clicked() {
    graphWorker_->DeleteTrend();
}


void MainWindow::on_add_harmonic_btn_clicked()
{
    graphWorker_->AddHarmonic();
}

