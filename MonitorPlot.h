#ifndef QLIST_MONITORPLOT_H
#define QLIST_MONITORPLOT_H

#include <QChart>
#include <QValueAxis>
#include <QChartView>
#include <QListWidget>
#include <QLineSeries>
#include "DataStructure.h"
#include <functional>
QT_CHARTS_USE_NAMESPACE

using ValueGetter = std::function<double(const MonitorVariableTable&)>;

class MonitorPlot : public QChartView{
Q_OBJECT

public:
    explicit MonitorPlot(QWidget* parent = nullptr);
    ~MonitorPlot()=default;
    void updateChart(int iteration, const MonitorVariableTable& data);
    void onFontChanged(const QFont &font);
    void hideSeries();
    void updateSeriesVisibility(const QStringList& selectedVariables);
    void updateRangeWithTimer(const MonitorVariableTable& data);
    void updateRangeOnVariableChange();

    QChart* monitorChart;

private:
    QList<QLineSeries* > chartSeriesTable;
    QLineSeries* inlet_pTotal;
    QLineSeries* inlet_tTotal;
    QLineSeries* inlet_vAxial;
    QLineSeries* inlet_vTheta;
    QLineSeries* inlet_pStatic;
    QLineSeries* inlet_mDot;
    
    QLineSeries* outlet_pTotal;
    QLineSeries* outlet_tTotal;
    QLineSeries* outlet_vAxial;
    QLineSeries* outlet_vTheta;
    QLineSeries* outlet_pStatic;
    QLineSeries* outlet_mDot;
    
    QLineSeries* perf_pRatio;
    QLineSeries* perf_tRatio;
    QLineSeries* perf_efficiency;
    QLineSeries* perf_turning;
    QLineSeries* perf_qInlet;
    QLineSeries* perf_qOutlet;

    QValueAxis* axisX;
    QValueAxis* axisY;
    QMap<QString, QLineSeries*> seriesMap;
    QMap<QString, ValueGetter> valueGetMap;
    double maxRangeY;
    double minRangeY;

    void setupChart();
    void initSeriesMap();
    void initValueGetMap();
    void autoScale();

};


#endif //QLIST_MONITORPLOT_H
