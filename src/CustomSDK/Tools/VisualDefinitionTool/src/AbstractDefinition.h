#pragma once

#ifndef __ABSTRACTDEFINITION_H__
# define __ABSTRACTDEFINITION_H__

class AbstractDefinition
{
public:
  virtual ~AbstractDefinition();
public:
  void setName(const std::string& name);
  virtual const std::string& getName() const;
  virtual std::string getCompleteName() const = 0;
public:
  virtual std::string toText(const std::string& current_indent = "") const = 0;
private:
  std::string name;///名称
  std::string annotation;///描述
};

#endif // !__ABSTRACTDEFINITION_H__
