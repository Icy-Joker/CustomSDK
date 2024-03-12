#include "stdafx.h"

#include "DataTypeDefinitions.h"

NamespaceDefinition::NamespaceDefinition(const std::string& name):
  name(name)
{
}

NamespaceDefinition::~NamespaceDefinition()
{
}

const std::string& NamespaceDefinition::getName() const
{
  return this->name;
}

PackageDefinition::PackageDefinition(const std::string& name):
  NamespaceDefinition(name)
{
}

PackageDefinition::~PackageDefinition()
{
}

ComplexDatatypeDefinition::ComplexDatatypeDefinition(const std::string& name):
  NamespaceDefinition(name)
{
}

ComplexDatatypeDefinition::~ComplexDatatypeDefinition()
{
}

boost::shared_ptr<PackageDefinition> ComplexDatatypeDefinition::getPackage() const
{
  return this->package_weak_ptr.lock();
}

EnumerationDefinition::EnumerationDefinition(const std::string& name):
  ComplexDatatypeDefinition(name)
{
}

EnumerationDefinition::~EnumerationDefinition()
{
}

StructureDefinition::StructureDefinition(const std::string& name):
  ComplexDatatypeDefinition(name)
{
}

StructureDefinition::~StructureDefinition()
{
}