#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <qfiledialog.h>
#include "toolparentclass.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
	filePath = ui->filePath;
	numSets = ui->numSets;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pathButton_clicked() {
    QString path = QFileDialog::getOpenFileName(0, "TSV-Datei öffnen", QDir::currentPath(), "CSV-Dateien(*.csv *.tsv *txt)");
	ui->filePath->setText(path);
	csv = csv.readCsv(ui->filePath->text());
	csv.filterEmptyContexts();

	csv.randomize();
	csv.writeToFile(path);
	
	
	csv.makeTotalBoW();
	csv.makeClassBoWs();
	csv.addFeatures();
	csv.writeVectorFile(path);

	//csv.makeSets(numSets->value());
}
