#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QLineSeries>
#include <QStringList>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
}

void MainWindow::setupUI()
{
    this->resize(1000, 800);
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    
    // 左侧控制面板
    QVBoxLayout *controlLayout = new QVBoxLayout();
    selectFileBtn = new QPushButton("选择监测文件", this);
    variableList = new QListWidget(this);
    variableList->setSelectionMode(QAbstractItemView::MultiSelection);
    
    controlLayout->addWidget(selectFileBtn);
    controlLayout->addWidget(variableList);
    
    // 右侧图表
    chart = new QChart();
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    
    mainLayout->addLayout(controlLayout, 1);
    mainLayout->addWidget(chartView, 4);
    
    setCentralWidget(centralWidget);
    
    connect(selectFileBtn, &QPushButton::clicked, this, &MainWindow::onSelectFile);
    connect(variableList, &QListWidget::itemSelectionChanged, 
            this, &MainWindow::onVariableSelectionChanged);
}

void MainWindow::onSelectFile()
{
    QString filePath = QFileDialog::getOpenFileName(this,
        "选择监测文件", "", "Monitor Files (*.mon);;All Files (*)");
    
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
    
    lastFilePath = filePath;
    
    QTextStream in(&file);
    QString line;
    // 跳过第一行
    line = in.readLine();
    // 读取变量行
    line = in.readLine();
    
    QStringList variables = parseVariables(line);
    
    variableList->clear();
    for (const QString &var : variables) {
        variableList->addItem(var);
    }
}

void MainWindow::onVariableSelectionChanged()
{
    plotSelectedVariables();
}

void MainWindow::plotSelectedVariables()
{
    QList<QListWidgetItem*> selectedItems = variableList->selectedItems();
    if (selectedItems.isEmpty())
        return;
        
    QList<int> selectedColumns;
    for (QListWidgetItem* item : selectedItems) {
        selectedColumns.append(variableList->row(item) + 2); // +2 因为第一列是Iter
    }
    
    // 清除现有图表
    chart->removeAllSeries();
    
    // 读取数据并绘图
    QVector<QVector<double>> data = readData(lastFilePath, selectedColumns);
    
    // 为每个选中的变量创建一条线
    for (int i = 0; i < selectedColumns.size(); ++i) {
        QLineSeries *series = new QLineSeries();
        series->setName(selectedItems[i]->text());
        
        for (int j = 0; j < data[0].size(); ++j) {
            series->append(j, data[i][j]);
        }
        
        chart->addSeries(series);
    }
    
    chart->createDefaultAxes();
}

QVector<QVector<double>> MainWindow::readData(const QString &filePath, const QList<int> &selectedColumns)
{
    QVector<QVector<double>> result(selectedColumns.size());
    
    QFile file(filePath);
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
    }
    
    return result;
}
