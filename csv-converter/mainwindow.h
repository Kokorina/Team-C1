#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <vector>
#include "CsvFile.h"
#include "toolparentclass.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
	void on_pathButton_clicked();

private:
    Ui::MainWindow *ui;
	QLineEdit *filePath;
	QPushButton *pathButton;
	QPushButton *convertFile;
	QLineEdit *targetPath;
	QPushButton *targetPathButton;
	QPushButton *saveFile;
	QSpinBox *numSets;

	CsvFile csv;
};

#endif // MAINWINDOW_H
