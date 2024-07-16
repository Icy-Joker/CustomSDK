#pragma once

#ifndef __PIECHART_H__
# define __PIECHART_H__

#include <QChartView>

class PieChart : public QChartView
{
  Q_OBJECT
public:
  explicit PieChart(QWidget *parent = nullptr);
  ~PieChart() override;
private:
};

#endif // !__PIECHART_H__
