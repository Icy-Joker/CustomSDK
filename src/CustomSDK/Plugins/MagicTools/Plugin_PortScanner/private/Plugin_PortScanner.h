#pragma once

#include <MagicToolBox/MagicTool.h>

class Plugin_PortScanner : public MagicTool
{
public:
	const char* getType() const override;
	const QIcon getIcon() const override;
	const char* getName() const override;
	const char* getDescription() const override;
	QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const override;
};
