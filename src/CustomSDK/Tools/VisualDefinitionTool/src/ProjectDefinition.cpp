#include "stdafx.h"

#include "ProjectDefinition.h"
#include "IDLFileDefinition.h"
#include "Package.h"
#include "StructureType.h"
#include "EnumerationType.h"

#include <boost/filesystem.hpp>

#include <fstream>
#include <iostream>

void ProjectDefinition::appendEnumerationType(const boost::shared_ptr<EnumerationType>& enumerated_data_type_shared_ptr,const boost::shared_ptr<Package>& parent_package_shared_ptr)
{
  if(enumerated_data_type_shared_ptr)
  {
    // 记录枚举类型定义
    this->enumerated_data_type_definitions.emplace_back(enumerated_data_type_shared_ptr);

    if(parent_package_shared_ptr)
    {
      //
      parent_package_shared_ptr->appendEnumerationType(enumerated_data_type_shared_ptr);
    }

    // 设置枚举类型的父命名空间
    enumerated_data_type_shared_ptr->setParentNamespace(parent_package_shared_ptr);
  }
}

void ProjectDefinition::removeEnumerationType(const boost::shared_ptr<EnumerationType>& enumerated_data_type_shared_ptr,const boost::shared_ptr<Package>& parent_package_shared_ptr)
{
  if(enumerated_data_type_shared_ptr)
  {
    this->enumerated_data_type_definitions.remove(enumerated_data_type_shared_ptr);
  }
}

std::list<boost::shared_ptr<EnumerationType>> ProjectDefinition::getAllEnumerationTypeDefinitions(const boost::shared_ptr<Package>& parent_package_shared_ptr) const
{
  return this->enumerated_data_type_definitions;
}

void ProjectDefinition::appendStructureType(const boost::shared_ptr<StructureType>& structured_data_type_shared_ptr,const boost::shared_ptr<Package>& parent_package_shared_ptr)
{
  if(structured_data_type_shared_ptr)
  {
    this->structured_data_type_definitions.emplace_back(structured_data_type_shared_ptr);
  }
}

void ProjectDefinition::removeStructureType(const boost::shared_ptr<StructureType>& structured_data_type_shared_ptr,const boost::shared_ptr<Package>& parent_package_shared_ptr)
{
  if(structured_data_type_shared_ptr)
  {
    this->structured_data_type_definitions.remove(structured_data_type_shared_ptr);
  }
}

std::list<boost::shared_ptr<StructureType>> ProjectDefinition::getAllStructureTypeDefinitions(const boost::shared_ptr<Package>& parent_package_shared_ptr) const
{
  return this->structured_data_type_definitions;
}

void ProjectDefinition::appendPackage(const boost::shared_ptr<Package>& package_shared_ptr,const boost::shared_ptr<Package>& parent_package_shared_ptr)
{
  if(package_shared_ptr)
  {
    this->package_definitions.emplace_back(package_shared_ptr);
  }
}

void ProjectDefinition::removePackage(const boost::shared_ptr<Package>& package_shared_ptr,const boost::shared_ptr<Package>& parent_package_shared_ptr)
{
  if(package_shared_ptr)
  {
    this->package_definitions.remove(package_shared_ptr);
  }
}

std::list<boost::shared_ptr<Package>> ProjectDefinition::getAllPackageDefinitions(const boost::shared_ptr<Package>& parent_package_shared_ptr) const
{
  return this->package_definitions;
}

boost::shared_ptr<IDLFileDefinition> ProjectDefinition::loadIDLFile(const std::string& idl_file_absolute_path) const
{
  boost::shared_ptr<IDLFileDefinition> idl_file_shared_ptr = nullptr;

  if(!this->idl_file_definitions.count(idl_file_absolute_path))
  {
    idl_file_shared_ptr = boost::make_shared<IDLFileDefinition>();
    idl_file_shared_ptr->setFilePath(idl_file_absolute_path);
  }
  else
  {
    idl_file_shared_ptr = this->idl_file_definitions.at(idl_file_absolute_path);
  }

  return idl_file_shared_ptr;
}

void ProjectDefinition::appendIDLFile(const boost::shared_ptr<IDLFileDefinition>& idl_file_shared_ptr)
{
  if(idl_file_shared_ptr)
  {
    const std::string& idl_file_absolute_path = idl_file_shared_ptr->getFilePath();
    if(!this->idl_file_definitions.count(idl_file_absolute_path))
    {
      this->idl_file_definitions.insert(std::make_pair(idl_file_absolute_path,idl_file_shared_ptr));
    }
  }
}

void ProjectDefinition::removeIDLFile(const std::string& idl_file_absolute_path)
{
  this->idl_file_definitions.erase(idl_file_absolute_path);
}

const std::map<std::string,boost::shared_ptr<IDLFileDefinition>>& ProjectDefinition::getAllIDLFileDefinitions() const
{
  return this->idl_file_definitions;
}

void ProjectDefinition::setMainIDLFile(const std::string& idl_file_absolute_path)
{
  boost::shared_ptr<IDLFileDefinition> idl_file_shared_ptr = nullptr;

  {
    if(this->idl_file_definitions.count(idl_file_absolute_path))
    {
      idl_file_shared_ptr = this->idl_file_definitions.at(idl_file_absolute_path);
    }
    else
    {
      idl_file_shared_ptr = this->loadIDLFile(idl_file_absolute_path);
    }
  }

  this->main_idl_file_weak_ptr = idl_file_shared_ptr;
}

boost::shared_ptr<IDLFileDefinition> ProjectDefinition::getMainIDLFile() const
{
  boost::shared_ptr<IDLFileDefinition> main_idl_file_shared_ptr = nullptr;

  {
    main_idl_file_shared_ptr = main_idl_file_weak_ptr.lock();
  }

  return main_idl_file_shared_ptr;
}

bool ProjectDefinition::doSave() const
{
  bool result = false;

  if(boost::shared_ptr<IDLFileDefinition> idl_file_shared_ptr = this->getMainIDLFile())
  {
    result = this->doSaveAs(idl_file_shared_ptr->getFilePath());
  }

  return result;
}

bool ProjectDefinition::doSaveAs(const std::string& file_path_string) const
{
  bool result = false;

  if(boost::shared_ptr<IDLFileDefinition> idl_file_shared_ptr = this->getMainIDLFile())
  {
    try
    {
      const boost::filesystem::path file_path(file_path_string);

      const boost::filesystem::path parent_directory = file_path.parent_path();
      if(!boost::filesystem::exists(parent_directory))
      {
        boost::filesystem::create_directories(parent_directory);
      }

      std::ofstream file_output_stream(file_path.string(),std::ios::binary);
      if(file_output_stream.is_open())
      {
        file_output_stream << idl_file_shared_ptr->toText();

        result = true;
      }
    }
    catch(const boost::filesystem::filesystem_error&)
    {
    }
  }

  return result;
}
