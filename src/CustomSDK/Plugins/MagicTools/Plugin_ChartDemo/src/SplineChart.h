#pragma once

#ifndef __SPLINECHART_H__
# define __SPLINECHART_H__

#include <QChartView>

class SplineChart : public QChartView
{
  Q_OBJECT
public:
  explicit SplineChart(QWidget *parent = nullptr);
  ~SplineChart() override;
private:
};

#endif // !__SPLINECHART_H__
