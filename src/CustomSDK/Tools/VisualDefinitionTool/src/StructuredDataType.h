#pragma once

#ifndef STRUCTURE_DATATYPE_H_
#define STRUCTURE_DATATYPE_H_

#include "AbstractNamespace.h"

class Package;
struct SingleElement;

class StructuredDataType : public AbstractNamespace
{
public:
  StructuredDataType();
  ~StructuredDataType() override;
public:
  const boost::shared_ptr<StructuredDataType> getParentStructuredDataType() const;
  const std::vector<boost::shared_ptr<SingleElement>>& getMemberElements() const;
  const std::vector<boost::shared_ptr<SingleElement>> getCompleteMemberElements() const;
public:
  std::string toText(const std::string& current_indent = "") const override;
private:
  boost::weak_ptr<StructuredDataType> parent_structured_data_type_weak_ptr;

  std::vector<boost::shared_ptr<SingleElement>> vector_member_elements;
};

#endif //!STRUCTURE_DATATYPE_H_
