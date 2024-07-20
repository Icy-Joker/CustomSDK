#include "stdafx.h"

#include "AbstractUIPlugin.h"

AbstractUIPlugin::AbstractUIPlugin():
  AbstractPlugin()
{
}

AbstractUIPlugin::~AbstractUIPlugin()
{
}

const QIcon AbstractUIPlugin::getIcon() const
{
  return this->icon;
}

void AbstractUIPlugin::setIcon(const QIcon& icon)
{
  this->icon = icon;
}
