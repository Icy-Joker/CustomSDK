#pragma once

#ifndef __VISUALDESIGNER_H__
# define __VISUALDESIGNER_H__

#include <QWidget>

namespace Ui
{
  class VisualDesigner;
}
class VisualDesigner : public QWidget
{
Q_OBJECT
public:
  explicit VisualDesigner(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
  ~VisualDesigner();
private:
  void doLoadFile(const std::string& file_path);
private:
  Ui::VisualDesigner* ui;
};

#endif // !__VISUALDESIGNER_H__
