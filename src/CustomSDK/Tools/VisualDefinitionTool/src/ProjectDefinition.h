#pragma once

#ifndef PROJECTDEFINITION_H
# define PROJECTDEFINITION_H

#include <list>
#include <map>

class EnumerationType;
class StructureType;
class Package;
class IDLFileDefinition;

class ProjectDefinition
{
public:
  //explicit ProjectDefinition();
  //~ProjectDefinition();
public:
  void appendEnumerationType(const boost::shared_ptr<EnumerationType>&,const boost::shared_ptr<Package>& parent_package_shared_ptr = nullptr);
  void removeEnumerationType(const boost::shared_ptr<EnumerationType>&,const boost::shared_ptr<Package>& parent_package_shared_ptr = nullptr);
  std::list<boost::shared_ptr<EnumerationType>> getAllEnumerationTypeDefinitions(const boost::shared_ptr<Package>& parent_package_shared_ptr = nullptr) const;

  void appendStructureType(const boost::shared_ptr<StructureType>&,const boost::shared_ptr<Package>& parent_package_shared_ptr = nullptr);
  void removeStructureType(const boost::shared_ptr<StructureType>&,const boost::shared_ptr<Package>& parent_package_shared_ptr = nullptr);
  std::list<boost::shared_ptr<StructureType>> getAllStructureTypeDefinitions(const boost::shared_ptr<Package>& parent_package_shared_ptr = nullptr) const;

  void appendPackage(const boost::shared_ptr<Package>&,const boost::shared_ptr<Package>& parent_package_shared_ptr = nullptr);
  void removePackage(const boost::shared_ptr<Package>&,const boost::shared_ptr<Package>& parent_package_shared_ptr = nullptr);
  std::list<boost::shared_ptr<Package>> getAllPackageDefinitions(const boost::shared_ptr<Package>& parent_package_shared_ptr = nullptr) const;

  boost::shared_ptr<IDLFileDefinition> loadIDLFile(const std::string&) const;
  void appendIDLFile(const boost::shared_ptr<IDLFileDefinition>&);
  void removeIDLFile(const std::string&);
  const std::map<std::string,boost::shared_ptr<IDLFileDefinition>>& getAllIDLFileDefinitions() const;

  void setMainIDLFile(const std::string&);
  boost::shared_ptr<IDLFileDefinition> getMainIDLFile() const;
public:
  bool doSave() const;
  bool doSaveAs(const std::string&) const;
private:
  std::list<boost::shared_ptr<EnumerationType>> enumerated_data_type_definitions;
  std::list<boost::shared_ptr<StructureType>> structured_data_type_definitions;
  std::list<boost::shared_ptr<Package>> package_definitions;
  std::map<std::string,boost::shared_ptr<IDLFileDefinition>> idl_file_definitions;

  boost::weak_ptr<IDLFileDefinition> main_idl_file_weak_ptr;
};

#endif // !PROJECTDEFINITION_H
