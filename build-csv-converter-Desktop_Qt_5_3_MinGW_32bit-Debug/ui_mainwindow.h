/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *filePath;
    QPushButton *pathButton;
    QPushButton *convertFile;
    QLabel *label_4;
    QLineEdit *targetPath;
    QPushButton *saveFile;
    QPushButton *targetPathButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(746, 518);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 191, 51));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 80, 621, 61));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 190, 71, 16));
        filePath = new QLineEdit(centralWidget);
        filePath->setObjectName(QStringLiteral("filePath"));
        filePath->setGeometry(QRect(130, 190, 311, 20));
        pathButton = new QPushButton(centralWidget);
        pathButton->setObjectName(QStringLiteral("pathButton"));
        pathButton->setGeometry(QRect(460, 190, 75, 23));
        convertFile = new QPushButton(centralWidget);
        convertFile->setObjectName(QStringLiteral("convertFile"));
        convertFile->setGeometry(QRect(550, 190, 91, 23));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 240, 47, 13));
        targetPath = new QLineEdit(centralWidget);
        targetPath->setObjectName(QStringLiteral("targetPath"));
        targetPath->setGeometry(QRect(130, 230, 311, 20));
        saveFile = new QPushButton(centralWidget);
        saveFile->setObjectName(QStringLiteral("saveFile"));
        saveFile->setGeometry(QRect(550, 230, 91, 23));
        targetPathButton = new QPushButton(centralWidget);
        targetPathButton->setObjectName(QStringLiteral("targetPathButton"));
        targetPathButton->setGeometry(QRect(460, 230, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 746, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label->setText(QApplication::translate("MainWindow", "CSV-Converter", 0));
        label_2->setText(QApplication::translate("MainWindow", "Instructions go here", 0));
        label_3->setText(QApplication::translate("MainWindow", "Datei w\303\244hlen", 0));
        pathButton->setText(QApplication::translate("MainWindow", "Durchsuchen", 0));
        convertFile->setText(QApplication::translate("MainWindow", "Konvertieren", 0));
        label_4->setText(QApplication::translate("MainWindow", "Ziel", 0));
        saveFile->setText(QApplication::translate("MainWindow", "Speichern", 0));
        targetPathButton->setText(QApplication::translate("MainWindow", "Durchsuchen", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
