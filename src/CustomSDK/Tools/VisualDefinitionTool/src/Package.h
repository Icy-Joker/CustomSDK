#pragma once

#ifndef __PACKAGE_H__
#define __PACKAGE_H__

#include "AbstractNamespace.h"

class EnumeratedDataType;
class StructuredDataType;

class Package : public AbstractNamespace
{
public:
  Package();
  ~Package() override;
public:
  void appendEnumeratedDataType(boost::weak_ptr<EnumeratedDataType>);
  void appendStructuredDataType(boost::weak_ptr<StructuredDataType>);
  void appendPackage(boost::weak_ptr<Package>);

  //获取直接包含的枚举类型
  const std::vector<boost::weak_ptr<EnumeratedDataType>>& getEnumeratedDataType() const;
  //获取直接包含的结构体类型
  const std::vector<boost::weak_ptr<StructuredDataType>>& getStructuredDataType() const;
  //获取直接包含的子包空间
  const std::vector<boost::weak_ptr<Package>>& getChildPackage() const;

  //获取后代枚举
  const std::vector<boost::weak_ptr<EnumeratedDataType>> collectEnumeratedDataType() const;
  //获取后代结构体
  const std::vector<boost::weak_ptr<StructuredDataType>> collectStructuredDataType() const;
  //获取后代包空间
  const std::vector<boost::weak_ptr<Package>> collectPackage() const;

  const std::vector<boost::weak_ptr<Package>> getAvailablePackage() const;
  const std::vector<boost::weak_ptr<EnumeratedDataType>> getAvailableEnumeratedDataType() const;
  const std::vector<boost::weak_ptr<StructuredDataType>> getAvailableStructuredDataType() const;
public:
  std::string getCompleteName() const override;
public:
  std::string toText(const std::string& current_indent = "") const override;
private:
  std::vector<boost::weak_ptr<EnumeratedDataType>> vector_enumerated_data_type;
  std::vector<boost::weak_ptr<StructuredDataType>> vector_structured_data_type;
  std::vector<boost::weak_ptr<Package>> vector_package;
};

#endif //!__PACKAGE_H__
