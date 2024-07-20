#include "stdafx.h"

#include "BasicFramework/AbstractPlugin.h"

AbstractPlugin::AbstractPlugin()
{
}

AbstractPlugin::~AbstractPlugin()
{
}

const char* AbstractPlugin::getName() const
{
  return this->name.c_str();
}

const char* AbstractPlugin::getDescription() const
{
  return this->description.c_str();
}

void AbstractPlugin::setName(const std::string& name)
{
  this->name = name;
}

void AbstractPlugin::setDescription(const std::string& description)
{
  this->description = description;
}
