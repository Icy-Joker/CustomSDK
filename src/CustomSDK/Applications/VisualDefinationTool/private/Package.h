#pragma once

#ifndef __PACKAGE_H__
#define __PACKAGE_H__

struct EnumeratedDataType;
struct StructuredDataType;

class Package
{
public:
  Package();
public:
  void setParentPackage(const boost::shared_ptr<Package>&);
  boost::shared_ptr<Package> getParentPackage()const;

  const std::string& getPackageName()const;
  const std::string getParentPackageCompleteName()const;
  const std::string getPackageCompleteName()const;

  void appendEnumeratedDataType(boost::weak_ptr<EnumeratedDataType>);
  void appendStructuredDataType(boost::weak_ptr<StructuredDataType>);
  void appendPackage(boost::weak_ptr<Package>);

  //获取直接包含的枚举类型
  const std::vector<boost::weak_ptr<EnumeratedDataType>>& getEnumeratedDataType()const;
  //获取直接包含的结构体类型
  const std::vector<boost::weak_ptr<StructuredDataType>>& getStructuredDataType()const;
  //获取直接包含的子包空间
  const std::vector<boost::weak_ptr<Package>>& getChildPackage()const;
  
  //获取后代包空间
  const std::vector<boost::weak_ptr<Package>> collectPackage()const;
  //获取后代枚举
  const std::vector<boost::weak_ptr<EnumeratedDataType>> collectEnumeratedDataType()const;
  //获取后代结构体
  const std::vector<boost::weak_ptr<StructuredDataType>> collectStructuredDataType()const;

  const std::vector<boost::weak_ptr<Package>> getAvailablePackage()const;
  const std::vector<boost::weak_ptr<EnumeratedDataType>> getAvailableEnumeratedDataType()const;
  const std::vector<boost::weak_ptr<StructuredDataType>> getAvailableStructuredDataType()const;
public:
  std::string toText(const std::string& current_indent="")const;
private:
  boost::weak_ptr<Package> parent_package_weak_ptr;
  
  std::string package_name;
  std::string annotation;

  std::vector<boost::weak_ptr<StructuredDataType>> vector_structured_data_type;
  std::vector<boost::weak_ptr<EnumeratedDataType>> vector_enumerated_data_type;
  std::vector<boost::weak_ptr<Package>> vector_package;
};

#endif //!__PACKAGE_H__
