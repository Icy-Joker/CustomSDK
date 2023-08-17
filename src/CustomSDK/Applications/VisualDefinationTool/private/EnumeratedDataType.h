#pragma once

#ifndef __ENUMERATEDDATATYPE_H__
#define __ENUMERATEDDATATYPE_H__

class Package;
struct SingleElement;

class EnumeratedDataType
{
public:
  EnumeratedDataType();
public:
  void setParentPackage(const boost::weak_ptr<Package>&);
  boost::shared_ptr<Package> getParentPackage()const;

  const std::string& getEnumeratedDataTypeName()const;
  const std::string getParentPackageCompleteName()const;
  const std::string getEnumeratedDataTypeCompleteName()const;

  const std::vector<boost::shared_ptr<SingleElement>>& getMemberElements()const;
public:
  std::string toText(const std::string& current_indent="")const;
private:
  boost::weak_ptr<Package> parent_package_weak_ptr;
  
  std::string enumerated_data_type_name;
  std::string annotation;

  std::vector<boost::shared_ptr<SingleElement>> vector_member_elements;
};

#endif //!__ENUMERATEDDATATYPE_H__
