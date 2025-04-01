#pragma once

#ifndef __PACKAGE_H__
#define __PACKAGE_H__

#include "AbstractNamespace.h"

class EnumerationType;
class StructureType;

class Package : public AbstractNamespace
{
public:
  Package();
  ~Package() override;
public:
  void appendEnumerationType(const boost::weak_ptr<EnumerationType>&);
  //获取直接包含的枚举类型
  const std::vector<boost::weak_ptr<EnumerationType>>& getEnumerationType() const;

  void appendStructureType(const boost::weak_ptr<StructureType>&);
  //获取直接包含的结构体类型
  const std::vector<boost::weak_ptr<StructureType>>& getStructureType() const;

  void appendPackage(const boost::weak_ptr<Package>&);
  //获取直接包含的子包空间
  const std::vector<boost::weak_ptr<Package>>& getChildPackage() const;
public:
  //获取后代枚举
  std::vector<boost::weak_ptr<EnumerationType>> collectEnumerationType() const;
  //获取后代结构体
  std::vector<boost::weak_ptr<StructureType>> collectStructureType() const;
  //获取后代包空间
  std::vector<boost::weak_ptr<Package>> collectPackage() const;

  //std::vector<boost::weak_ptr<Package>> getAvailablePackage() const;
  //std::vector<boost::weak_ptr<EnumerationType>> getAvailableEnumerationType() const;
  //std::vector<boost::weak_ptr<StructureType>> getAvailableStructureType() const;
public:
  std::string toText(const std::string& current_indent = "") const override;
private:
  std::vector<boost::weak_ptr<EnumerationType>> vector_enumerated_data_type;
  std::vector<boost::weak_ptr<StructureType>> vector_structured_data_type;
  std::vector<boost::weak_ptr<Package>> vector_package;
  std::vector<boost::weak_ptr<AbstractNamespace>> vector_namespace;
};

#endif //!__PACKAGE_H__
