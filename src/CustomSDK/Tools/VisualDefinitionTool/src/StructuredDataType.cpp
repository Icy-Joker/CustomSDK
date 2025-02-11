#include "stdafx.h"
#include "StructuredDataType.h"

#include "CommonStructDefinition.h"
#include "Package.h"

StructuredDataType::StructuredDataType()
{
  this->setName("StructuredDataType");
}

StructuredDataType::~StructuredDataType()
{
}

// void StructuredDataType::setParentPackage(const boost::weak_ptr<Package>& parent_package_weak_ptr)
// {
//   this->parent_package_weak_ptr = parent_package_weak_ptr;
// }
//
// const boost::shared_ptr<Package>& StructuredDataType::getParentPackage() const
// {
//   return std::move(this->parent_package_weak_ptr.lock());
// }
//
// const std::string& StructuredDataType::getStructuredDataTypeName() const
// {
//   return structured_data_type_name;
// }
//
// const std::string StructuredDataType::getParentPackageCompleteName() const
// {
//   std::string result;
//
//   if(boost::shared_ptr<Package> parent_package_shared_ptr = getParentPackage())
//   {
//     result = parent_package_shared_ptr->getPackageCompleteName();
//   }
//
//   return std::cref(result);
// }
//
// const std::string StructuredDataType::getStructuredDataTypeCompleteName() const
// {
//   std::string result;
//
//   const std::string parent_package_complete_name = getParentPackageCompleteName();
//   result = parent_package_complete_name.empty() ? structured_data_type_name : parent_package_complete_name + "::" + structured_data_type_name;
//
//   return std::cref(result);
// }

const boost::shared_ptr<StructuredDataType> StructuredDataType::getParentStructuredDataType() const
{
  return std::move(parent_structured_data_type_weak_ptr.lock());
}

const std::vector<boost::shared_ptr<SingleElement>>& StructuredDataType::getMemberElements() const
{
  return vector_member_elements;
}

const std::vector<boost::shared_ptr<SingleElement>> StructuredDataType::getCompleteMemberElements() const
{
  return std::vector<boost::shared_ptr<SingleElement>>();
}

std::string StructuredDataType::toText(const std::string& current_indent) const
{
  std::string result;
  std::string child_indent = current_indent;

  child_indent += "  ";
  result += current_indent + "struct " + this->getName() + "\n";
  result += current_indent + "{\n";

  result += current_indent + "};\n";

  return result;
}
