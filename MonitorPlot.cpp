
#include "MonitorPlot.h"
#include <QLineSeries>
#include <QValueAxis>
#include <QDebug>

MonitorPlot::MonitorPlot(QWidget *parent):
            monitorChart(new QChart){

    setupChart();
}

void MonitorPlot::setupChart() {
    this->setChart(monitorChart);
    QLineSeries* defaultSeries = new QLineSeries(this);
    QValueAxis* axisX = new QValueAxis(this);
    QValueAxis* axisY = new QValueAxis(this);
    qDebug()<<"ok1";

    monitorChart->addAxis(axisX,Qt::AlignBottom);
    monitorChart->addAxis(axisY,Qt::AlignLeft);

    axisX->setTitleText("Iter");
    axisY->setTitleText("Value");

    defaultSeries->attachAxis(axisX);
    defaultSeries->attachAxis(axisY);

    axisX->setRange(0,20);
    axisY->setRange(0,20);
    qDebug()<<"ok2";

    monitorChart->addSeries(defaultSeries);
}

void MonitorPlot::updateChart(QList<int> &selectedColumns, QList<QListWidgetItem *> selectedItems,
                              QVector<QVector<double>> &data)  {
    for (int i = 0; i < selectedColumns.size(); ++i) {
        QLineSeries *series = new QLineSeries();
        series->setName(selectedItems[i]->text());

        int iter = 0;

        for (int j = 0; j < data[0].size(); ++j) {
            iter = j+1;
            series->append(iter, data[i][j]);
        }

        monitorChart->addSeries(series);
    }

    monitorChart->createDefaultAxes();

}