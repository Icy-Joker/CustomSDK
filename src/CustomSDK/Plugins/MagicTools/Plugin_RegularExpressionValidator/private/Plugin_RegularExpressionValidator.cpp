#include "Plugin_RegularExpressionValidator.h"

#include "RegularExpressionValidator/RegularExpressionValidator.h"

const char * Plugin_RegularExpressionValidator::getType() const
{
  return "通用工具";
}

const QIcon Plugin_RegularExpressionValidator::getIcon() const
{
  return  QIcon(":/resource/images/heart.png");
}

const char * Plugin_RegularExpressionValidator::getName() const
{
  return "正则验证";
}

const char * Plugin_RegularExpressionValidator::getDescription() const
{
  return "正则验证";
}

QWidget * Plugin_RegularExpressionValidator::createInstance(QWidget* parent,Qt::WindowFlags flags) const
{
  RegularExpressionValidator* magic_tool = new RegularExpressionValidator(parent,flags);
  return magic_tool;
}

PLUGIN_EXPORT(Plugin_RegularExpressionValidator)
