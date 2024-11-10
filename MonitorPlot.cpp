
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
    axisX = new QValueAxis(this);
    axisY = new QValueAxis(this);
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
    monitorChart->legend()->setBackgroundVisible(false);
    monitorChart->legend()->setLabelColor(Qt::black);
    monitorChart->setAnimationOptions(QChart::SeriesAnimations);
    monitorChart->setTheme(QChart::ChartThemeBlueCerulean);
    monitorChart->setBackgroundRoundness(20); 
    monitorChart->setBackgroundVisible(1);
    monitorChart->setDropShadowEnabled(true);  // 开启阴影效果
    
}

void MonitorPlot::updateChart(QList<int> &selectedColumns, QList<QListWidgetItem *> selectedItems,
                              QVector<QVector<double>> &data, QVector<int> &iteration) {
    monitorChart->removeAllSeries(); // 清除旧的系列

    for (int i = 0; i < selectedColumns.size(); ++i) {
        QLineSeries *series = new QLineSeries();
        series->setName(selectedItems[i]->text());

        for (int j = 0; j < data[i].size(); ++j) {
            series->append(iteration[j], data[i][j]);
        }

        monitorChart->addSeries(series);
    }

    monitorChart->createDefaultAxes(); // 自动创建并调整坐标轴

    // 设置坐标轴标题而不更改范围
    axisX = qobject_cast<QValueAxis *>(monitorChart->axes(Qt::Horizontal).first());
    axisY = qobject_cast<QValueAxis *>(monitorChart->axes(Qt::Vertical).first() );
 
    if (axisX) {
        axisX->setTitleText("X Axis Title");
        axisX->setGridLineVisible(0);
    }
    if (axisY) {
        axisY->setTitleText("Y Axis Title");
        axisY->setGridLineVisible(1);
        axisY->setLabelFormat("%.0f");
    }

}

void MonitorPlot::onFontChanged(const QFont &font)
{
    monitorChart->legend()->setFont(font);
}