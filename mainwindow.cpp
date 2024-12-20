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
    : QMainWindow(parent), ui(new Ui::MainWindow),
    monitorPlot(new MonitorPlot(this)),
    timer(new QTimer(this)), filePositionTable({0,0,0})
{
    inletFile.setFileName("./mon_inlet.dat");
    outletFile.setFileName("./mon_outlet.dat");
    perfFile.setFileName("./mon_perf.dat");

    ui->setupUi(this);
    setupUI();
    timer->setInterval(1000);
    connect(timer,&QTimer::timeout,this,&MainWindow::updateMonitorData);
}

void MainWindow::setupUI()
{
    ui->Layout_Plot->addWidget(monitorPlot);
    connect(ui->Button_Select, &QPushButton::clicked, this, &MainWindow::onSelectFile);
    connect(ui->List_Variable, &QListWidget::itemSelectionChanged, 
            this, &MainWindow::onVariableSelectionChanged);
    connect(ui->Button_Font, &QPushButton::clicked, this, &MainWindow::onFontChanged);
    connect(ui->CBox_Theme,
            static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &MainWindow::updateUI);


    ui->CBox_Theme->addItem("Light", QChart::ChartThemeLight);
    ui->CBox_Theme->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    ui->CBox_Theme->addItem("Dark", QChart::ChartThemeDark);
    ui->CBox_Theme->addItem("Brown Sand", QChart::ChartThemeBrownSand);
    ui->CBox_Theme->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
    ui->CBox_Theme->addItem("High Contrast", QChart::ChartThemeHighContrast);
    ui->CBox_Theme->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    ui->CBox_Theme->addItem("Qt", QChart::ChartThemeQt);
}

void MainWindow::onSelectFile()
{
    QString filePath = QFileDialog::getOpenFileName(this,
        "Select Monitor Files", "", "Monitor Files (*.dat);;All Files (*)");
    if (filePath.isEmpty())
        return;

    ui->List_Variable->clear();
    qDebug()<< filePath;

    if(filePath.contains("inlet")){
        ui->List_Variable->addItem("pTotal(inlet)");
        ui->List_Variable->addItem("tTotal(inlet)");
        ui->List_Variable->addItem("vAxial(inlet)");
        ui->List_Variable->addItem("vTheta(inlet)");
        ui->List_Variable->addItem("pStatic(inlet)");
        ui->List_Variable->addItem("mDot(inlet)");
    }
    if(filePath.contains("outlet")){
        ui->List_Variable->addItem("pTotal(outlet)");
        ui->List_Variable->addItem("tTotal(outlet)");
        ui->List_Variable->addItem("vAxial(outlet)");
        ui->List_Variable->addItem("vTheta(outlet)");
        ui->List_Variable->addItem("pStatic(outlet)");
        ui->List_Variable->addItem("mDot(outlet)");
    }
    if(filePath.contains("perf")){
        ui->List_Variable->addItem("pRatio");
        ui->List_Variable->addItem("tRatio");
        ui->List_Variable->addItem("efficiency");
        ui->List_Variable->addItem("turning");
        ui->List_Variable->addItem("qInlet");
        ui->List_Variable->addItem("qOutlet");
    }
}


void MainWindow::onVariableSelectionChanged()
{
    if(ui->List_Variable->selectedItems().isEmpty()){
        monitorPlot->hideSeries();
        qDebug() << "List is empty ";
        return;
    }

    displayVariableList.clear();
    for(auto const item : ui->List_Variable->selectedItems()){
        qDebug()<<item->data(Qt::DisplayRole).toString();
        displayVariableList.append(item->data(Qt::DisplayRole).toString());
    }

    monitorPlot->updateSeriesVisibility(displayVariableList);
    monitorPlot->updateRangeOnVariableChange();
    updateMonitorData();
}



