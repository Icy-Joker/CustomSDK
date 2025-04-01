#pragma once

#ifndef STRUCTURE_DATATYPE_H_
#define STRUCTURE_DATATYPE_H_

#include "AbstractNamespace.h"

#include <boost/smart_ptr/enable_shared_from_this.hpp>

#include <list>

class EnumerationType;

struct StructureMember
{
  std::string identifier;
  std::string data_type_name;
  std::string default_value;
  bool repeatable;
  std::string annotation;
};

class StructureType : public AbstractNamespace,public boost::enable_shared_from_this<StructureType>
{
public:
  StructureType();
  ~StructureType() override;
public:
  void appendMemberElement(const boost::shared_ptr<StructureMember>&);

  boost::shared_ptr<StructureType> getParentStructureType() const;
  const std::list<boost::shared_ptr<StructureMember>>& getMemberElements() const;
  std::vector<boost::shared_ptr<StructureMember>> getCompleteMemberElements() const;
public:
  // std::vector<boost::weak_ptr<EnumerationType>> getAvailableEnumerationDataType() const;
  // std::vector<boost::weak_ptr<StructureType>> getAvailableStructureType() const;
public:
  bool inheritFrom(const boost::shared_ptr<const StructureType>&) const;
public:
  std::string toText(const std::string& current_indent = "") const override;
private:
  boost::weak_ptr<StructureType> parent_structured_data_type_weak_ptr;

  std::list<boost::shared_ptr<StructureMember>> structure_members;
};

#endif //!STRUCTURE_DATATYPE_H_
