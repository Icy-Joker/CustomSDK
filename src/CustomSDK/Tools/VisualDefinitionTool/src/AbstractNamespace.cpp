#include "stdafx.h"

#include "AbstractNamespace.h"

void AbstractNamespace::setParentNamespace(const boost::shared_ptr<AbstractNamespace>& parent_package_shared_ptr)
{
  this->parent_namespace_weak_ptr = parent_package_shared_ptr;
}

boost::shared_ptr<AbstractNamespace> AbstractNamespace::getParentNamespace() const
{
  return this->parent_namespace_weak_ptr.lock();
}

std::string AbstractNamespace::getParentNamespaceCompleteName() const// NOLINT(misc-no-recursion)
{
  std::string result;

  if(auto parent_package_shared_ptr = getParentNamespace())
  {
    result = parent_package_shared_ptr->getCompleteName();
  }

  return result;
}

std::string AbstractNamespace::getCompleteName() const// NOLINT(misc-no-recursion)
{
  const std::string parent_package_complete_name = getParentNamespaceCompleteName();

  return parent_package_complete_name.empty() ? this->getName() : parent_package_complete_name + "::" + this->getName();
}
