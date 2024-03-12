#pragma once

#ifndef __DATATYPEDEFINITIONS_H__
# define __DATATYPEDEFINITIONS_H__

#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <string>

class NamespaceDefinition
{
public:
  explicit NamespaceDefinition(const std::string& name);
  virtual ~NamespaceDefinition() = 0;
public:
  const std::string& getName() const;
protected:
  std::string name;
};

class PackageDefinition : public NamespaceDefinition
{
public:
  explicit PackageDefinition(const std::string& name);
  ~PackageDefinition() override;
protected:
  boost::weak_ptr<PackageDefinition> parent_package_weak_ptr;
};

class ComplexDatatypeDefinition : public NamespaceDefinition
{
public:
  struct SingleElement
  {
    std::string type_name;
    std::string identifier;
    std::string default_value;
  };
public:
  explicit ComplexDatatypeDefinition(const std::string& name);
  virtual ~ComplexDatatypeDefinition() override = 0;
public:
  boost::shared_ptr<PackageDefinition> getPackage() const;
protected:
  std::vector<SingleElement> members;
  boost::weak_ptr<PackageDefinition> package_weak_ptr;
};

class EnumerationDefinition : public ComplexDatatypeDefinition
{
public:
  explicit EnumerationDefinition(const std::string& name);
  ~EnumerationDefinition() override;
};

class StructureDefinition : public ComplexDatatypeDefinition
{
public:
  explicit StructureDefinition(const std::string& name);
  ~StructureDefinition() override;
private:
  boost::weak_ptr<ComplexDatatypeDefinition> parent_structure_weak_ptr;
};

#endif // !__DATATYPEDEFINITIONS_H__
