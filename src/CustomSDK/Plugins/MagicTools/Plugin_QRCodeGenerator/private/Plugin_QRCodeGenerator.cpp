#include "Plugin_QRCodeGenerator.h"

#include "QRCodeGenerator/QRCodeGenerator.h"

const char * Plugin_QRCodeGenerator::getType() const
{
	return "通用工具";
}

const QIcon Plugin_QRCodeGenerator::getIcon() const
{
	return  QIcon(":/resource/images/heart.png");
}

const char * Plugin_QRCodeGenerator::getName() const
{
	return "二维码生成器";
}

const char * Plugin_QRCodeGenerator::getDescription() const
{
	return "二维码生成器";
}

QWidget * Plugin_QRCodeGenerator::createInstance(QWidget* parent,Qt::WindowFlags flags) const
{
	QRCodeGenerator* magic_tool = new QRCodeGenerator(parent,flags);
	return magic_tool;
}

PLUGIN_EXPORT(Plugin_QRCodeGenerator)
