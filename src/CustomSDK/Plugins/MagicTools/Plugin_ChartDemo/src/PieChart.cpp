#include "stdafx.h"

#include "PieChart.h"

#include <QPieSeries>

PieChart::PieChart(QWidget* parent /*= nullptr*/):
  QChartView(parent)
{
  this->setRenderHint(QPainter::Antialiasing);

  if(QChart* chart = new QChart())
  {
    if(QPieSeries* series = new QPieSeries())
    {
      series->append("Jane",1);
      series->append("Joe",2);
      series->append("Andy",3);
      series->append("Barbara",4);
      series->append("Axel",5);

      chart->addSeries(series);

      if(QPieSlice* slice = series->slices().at(1))
      {
        slice->setExploded(true);//突出显示
        slice->setLabelVisible();
        slice->setPen(QPen(Qt::darkGreen,2));
        slice->setBrush(Qt::green);
      }
    }

    chart->setTitle(QString::fromUtf8("简单饼图示例"));

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    this->setChart(chart);
  }
}

PieChart::~PieChart()
{
}
