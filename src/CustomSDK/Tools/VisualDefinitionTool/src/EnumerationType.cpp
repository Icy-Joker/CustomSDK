#include "stdafx.h"
#include "EnumerationType.h"

#include "Package.h"

EnumerationType::EnumerationType()
{
  this->setName("EnumerationType");
}

EnumerationType::~EnumerationType()
{
}

void EnumerationType::appendEnumerationMember(const boost::shared_ptr<EnumerationMember>& single_element_shared_ptr)
{
  this->enumeration_members.push_back(single_element_shared_ptr);
}

const std::list<boost::shared_ptr<EnumerationMember>>& EnumerationType::getEnumerationMembers() const
{
  return this->enumeration_members;
}

void EnumerationType::setEnumerationMembers(const std::list<boost::shared_ptr<EnumerationMember>>& enumeration_members)
{
  this->enumeration_members = enumeration_members;
}

std::string EnumerationType::toText(const std::string& current_indent) const
{
  std::string result = "";
  std::string child_indent = current_indent;

  child_indent += "  ";
  result += current_indent + "enum " + this->getName() + "\n";
  result += current_indent + "{\n";

  result += current_indent + "};\n";

  return result;
}
