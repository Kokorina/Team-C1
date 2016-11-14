#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <qfiledialog.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
	filePath = ui->filePath;
	targetPath = ui->targetPath;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pathButton_clicked() {
    QString path = QFileDialog::getOpenFileName(0, "CSV-Datei öffnen", QDir::currentPath(), "CSV-Dateien(*.csv *txt)");
	ui->filePath->setText(path);
}

void MainWindow::on_targetPathButton_clicked() {
	QString path = QFileDialog::getSaveFileName(this, "CSV-Datei speichern", QDir::currentPath(), "CSV-Dateien(*.csv *txt)");
	ui->targetPath->setText(path);
	csv.writeToFile(ui->targetPath->text());
}

void MainWindow::on_convertFile_clicked() {
    csv = csv.readCsv(ui->filePath->text());
	//TO-DO: success message
}

void MainWindow::on_saveFile_clicked() {
    csv.writeToFile(ui->targetPath->text());
	//TO-DO: success message
}
