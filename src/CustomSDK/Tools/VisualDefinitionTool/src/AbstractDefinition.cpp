#include "stdafx.h"

#include "AbstractDefinition.h"

AbstractDefinition::~AbstractDefinition()
{
}

void AbstractDefinition::setName(const std::string& name)
{
  this->name = name;
}

const std::string& AbstractDefinition::getName() const
{
  return this->name;
}
