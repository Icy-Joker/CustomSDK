#pragma once

#ifndef AbstractNamespace_H
# define AbstractNamespace_H

#include <AbstractDefinition.h>

class AbstractNamespace : public AbstractDefinition
{
public:
  ~AbstractNamespace() override = default;
public:
  void setParentNamespace(const boost::shared_ptr<AbstractNamespace>&);
  boost::shared_ptr<AbstractNamespace> getParentNamespace() const;

  std::string getParentNamespaceCompleteName() const;
public:
  std::string getCompleteName() const override;
private:
  boost::weak_ptr<AbstractNamespace> parent_namespace_weak_ptr;
};

#endif // !AbstractNamespace_H
