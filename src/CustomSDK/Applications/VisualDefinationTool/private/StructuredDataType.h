#pragma once

#ifndef __STRUCTUREDDATATYPE_H__
#define __STRUCTUREDDATATYPE_H__

class Package;
struct SingleElement;

class StructuredDataType
{
public:
  StructuredDataType();
public:
  void setParentPackage(const boost::weak_ptr<Package>&);
  boost::shared_ptr<Package> getParentPackage()const;

  const std::string& getStructuredDataTypeName()const;
  const std::string getParentPackageCompleteName()const;
  const std::string getStructuredDataTypeCompleteName()const;

  boost::shared_ptr<StructuredDataType> getParentStructuredDataType()const;
  const std::vector<boost::shared_ptr<SingleElement>>& getMemberElements()const; 
  const std::vector<boost::shared_ptr<SingleElement>>& getCompleteMemberElements()const; 
public:
  std::string toText(const std::string& current_indent="")const;
private:
  boost::weak_ptr<Package> parent_package_weak_ptr;
  
  std::string structured_data_type_name;
  std::string annotation;

  boost::weak_ptr<StructuredDataType> parent_structured_data_type_weak_ptr;

  std::vector<boost::shared_ptr<SingleElement>> vector_member_elements; 
};

#endif //!__STRUCTUREDDATATYPE_H__
