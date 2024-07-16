#include "stdafx.h"

#include "LineChart.h"

#include <QLineSeries>

LineChart::LineChart(QWidget* parent /*= nullptr*/):
  QChartView(parent)
{
  this->setRenderHint(QPainter::Antialiasing);

  if(QChart* chart = new QChart())
  {
    if(QLineSeries* series = new QLineSeries())
    {
      series->append(0,6);
      series->append(2,4);
      series->append(3,8);
      series->append(7,4);
      series->append(10,5);

      series->setName(QString::fromUtf8("折线1"));

      chart->addSeries(series);
    }

    chart->setTitle(QString::fromUtf8("简单折线图示例"));
    chart->createDefaultAxes();

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    this->setChart(chart);
  }
}

LineChart::~LineChart()
{
}
