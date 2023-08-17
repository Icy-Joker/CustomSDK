#pragma once

#include <QWidget>

#include <vector>

class MagicTool;

class MagicBox :public QWidget
{
	Q_OBJECT
public:
	explicit MagicBox(const QString& name=QString::fromLocal8Bit("Õ®”√"), QWidget* parent=nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
	~MagicBox();
public:
	const QString& getName();

	MagicTool* findToolByName(const QString&);
	const std::vector<MagicTool*>& getAllMagicTools();

	void appendTool(MagicTool*);
signals:
	void signal_magicTool_requested(MagicTool*);
private slots:
	void slot_plugin_clicked();
private:
	void initializeUI();
private:
	QString magic_box_name;
	std::vector<MagicTool*> vector_magic_tools;
};