void MainWindow::updateMonitorData() {
    qDebug()<<"lastFilePosition"<<filePositionTable[0];
    if(!inletFile.isOpen()) {
        if (!(inletFile.open(QIODevice::ReadOnly | QIODevice::Text))) {
            qDebug() << "faile to read Files";
            return;
        }
    }
    if(!outletFile.isOpen()) {
        if (!(outletFile.open(QIODevice::ReadOnly | QIODevice::Text))) {
            qDebug() << "faile to read Files";
            return;
        }
    }
    if(!perfFile.isOpen()) {
        if (!(perfFile.open(QIODevice::ReadOnly | QIODevice::Text))) {
            qDebug() << "faile to read Files";
            return;
        }
    }
    QTextStream inInlet(&inletFile);
    QTextStream inOutlet(&outletFile);
    QTextStream inPerf(&perfFile);

    inInlet.seek(filePositionTable[0]);
    inOutlet.seek(filePositionTable[1]);
    inPerf.seek(filePositionTable[2]);

    if(filePositionTable[0] == 0){
        inInlet.readLine();
        inInlet.readLine();
        inOutlet.readLine();
        inOutlet.readLine();
        inPerf.readLine();
        inPerf.readLine();
    }
    QString lineInlet = inInlet.readLine();
    QString lineOutlet = inOutlet.readLine();
    QString linePerf = inPerf.readLine();
    if(lineInlet.isEmpty() || lineOutlet.isEmpty() || linePerf.isEmpty()) {
        qDebug() << lineInlet.isEmpty();
        qDebug() << lineOutlet.isEmpty();
        qDebug() << linePerf.isEmpty();
        return;
    }

    QStringList valuesInlet = lineInlet.split(" ",Qt::SkipEmptyParts);
    qDebug() << "inletFile value is " <<valuesInlet;
    iteration.append(valuesInlet[0].toInt());

    monitorVariableTable.inlet.pTotal.append(valuesInlet[1].toDouble());
    monitorVariableTable.inlet.tTotal.append(valuesInlet[2].toDouble());
    monitorVariableTable.inlet.vAxial.append(valuesInlet[3].toDouble());
    monitorVariableTable.inlet.vTheta.append(valuesInlet[4].toDouble());
    monitorVariableTable.inlet.pStatic.append(valuesInlet[5].toDouble());
    monitorVariableTable.inlet.mDot.append(valuesInlet[6].toDouble());

    QStringList valuesOutlet = lineOutlet.split(" ",Qt::SkipEmptyParts) ;
    qDebug() << "outletFile value is " << valuesOutlet;
    monitorVariableTable.outlet.pTotal.append(valuesOutlet[1].toDouble());
    monitorVariableTable.outlet.tTotal.append(valuesOutlet[2].toDouble());
    monitorVariableTable.outlet.vAxial.append(valuesOutlet[3].toDouble());
    monitorVariableTable.outlet.vTheta.append(valuesOutlet[4].toDouble());
    monitorVariableTable.outlet.pStatic.append(valuesOutlet[5].toDouble());
    monitorVariableTable.outlet.mDot.append(valuesOutlet[6].toDouble());

    QStringList valuesPerf = linePerf.split(" ", Qt::SkipEmptyParts);
    qDebug() << "PerfFile value is " << valuesPerf;
    monitorVariableTable.perform.pRatio.append(valuesPerf[1].toDouble());
    monitorVariableTable.perform.tRatio.append(valuesPerf[2].toDouble());
    monitorVariableTable.perform.efficiency.append(valuesPerf[3].toDouble());
    monitorVariableTable.perform.turning.append(valuesPerf[4].toDouble());
    monitorVariableTable.perform.qInlet.append(valuesPerf[5].toDouble());
    monitorVariableTable.perform.qOutlet.append(valuesPerf[6].toDouble());

    filePositionTable[0] = inInlet.pos();
    filePositionTable[1] = inOutlet.pos();
    filePositionTable[2] = inPerf.pos();
    if(ui->List_Variable->selectedItems().isEmpty())
        return;
    monitorPlot->updateChart(iteration.last(), monitorVariableTable);
}


void MainWindow::onFontChanged()
{   
        bool ok;
        QFont font = QFontDialog::getFont(&ok, QFont("Arial", 12), this);
        if (ok) {
            monitorPlot->onFontChanged(font);
        }
}

void MainWindow::on_Button_Start_clicked(){
    qDebug()<<"you pressed the start button";
    timer->start();

}

void MainWindow::updateUI(){
    qDebug()<<ui->CBox_Theme->currentIndex();
    QChart::ChartTheme theme = static_cast<QChart::ChartTheme>(
            ui->CBox_Theme->itemData(ui->CBox_Theme->currentIndex()).toInt());
    monitorPlot->monitorChart->setTheme(theme);

    QPalette pal = window()->palette();
    if (theme == QChart::ChartThemeLight) {
        pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
        //![8]
    } else if (theme == QChart::ChartThemeDark) {
        pal.setColor(QPalette::Window, QRgb(0x121218));
        pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    } else if (theme == QChart::ChartThemeBlueCerulean) {
        pal.setColor(QPalette::Window, QRgb(0x40434a));
        pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    } else if (theme == QChart::ChartThemeBrownSand) {
        pal.setColor(QPalette::Window, QRgb(0x9e8965));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
    } else if (theme == QChart::ChartThemeBlueNcs) {
        pal.setColor(QPalette::Window, QRgb(0x018bba));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
    } else if (theme == QChart::ChartThemeHighContrast) {
        pal.setColor(QPalette::Window, QRgb(0xffab03));
        pal.setColor(QPalette::WindowText, QRgb(0x181818));
    } else if (theme == QChart::ChartThemeBlueIcy) {
        pal.setColor(QPalette::Window, QRgb(0xcee7f0));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
    } else {
        pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
    }
    window()->setPalette(pal);
}