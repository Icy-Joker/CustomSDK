#pragma once

#ifndef __MAGICTOOLBOX_H__
# define __MAGICTOOLBOX_H__

#include <QMainWindow>
#include <QSystemTrayIcon>

namespace Ui
{
  class MagicToolBox;
}

class MagicBox;
class MagicTool;

class MagicToolBox : public QMainWindow
{
  Q_OBJECT
public:
  explicit MagicToolBox(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
  ~MagicToolBox();
public:
  MagicBox* findBoxByName(const QString& name);
  MagicBox* createBoxByName(const QString& name);
private:
  MagicTool* doLoadPlugin(const QString& plugin_path);
  QMenu* doCreateSystemTrayMenu();
  QSystemTrayIcon* doCreateSystemTray(QIcon icon);
  void registerMagicTool(MagicTool* magic_tool);
private:
  void doLoadPlugin();
  void doCreateSystemTray();
private:
  void closeEvent(QCloseEvent* event) override;
private slots:
  void slot_listView_currentRowChanged(const QModelIndex&,const QModelIndex&);
  void slot_trayIcon_activated(QSystemTrayIcon::ActivationReason reason);
private:
  Ui::MagicToolBox* ui;
};

#endif // !__MAGICTOOLBOX_H__
