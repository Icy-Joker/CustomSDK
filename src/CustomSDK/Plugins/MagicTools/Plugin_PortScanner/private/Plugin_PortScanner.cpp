#include "Plugin_PortScanner.h"

#include "PortScanner/PortScanner.h"

const char * Plugin_PortScanner::getType() const
{
	return "网络工具";
}

const QIcon Plugin_PortScanner::getIcon() const
{
	return  QIcon(":/resource/images/heart.png");
}

const char * Plugin_PortScanner::getName() const
{
	return "端口扫描器";
}

const char * Plugin_PortScanner::getDescription() const
{
	return "端口扫描器";
}

QWidget * Plugin_PortScanner::createInstance(QWidget* parent,Qt::WindowFlags flags) const
{
	PortScanner* magic_tool = new PortScanner(parent,flags);
	return magic_tool;
}

PLUGIN_EXPORT(Plugin_PortScanner)
