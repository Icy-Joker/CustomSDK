#include "stdafx.h"
#include "EnumeratedDataType.h"
#include "CommonStructDefinition.h"

#include "Package.h"

EnumeratedDataType::EnumeratedDataType()
{
  this->setName("EnumeratedDataType");

  {
    // 测试
    boost::shared_ptr<SingleElement> single_element_shared_ptr = boost::make_shared<SingleElement>();
    {
      single_element_shared_ptr->data_type_name = "data_type_name";
      single_element_shared_ptr->identifier = "identifier";
      single_element_shared_ptr->default_value = "default_value";
      single_element_shared_ptr->annotation = "annotation";
    }

    this->appendMemberElement(single_element_shared_ptr);
  }
}

EnumeratedDataType::~EnumeratedDataType()
{
}

void EnumeratedDataType::appendMemberElement(const boost::shared_ptr<SingleElement>& single_element_shared_ptr)
{
  this->vector_member_elements.push_back(single_element_shared_ptr);
}

// void EnumeratedDataType::setParentPackage(const boost::weak_ptr<Package>& parent_package_weak_ptr)
// {
//   this->parent_package_weak_ptr = parent_package_weak_ptr;
// }

// boost::shared_ptr<Package> EnumeratedDataType::getParentPackage() const
// {
//   return parent_package_weak_ptr.lock();
// }
//
// const std::string& EnumeratedDataType::getEnumeratedDataTypeName() const
// {
//   return enumerated_data_type_name;
// }

// const std::string EnumeratedDataType::getParentPackageCompleteName() const
// {
//   std::string result = "";
//
//   if(boost::shared_ptr<Package> parent_package_shared_ptr = getParentPackage())
//   {
//     result = parent_package_shared_ptr->getPackageCompleteName();
//   }
//
//   return result;
// }

// const std::string EnumeratedDataType::getEnumeratedDataTypeCompleteName() const
// {
//   const std::string parent_package_complete_name = getParentPackageCompleteName();
//
//   return parent_package_complete_name.empty() ? enumerated_data_type_name : parent_package_complete_name + "::" + enumerated_data_type_name;
// }

const std::vector<boost::shared_ptr<SingleElement>>& EnumeratedDataType::getMemberElements() const
{
  return vector_member_elements;
}

std::string EnumeratedDataType::toText(const std::string& current_indent) const
{
  std::string result = "";
  std::string child_indent = current_indent;

  child_indent += "  ";
  result += current_indent + "enum " + this->getName() + "\n";
  result += current_indent + "{\n";

  result += current_indent + "};\n";

  return result;
}
