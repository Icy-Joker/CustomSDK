#include "stdafx.h"
#include "StructureType.h"

#include "EnumerationType.h"
#include "Package.h"

StructureType::StructureType()
{
  this->setName("StructureType");
}

StructureType::~StructureType()
{
}

void StructureType::appendMemberElement(const boost::shared_ptr<StructureMember>& single_element_shared_ptr)
{
  this->structure_members.emplace_back(single_element_shared_ptr);
}

boost::shared_ptr<StructureType> StructureType::getParentStructureType() const
{
  return parent_structured_data_type_weak_ptr.lock();
}

const std::list<boost::shared_ptr<StructureMember>>& StructureType::getMemberElements() const
{
  return this->structure_members;
}

std::vector<boost::shared_ptr<StructureMember>> StructureType::getCompleteMemberElements() const
{
  std::vector<boost::shared_ptr<StructureMember>> result;

  if(const boost::shared_ptr<StructureType>& parent_structure_shared_ptr = this->getParentStructureType())
  {
    //获取基结构体成员
    std::vector<boost::shared_ptr<StructureMember>> parent_structure_members = parent_structure_shared_ptr->getCompleteMemberElements();
    result.insert(result.end(),parent_structure_members.begin(),parent_structure_members.end());
  }
  //填充当前结构体成员
  result.insert(result.end(),this->structure_members.begin(),this->structure_members.end());

  return result;
}

// std::vector<boost::weak_ptr<EnumerationType>> StructureType::getAvailableEnumerationDataType() const
// {
//   std::vector<boost::weak_ptr<EnumerationType>> result;
//
//   if(boost::shared_ptr<Package> parent_package_shared_ptr = boost::dynamic_pointer_cast<Package>(this->getParentNamespace()))
//   {
//     result = parent_package_shared_ptr->getAvailableEnumerationType();
//   }
//
//   return result;
// }
//
// std::vector<boost::weak_ptr<StructureType>> StructureType::getAvailableStructureType() const
// {
//   std::vector<boost::weak_ptr<StructureType>> result;
//
//   if(boost::shared_ptr<Package> parent_package_shared_ptr = boost::dynamic_pointer_cast<Package>(this->getParentNamespace()))
//   {
//     const std::vector<boost::weak_ptr<StructureType>> structure_definitions = parent_package_shared_ptr->getAvailableStructureType();
//     std::for_each(structure_definitions.begin(),structure_definitions.end(),[&](const boost::weak_ptr<StructureType>& structured_data_type_weak_ptr_existed)
//     {
//       if(boost::shared_ptr<StructureType> structured_data_type_shared_ptr_existed = structured_data_type_weak_ptr_existed.lock())
//       {
//         if(structured_data_type_shared_ptr_existed != shared_from_this() &&
//           structured_data_type_shared_ptr_existed->getCompleteName() != this->getCompleteName() &&
//           !structured_data_type_shared_ptr_existed->inheritFrom(shared_from_this()))
//         {
//           result.emplace_back(structured_data_type_weak_ptr_existed);
//         }
//       }
//     });
//   }
//
//   return result;
// }

bool StructureType::inheritFrom(const boost::shared_ptr<const StructureType>& structured_data_type_shared_ptr) const// NOLINT(misc-no-recursion)
{
  bool result = false;

  if(const boost::shared_ptr<StructureType>& parent_structured_data_type_shared_ptr = this->getParentStructureType())
  {
    result = (parent_structured_data_type_shared_ptr == structured_data_type_shared_ptr) || parent_structured_data_type_shared_ptr->inheritFrom(structured_data_type_shared_ptr);
  }

  return result;
}

std::string StructureType::toText(const std::string& current_indent) const
{
  std::string result;
  std::string child_indent = current_indent;

  child_indent += "  ";
  result += current_indent + "struct " + this->getName() + "\n";
  result += current_indent + "{\n";

  result += current_indent + "};\n";

  return result;
}
