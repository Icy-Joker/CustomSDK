#pragma once

#ifndef __ENUMERATEDDATATYPE_H__
#define __ENUMERATEDDATATYPE_H__

#include "AbstractNamespace.h"

class Package;
struct SingleElement;

class EnumeratedDataType : public AbstractNamespace
{
public:
  EnumeratedDataType();
  ~EnumeratedDataType() override;
public:
  const std::vector<boost::shared_ptr<SingleElement>>& getMemberElements() const;
public:
  std::string toText(const std::string& current_indent = "") const override;
private:
  std::vector<boost::shared_ptr<SingleElement>> vector_member_elements;
};

#endif //!__ENUMERATEDDATATYPE_H__
