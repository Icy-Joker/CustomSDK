#pragma once

#ifndef __ENUMERATEDDATATYPE_H__
#define __ENUMERATEDDATATYPE_H__

#include "AbstractNamespace.h"

#include <list>

class Package;

struct EnumerationMember
{
  std::string annotation;
  std::string data_type_name;
  std::string default_value;
  std::string identifier;
};

class EnumerationType : public AbstractNamespace
{
public:
  EnumerationType();
  ~EnumerationType() override;
public:
  void appendEnumerationMember(const boost::shared_ptr<EnumerationMember>&);
  const std::list<boost::shared_ptr<EnumerationMember>>& getEnumerationMembers() const;
  void setEnumerationMembers(const std::list<boost::shared_ptr<EnumerationMember>>&);
public:
  std::string toText(const std::string& current_indent = "") const override;
private:
  std::list<boost::shared_ptr<EnumerationMember>> enumeration_members;
};

#endif //!__ENUMERATEDDATATYPE_H__
