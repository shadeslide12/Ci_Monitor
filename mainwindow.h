#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChartView>
#include <QChart>
#include <QPushButton>
#include <QListWidget>
#include "MonitorPlot.h"
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

    MonitorPlot *monitorPlot;
    Ui::MainWindow *ui;
    void setupUI();
    void loadMonitorFile(const QString &filePath);
    void plotSelectedVariables();
    QStringList parseVariables(const QString &headerLine);
    QVector<QVector<double>> readData(const QList<int> &selectedColumns);

private slots:
    void onSelectFile();
    void onVariableSelectionChanged();
    void onFontChanged();
};

#endif // MAINWINDOW_H