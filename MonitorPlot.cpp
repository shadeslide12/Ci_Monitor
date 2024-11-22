#include "MonitorPlot.h"
#include <QDebug>

MonitorPlot::MonitorPlot(QWidget *parent) : 
    monitorChart(new QChart),
    inlet_pTotal(new QLineSeries(this)),
    inlet_tTotal(new QLineSeries(this)),
    inlet_vAxial(new QLineSeries(this)),
    inlet_vTheta(new QLineSeries(this)),
    inlet_pStatic(new QLineSeries(this)),
    inlet_mDot(new QLineSeries(this)),
    outlet_pTotal(new QLineSeries(this)),
    outlet_tTotal(new QLineSeries(this)),
    outlet_vAxial(new QLineSeries(this)),
    outlet_vTheta(new QLineSeries(this)),
    outlet_pStatic(new QLineSeries(this)),
    outlet_mDot(new QLineSeries(this)),
    perf_pRatio(new QLineSeries(this)),
    perf_tRatio(new QLineSeries(this)),
    perf_efficiency(new QLineSeries(this)),
    perf_turning(new QLineSeries(this)),
    perf_qInlet(new QLineSeries(this)),
    perf_qOutlet(new QLineSeries(this))
{
    chartSeriesTable = {
            inlet_pTotal, inlet_tTotal, inlet_vAxial, inlet_vTheta, inlet_pStatic, inlet_mDot,
            outlet_pTotal, outlet_tTotal, outlet_vAxial, outlet_vTheta, outlet_pStatic, outlet_mDot,
            perf_pRatio, perf_tRatio, perf_efficiency, perf_turning, perf_qInlet, perf_qOutlet
    };
    setupChart();
}

void MonitorPlot::setupChart() {
    this->setChart(monitorChart);
    axisX = new QValueAxis(this);
    axisY = new QValueAxis(this);

    inlet_pTotal->setName("Inlet pTotal");
    inlet_tTotal->setName("Inlet tTotal");
    inlet_vAxial->setName("Inlet vAxial");
    inlet_vTheta->setName("Inlet vTheta");
    inlet_pStatic->setName("Inlet pStatic");
    inlet_mDot->setName("Inlet mDot");
    
    outlet_pTotal->setName("Outlet pTotal");
    outlet_tTotal->setName("Outlet tTotal");
    outlet_vAxial->setName("Outlet vAxial");
    outlet_vTheta->setName("Outlet vTheta");
    outlet_pStatic->setName("Outlet pStatic");
    outlet_mDot->setName("Outlet mDot");
    
    perf_pRatio->setName("Perf pRatio");
    perf_tRatio->setName("Perf tRatio");
    perf_efficiency->setName("Efficiency");
    perf_turning->setName("Turning");
    perf_qInlet->setName("qInlet");
    perf_qOutlet->setName("qOutlet");

    monitorChart->addSeries(inlet_pTotal);
    monitorChart->addSeries(inlet_tTotal);
    monitorChart->addSeries(inlet_vAxial);
    monitorChart->addSeries(inlet_vTheta);
    monitorChart->addSeries(inlet_pStatic);
    monitorChart->addSeries(inlet_mDot);
    
    monitorChart->addSeries(outlet_pTotal);
    monitorChart->addSeries(outlet_tTotal);
    monitorChart->addSeries(outlet_vAxial);
    monitorChart->addSeries(outlet_vTheta);
    monitorChart->addSeries(outlet_pStatic);
    monitorChart->addSeries(outlet_mDot);
    
    monitorChart->addSeries(perf_pRatio);
    monitorChart->addSeries(perf_tRatio);
    monitorChart->addSeries(perf_efficiency);
    monitorChart->addSeries(perf_turning);
    monitorChart->addSeries(perf_qInlet);
    monitorChart->addSeries(perf_qOutlet);

    monitorChart->addAxis(axisX, Qt::AlignBottom);
    monitorChart->addAxis(axisY, Qt::AlignLeft);
    
    for(auto series : chartSeriesTable) {
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }

    axisX->setTitleText("Iteration");
    axisY->setTitleText("Value");
    axisX->setRange(0, 20);
    axisY->setRange(-10, 10);

    monitorChart->legend()->setBackgroundVisible(false);
    monitorChart->legend()->setLabelColor(Qt::black);
    monitorChart->setAnimationOptions(QChart::SeriesAnimations);
    monitorChart->setTheme(QChart::ChartThemeBlueCerulean);
    monitorChart->setBackgroundRoundness(20);
    monitorChart->setBackgroundVisible(true);
    monitorChart->setDropShadowEnabled(true);

    initSeriesMap();
    
    hideSeries();
}

