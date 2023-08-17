#pragma once

#include <QToolBox>
#include <QSystemTrayIcon>

#include <vector>

namespace Ui
{
	class MagicToolBox;
}

class MagicBox;
class MagicTool;

class MagicToolBox : public QToolBox
{
	Q_OBJECT
public:
	explicit MagicToolBox(QWidget* parent=nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
	~MagicToolBox();
private:
	void toggleStatus();
private:
	void loadPlugin(const QString&);
private:
	MagicBox * findBoxByName(const QString&);
	MagicTool* findToolByName(const QString&,const QString&);
private slots:
	void slot_action_triggered();
	void slot_magicTool_requested(MagicTool*);
	void slot_trayIcon_activated(QSystemTrayIcon::ActivationReason);
private:
	Ui::MagicToolBox* ui;

	QSystemTrayIcon* trayIcon;

	std::vector<MagicBox*> vector_magic_boxes;
};
