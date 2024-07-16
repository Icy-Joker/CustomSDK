#pragma once

#ifndef __STACKEDBARCHART_H__
# define __STACKEDBARCHART_H__

#include <QChartView>

class StackedBarChart : public QChartView
{
  Q_OBJECT
public:
  explicit StackedBarChart(QWidget *parent = nullptr);
  ~StackedBarChart() override;
private:
};

#endif // !__STACKEDBARCHART_H__
