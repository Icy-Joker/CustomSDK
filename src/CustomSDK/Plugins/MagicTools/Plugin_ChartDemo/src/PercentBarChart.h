#pragma once

#ifndef __PERCENTBARCHART_H__
# define __PERCENTBARCHART_H__

#include <QChartView>

class PercentBarChart : public QChartView
{
  Q_OBJECT
public:
  explicit PercentBarChart(QWidget *parent = nullptr);
  ~PercentBarChart() override;
private:
};

#endif // !__PERCENTBARCHART_H__
