#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <qpushbutton.h>
#include "CsvFile.h"

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
	void on_convertFile_clicked();
	void on_targetPathButton_clicked();
	void on_saveFile_clicked();

private:
    Ui::MainWindow *ui;
	QLineEdit *filePath;
	QPushButton *pathButton;
	QPushButton *convertFile;
	QLineEdit *targetPath;
	QPushButton *targetPathButton;
	QPushButton *saveFile;

	CsvFile csv;
};

#endif // MAINWINDOW_H
