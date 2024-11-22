#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChartView>
#include <QChart>
#include <QPushButton>
#include <QListWidget>
#include <QTimer>
#include "MonitorPlot.h"
#include "DataStructure.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private:
    QString monitorFilePath;
    QVector<int> iteration;
    MonitorVariableTable monitorVariableTable;
    QTimer *timer;
    QFile inletFile;
    QFile outletFile;
    QFile perfFile;
    QList<QString> displayVariableList;
    QVector<qint64> filePositionTable;
    MonitorPlot *monitorPlot;
    Ui::MainWindow *ui;


    void setupUI();
    void updateMonitorData();
    
private slots:
    void onSelectFile();
    void onVariableSelectionChanged();
    void onFontChanged();
    void on_Button_Start_clicked();
    void updateUI();
};

#endif // MAINWINDOW_H