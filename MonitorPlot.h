
#ifndef QLIST_MONITORPLOT_H
#define QLIST_MONITORPLOT_H

#include <QChart>
#include <QChartView>
#include <QListWidget>
QT_CHARTS_USE_NAMESPACE

class MonitorPlot : public QChartView{
Q_OBJECT

public:
    explicit MonitorPlot(QWidget* parent = nullptr);
    ~MonitorPlot()=default;

    void updateChart(QList<int>& selectedColumns,
                     QList<QListWidgetItem*> selectedItems,
                     QVector<QVector<double>>& data);

    QChart* monitorChart;

private:
    void setupChart();

};


#endif //QLIST_MONITORPLOT_H
