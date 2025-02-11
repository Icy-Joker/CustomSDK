#include "stdafx.h"

#include "AbstractNamespace.h"

#include "Package.h"

AbstractNamespace::~AbstractNamespace()
{
}

void AbstractNamespace::setParentNamespace(boost::shared_ptr<AbstractNamespace> parent_package_shared_ptr)
{
  this->parent_namespace_weak_ptr = parent_package_shared_ptr;
}

boost::shared_ptr<AbstractNamespace> AbstractNamespace::getParentNamespace() const
{
  return this->parent_namespace_weak_ptr.lock();
}

std::string AbstractNamespace::getParentNamespaceCompleteName() const
{
  std::string result;

  if(auto parent_package_shared_ptr = getParentNamespace())
  {
    result = parent_package_shared_ptr->getCompleteName();
  }

  return result;
}

std::string AbstractNamespace::getCompleteName() const
{
  const std::string parent_package_complete_name = getParentNamespaceCompleteName();

  return parent_package_complete_name.empty() ? this->getName() : parent_package_complete_name + "::" + this->getName();
}
