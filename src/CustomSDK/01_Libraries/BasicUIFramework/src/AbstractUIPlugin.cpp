#include "stdafx.h"

#include "AbstractUIPlugin.h"
#include "AbstractUiPluginPrivate.h"

AbstractUIPlugin::AbstractUIPlugin():
  private_ptr(new AbstractUIPluginPrivate())
{
}

AbstractUIPlugin::~AbstractUIPlugin()
{
  if(private_ptr)
  {
    delete private_ptr;
    private_ptr = nullptr;
  }
}

const std::string& AbstractUIPlugin::getType() const
{
  return private_ptr->type;
}

void AbstractUIPlugin::setType(const std::string& type)
{
  this->private_ptr->type = type;
}

const QIcon& AbstractUIPlugin::getIcon() const
{
  return private_ptr->icon;
}

void AbstractUIPlugin::setIcon(const QIcon& icon)
{
  this->private_ptr->icon = icon;
}
