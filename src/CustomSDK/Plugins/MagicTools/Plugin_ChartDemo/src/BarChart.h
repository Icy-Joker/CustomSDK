#pragma once

#ifndef __BARCHART_H__
# define __BARCHART_H__

#include <QChartView>

class BarChart : public QChartView
{
  Q_OBJECT
public:
  explicit BarChart(QWidget *parent = nullptr);
  ~BarChart() override;
private:
};

#endif // !__BARCHART_H__
