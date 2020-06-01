#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QObject>
#include <QtCharts/QChartView>
#include <iostream>
QT_CHARTS_USE_NAMESPACE

class ChartView : public QChartView
{
    Q_OBJECT
public:
    explicit ChartView(QWidget* parent = 0);

public slots:
    void setValue(int value) {
        std::cout << "Test" << std::endl;
    }
};

#endif // CHARTVIEW_H