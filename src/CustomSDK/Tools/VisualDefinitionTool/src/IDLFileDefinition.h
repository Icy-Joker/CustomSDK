#pragma once

#ifndef __IDLFILEDEFINITION_H__
# define __IDLFILEDEFINITION_H__

#include "AbstractDefinition.h"

class Package;

class IDLFileDefinition : public AbstractDefinition
{
public:
  explicit IDLFileDefinition();
  ~IDLFileDefinition() override;
public:
  std::string getCompleteName() const override;
public:
  std::string toText(const std::string& current_indent = "") const override;
private:
  std::string file_path;
  std::vector<std::string> file_dependence;

  boost::shared_ptr<Package> global_package_shared_ptr;
};

#endif // !__IDLFILEDEFINITION_H__
