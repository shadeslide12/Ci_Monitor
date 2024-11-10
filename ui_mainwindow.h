/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *Button_Select;
    QListWidget *List_Variable;
    QWidget *Show_Plot;
    QVBoxLayout *Layout_Plot;
    QPushButton *Button_Font;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Button_Select = new QPushButton(centralwidget);
        Button_Select->setObjectName(QString::fromUtf8("Button_Select"));
        Button_Select->setGeometry(QRect(30, 30, 181, 41));
        List_Variable = new QListWidget(centralwidget);
        List_Variable->setObjectName(QString::fromUtf8("List_Variable"));
        List_Variable->setGeometry(QRect(20, 120, 201, 391));
        List_Variable->setSelectionMode(QAbstractItemView::MultiSelection);
        Show_Plot = new QWidget(centralwidget);
        Show_Plot->setObjectName(QString::fromUtf8("Show_Plot"));
        Show_Plot->setGeometry(QRect(250, 30, 521, 491));
        Layout_Plot = new QVBoxLayout(Show_Plot);
        Layout_Plot->setObjectName(QString::fromUtf8("Layout_Plot"));
        Button_Font = new QPushButton(centralwidget);
        Button_Font->setObjectName(QString::fromUtf8("Button_Font"));
        Button_Font->setGeometry(QRect(30, 80, 80, 25));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Button_Select->setText(QCoreApplication::translate("MainWindow", "Select File", nullptr));
        Button_Font->setText(QCoreApplication::translate("MainWindow", "font", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
