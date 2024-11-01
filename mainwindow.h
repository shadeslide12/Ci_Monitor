#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChartView>
#include <QChart>
#include <QPushButton>
#include <QListWidget>

QT_CHARTS_USE_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private:
    QChartView *chartView;
    QChart *chart;
    QPushButton *selectFileBtn;
    QListWidget *variableList;
    QString lastFilePath;
    
    void setupUI();
    void loadMonitorFile(const QString &filePath);
    void plotSelectedVariables();
    QStringList parseVariables(const QString &headerLine);
    QVector<QVector<double>> readData(const QString &filePath, const QList<int> &selectedColumns);

private slots:
    void onSelectFile();
    void onVariableSelectionChanged();
};

#endif // MAINWINDOW_H