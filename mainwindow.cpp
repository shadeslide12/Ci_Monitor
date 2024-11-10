#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QLineSeries>
#include <QStringList>
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFontDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), monitorPlot(new MonitorPlot(this))
{
    ui->setupUi(this);
    setupUI();
}

void MainWindow::setupUI()
{
    ui->Layout_Plot->addWidget(monitorPlot);
    connect(ui->Button_Select, &QPushButton::clicked, this, &MainWindow::onSelectFile);
    connect(ui->List_Variable, &QListWidget::itemSelectionChanged, 
            this, &MainWindow::onVariableSelectionChanged);
    connect(ui->Button_Font, &QPushButton::clicked, this, &MainWindow::onFontChanged);
}

void MainWindow::onSelectFile()
{
    QString filePath = QFileDialog::getOpenFileName(this,
        "选择监测文件", "", "Monitor Files (*.dat);;All Files (*)");
    qDebug()<<filePath;
    if (!filePath.isEmpty()) {
        loadMonitorFile(filePath);
    }
}

QStringList MainWindow::parseVariables(const QString &headerLine)
{
    QStringList variables = headerLine.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    variables.removeFirst(); // 移除 "Iter"
    return variables;
}

void MainWindow::loadMonitorFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    
    monitorFilePath = filePath;
    QTextStream in(&file);
    QString line;
    line = in.readLine();
    line = in.readLine();

    QStringList variables = parseVariables(line);
    ui->List_Variable->clear();
    bool isFirst = 1;
    for (const QString &var : variables) {
        if(isFirst)
        {
            isFirst = 0;
            continue;
        }
        ui->List_Variable->addItem(var);
    }
}

void MainWindow::onVariableSelectionChanged()
{
    plotSelectedVariables();
}

void MainWindow::plotSelectedVariables()
{
    QList<QListWidgetItem*> selectedItems = ui->List_Variable->selectedItems();
    if (selectedItems.isEmpty())
        return;

    QList<int> selectedColumns;
    for (QListWidgetItem* item : selectedItems) {
        selectedColumns.append(ui->List_Variable->row(item) + 1);
    }

    monitorPlot->monitorChart->removeAllSeries();

    QVector<QVector<double>> data = readData(selectedColumns);
    qDebug() << data[0];
    monitorPlot->updateChart(selectedColumns,selectedItems,data,iteration);
}

QVector<QVector<double>> MainWindow::readData(const QList<int> &selectedColumns)
{
    iteration.clear();
    QVector<QVector<double>> result(selectedColumns.size());

    QFile file(monitorFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return result;

    QTextStream in(&file);
    QString line;
    
    // 跳过前两行
    in.readLine();
    in.readLine();
    
    // 读取数据
    while (!in.atEnd()) {
        line = in.readLine();
        QStringList values = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        
        for (int i = 0; i < selectedColumns.size(); ++i) {
            int col = selectedColumns[i];
            if (col < values.size()) {
                result[i].append(values[col].toDouble());
            }
        }

        iteration.append(values[0].toInt());
    }
    
    return result;
}

void MainWindow::onFontChanged()
{   
        bool ok;
        QFont font = QFontDialog::getFont(&ok, QFont("Arial", 12), this);
        if (ok) {
            monitorPlot->onFontChanged(font);
        }
}
