#include "stdafx.h"
#include "StructuredDataType.h"

#include "CommonStructDefinition.h"
#include <EnumeratedDataType.h>
#include "Package.h"

StructuredDataType::StructuredDataType()
{
  this->setName("StructuredDataType");

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

StructuredDataType::~StructuredDataType()
{
}

void StructuredDataType::appendMemberElement(const boost::shared_ptr<SingleElement>& single_element_shared_ptr)
{
  this->vector_member_elements.emplace_back(single_element_shared_ptr);
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

boost::shared_ptr<StructuredDataType> StructuredDataType::getParentStructuredDataType() const
{
  return parent_structured_data_type_weak_ptr.lock();
}

const std::vector<boost::shared_ptr<SingleElement>>& StructuredDataType::getMemberElements() const
{
  return vector_member_elements;
}

std::vector<boost::shared_ptr<SingleElement>> StructuredDataType::getCompleteMemberElements() const
{
  std::vector<boost::shared_ptr<SingleElement>> result;

  if(const boost::shared_ptr<StructuredDataType>& parent_structured_data_type_shared_ptr = this->getParentStructuredDataType())
  {
    //获取基结构体成员
    std::vector<boost::shared_ptr<SingleElement>> parent_vector_member_elements = parent_structured_data_type_shared_ptr->getCompleteMemberElements();
    result.insert(result.end(),parent_vector_member_elements.begin(),parent_vector_member_elements.end());
  }
  //填充当前结构体成员
  result.insert(result.end(),this->vector_member_elements.begin(),this->vector_member_elements.end());

  return result;
}

std::vector<boost::weak_ptr<EnumeratedDataType>> StructuredDataType::getAvailableEnumerationDataType() const
{
  std::vector<boost::weak_ptr<EnumeratedDataType>> result;

  if(boost::shared_ptr<Package> parent_package_shared_ptr = boost::dynamic_pointer_cast<Package>(this->getParentNamespace()))
  {
    result = parent_package_shared_ptr->getAvailableEnumeratedDataType();
  }

  return result;
}

std::vector<boost::weak_ptr<StructuredDataType>> StructuredDataType::getAvailableStructuredDataType() const
{
  std::vector<boost::weak_ptr<StructuredDataType>> result;

  if(boost::shared_ptr<Package> parent_package_shared_ptr = boost::dynamic_pointer_cast<Package>(this->getParentNamespace()))
  {
    const std::vector<boost::weak_ptr<StructuredDataType>> structure_definitions = parent_package_shared_ptr->getAvailableStructuredDataType();
    std::for_each(structure_definitions.begin(),structure_definitions.end(),[&](const boost::weak_ptr<StructuredDataType>& structured_data_type_weak_ptr_existed)
    {
      if(boost::shared_ptr<StructuredDataType> structured_data_type_shared_ptr_existed = structured_data_type_weak_ptr_existed.lock())
      {
        if(structured_data_type_shared_ptr_existed != shared_from_this() &&
          structured_data_type_shared_ptr_existed->getCompleteName() != this->getCompleteName() &&
          !structured_data_type_shared_ptr_existed->inheritFrom(shared_from_this()))
        {
          result.emplace_back(structured_data_type_weak_ptr_existed);
        }
      }
    });
  }

  return result;
}

bool StructuredDataType::inheritFrom(const boost::shared_ptr<const StructuredDataType>& structured_data_type_shared_ptr)
{
  bool result = false;

  if(const boost::shared_ptr<StructuredDataType>& parent_structured_data_type_shared_ptr = this->getParentStructuredDataType())
  {
    result = (parent_structured_data_type_shared_ptr == structured_data_type_shared_ptr) || parent_structured_data_type_shared_ptr->inheritFrom(structured_data_type_shared_ptr);
  }

  return result;
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
