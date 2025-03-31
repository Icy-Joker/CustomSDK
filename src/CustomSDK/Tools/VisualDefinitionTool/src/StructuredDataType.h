#pragma once

#ifndef STRUCTURE_DATATYPE_H_
#define STRUCTURE_DATATYPE_H_

#include <boost/smart_ptr/enable_shared_from_this.hpp>

#include "AbstractNamespace.h"

class EnumeratedDataType;
class Package;
struct SingleElement;

class StructuredDataType : public AbstractNamespace,public boost::enable_shared_from_this<StructuredDataType>
{
public:
  StructuredDataType();
  ~StructuredDataType() override;
public:
  void appendMemberElement(const boost::shared_ptr<SingleElement>&);

  boost::shared_ptr<StructuredDataType> getParentStructuredDataType() const;
  const std::vector<boost::shared_ptr<SingleElement>>& getMemberElements() const;
  std::vector<boost::shared_ptr<SingleElement>> getCompleteMemberElements() const;
public:
  std::vector<boost::weak_ptr<EnumeratedDataType>> getAvailableEnumerationDataType() const;
  std::vector<boost::weak_ptr<StructuredDataType>> getAvailableStructuredDataType() const;
public:
  bool inheritFrom(const boost::shared_ptr<const StructuredDataType>&);
public:
  std::string toText(const std::string& current_indent = "") const override;
private:
  boost::weak_ptr<StructuredDataType> parent_structured_data_type_weak_ptr;

  std::vector<boost::shared_ptr<SingleElement>> vector_member_elements;
};

#endif //!STRUCTURE_DATATYPE_H_
