#include "stdafx.h"

#include "CommonFramework/AbstractPlugin.h"

#include "AbstractPluginPrivate.h"

AbstractPlugin::AbstractPlugin():
  private_ptr(new AbstractPluginPrivate())
{
}

AbstractPlugin::~AbstractPlugin()
{
  if(private_ptr)
  {
    delete private_ptr;
    private_ptr = nullptr;
  }
}

const std::string& AbstractPlugin::getName() const
{
  return private_ptr->name;
}

void AbstractPlugin::setName(const std::string& name)
{
  private_ptr->name = name;
}

const std::string& AbstractPlugin::getDescription() const
{
  return private_ptr->description;
}

void AbstractPlugin::setDescription(const std::string& description)
{
  private_ptr->description = description;
}
