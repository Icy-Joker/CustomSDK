#include "stdafx.h"

#include "BarChart.h"

#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>

BarChart::BarChart(QWidget* parent /*= nullptr*/):
  QChartView(parent)
{
  this->setRenderHint(QPainter::Antialiasing);

  if(QChart* chart = new QChart())
  {
    if(QBarSeries* series = new QBarSeries())
    {
      {
        QBarSet* set0 = new QBarSet("A");
        *set0 << 1 << 2 << 3 << 4 << 5 << 6;
        series->append(set0);
      }
      {
        QBarSet* set1 = new QBarSet("B");
        *set1 << 5 << 0 << 0 << 4 << 0 << 7;
        series->append(set1);
      }
      {
        QBarSet* set2 = new QBarSet("C");
        *set2 << 3 << 5 << 8 << 13 << 8 << 5;
        series->append(set2);
      }
      {
        QBarSet* set3 = new QBarSet("D");
        *set3 << 5 << 6 << 7 << 3 << 4 << 5;
        series->append(set3);
      }
      {
        QBarSet* set4 = new QBarSet("E");
        *set4 << 9 << 7 << 5 << 3 << 1 << 2;
        series->append(set4);
      }

      chart->addSeries(series);

      if(QBarCategoryAxis* axisX = new QBarCategoryAxis())
      {
        axisX->append(QStringList() << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun");//数目要和QBarSet里面的数据个数相同
        chart->addAxis(axisX,Qt::AlignBottom);
        series->attachAxis(axisX);
      }

      if(QValueAxis* axisY = new QValueAxis())
      {
        axisY->setRange(0,15);
        chart->addAxis(axisY,Qt::AlignLeft);
        series->attachAxis(axisY);
      }
    }

    chart->setTitle(QString::fromUtf8("简单条形图示例"));
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    this->setChart(chart);
  }
}

BarChart::~BarChart()
{
}
