#pragma once

#ifndef __STRUCTDEFINITIONWIDGET_H__
# define __STRUCTDEFINITIONWIDGET_H__

#include <QWidget>

namespace Ui
{
  class StructDefinitionWidget;
}

class StructDefinitionWidget : public QWidget
{
  Q_OBJECT
public:
  explicit StructDefinitionWidget(QWidget *parent = nullptr);
  ~StructDefinitionWidget() override;
private:
  Ui::StructDefinitionWidget* ui;
};

#endif // !__STRUCTDEFINITIONWIDGET_H__
