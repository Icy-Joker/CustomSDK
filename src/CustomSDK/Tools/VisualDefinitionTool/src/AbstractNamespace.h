#pragma once

#ifndef __ABSTRACTNAMESPACE_H__
# define __ABSTRACTNAMESPACE_H__

#include <AbstractDefinition.h>

class AbstractNamespace : public AbstractDefinition
{
public:
  ~AbstractNamespace() override;
public:
  void setParentNamespace(boost::shared_ptr<AbstractNamespace>);
  boost::shared_ptr<AbstractNamespace> getParentNamespace() const;

  std::string getParentNamespaceCompleteName() const;
public:
  std::string getCompleteName() const override;
private:
  boost::weak_ptr<AbstractNamespace> parent_namespace_weak_ptr;
};

#endif // !__ABSTRACTNAMESPACE_H__
