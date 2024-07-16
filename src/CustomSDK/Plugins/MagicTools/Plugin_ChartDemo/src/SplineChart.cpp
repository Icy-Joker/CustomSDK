#include "stdafx.h"

#include "SplineChart.h"

#include <QSplineSeries>

SplineChart::SplineChart(QWidget* parent /*= nullptr*/):
  QChartView(parent)
{
  this->setRenderHint(QPainter::Antialiasing);

  if(QChart* chart = new QChart())
  {
    if(QSplineSeries* series = new QSplineSeries())
    {
      series->append(0,6);
      series->append(2,4);
      series->append(3,8);
      series->append(7,4);
      series->append(10,5);

      series->setName("spline");

      chart->addSeries(series);
    }

    chart->setTitle(QString::fromUtf8("简单曲线图示例"));
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0,10);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    this->setChart(chart);
  }
}

SplineChart::~SplineChart()
{
}