void MonitorPlot::initSeriesMap() {
    seriesMap = {
        {"pTotal(inlet)", inlet_pTotal},
        {"tTotal(inlet)", inlet_tTotal},
        {"vAxial(inlet)", inlet_vAxial},
        {"vTheta(inlet)", inlet_vTheta},
        {"pStatic(inlet)", inlet_pStatic},
        {"mDot(inlet)", inlet_mDot},
        {"pTotal(outlet)", outlet_pTotal},
        {"tTotal(outlet)", outlet_tTotal},
        {"vAxial(outlet)", outlet_vAxial},
        {"vTheta(outlet)", outlet_vTheta},
        {"pStatic(outlet)", outlet_pStatic},
        {"mDot(outlet)", outlet_mDot},
        {"pRatio", perf_pRatio},
        {"tRatio", perf_tRatio},
        {"efficiency", perf_efficiency},
        {"turning", perf_turning},
        {"qInlet", perf_qInlet},
        {"qOutlet", perf_qOutlet}
    };
}

void MonitorPlot::updateSeriesVisibility(const QStringList& selectedVariables) {
    for(auto series : seriesMap.values()) {
        series->hide();
    }
    
    for(const QString& var : selectedVariables) {
        if(seriesMap.contains(var)) {
            seriesMap[var]->show();
        }
    }
}

void MonitorPlot::updateChart(int iteration, const MonitorVariableTable& data) {
    inlet_pTotal->append(iteration, data.inlet.pTotal.last());
    inlet_tTotal->append(iteration, data.inlet.tTotal.last());
    inlet_vAxial->append(iteration, data.inlet.vAxial.last());
    inlet_vTheta->append(iteration, data.inlet.vTheta.last());
    inlet_pStatic->append(iteration, data.inlet.pStatic.last());
    inlet_mDot->append(iteration, data.inlet.mDot.last());
    
    outlet_pTotal->append(iteration, data.outlet.pTotal.last());
    outlet_tTotal->append(iteration, data.outlet.tTotal.last());
    outlet_vAxial->append(iteration, data.outlet.vAxial.last());
    outlet_vTheta->append(iteration, data.outlet.vTheta.last());
    outlet_pStatic->append(iteration, data.outlet.pStatic.last());
    outlet_mDot->append(iteration, data.outlet.mDot.last());
    
    perf_pRatio->append(iteration, data.perform.pRatio.last());
    perf_tRatio->append(iteration, data.perform.tRatio.last());
    perf_efficiency->append(iteration, data.perform.efficiency.last());
    perf_turning->append(iteration, data.perform.turning.last());
    perf_qInlet->append(iteration, data.perform.qInlet.last());
    perf_qOutlet->append(iteration, data.perform.qOutlet.last());

    if (iteration > axisX->max()) {
        axisX->setRange(0, iteration + 10);
    }
}

void MonitorPlot::onFontChanged(const QFont &font)
{
    monitorChart->legend()->setFont(font);
}

void MonitorPlot::hideSeries() {
    for(auto series : seriesMap.values()) {
        series->hide();
    }
}

void MonitorPlot::autoScale() {

}