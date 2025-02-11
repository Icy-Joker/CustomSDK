#include "stdafx.h"

#include "IDLFileDefinition.h"

IDLFileDefinition::IDLFileDefinition()
{
  this->setName("IDLFileDefinition");
}

IDLFileDefinition::~IDLFileDefinition()
{
}

std::string IDLFileDefinition::getCompleteName() const
{
  return this->file_path;
}

std::string IDLFileDefinition::toText(const std::string& current_indent) const
{
  std::string result;
  std::string child_indent = current_indent;

  return result;
}
