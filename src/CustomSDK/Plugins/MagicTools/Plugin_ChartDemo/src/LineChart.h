#pragma once

#ifndef __LINECHART_H__
# define __LINECHART_H__

#include <QChartView>

class LineChart : public QChartView
{
  Q_OBJECT
public:
  explicit LineChart(QWidget *parent = nullptr);
  ~LineChart() override;
private:
};

#endif // !__LINECHART_H__
