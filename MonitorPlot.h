
#ifndef QLIST_MONITORPLOT_H
#define QLIST_MONITORPLOT_H

#include <QChart>
#include <QValueAxis>
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
                     QVector<QVector<double>>& data,
                     QVector<int> &iteration);

    void onFontChanged(const QFont &font);

    QChart* monitorChart;

private:
    void setupChart();
    QValueAxis* axisX;
    QValueAxis* axisY;

};


#endif //QLIST_MONITORPLOT_H
