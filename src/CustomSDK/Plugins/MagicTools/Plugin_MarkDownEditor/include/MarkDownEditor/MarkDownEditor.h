#pragma once

#ifndef __MARKDOWNEDITOR_H__
# define __MARKDOWNEDITOR_H__

#include <QMainWindow>

namespace Ui
{
  class MarkDownEditor;
}

class MarkDownEditor : public QMainWindow
{
public:
  Q_OBJECT
public:
  explicit MarkDownEditor(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
  ~MarkDownEditor();
private slots:
  void on_tab_SourceView_textChanged();
private:
  Ui::MarkDownEditor* ui;
};

#endif // !__MARKDOWNEDITOR_H__
