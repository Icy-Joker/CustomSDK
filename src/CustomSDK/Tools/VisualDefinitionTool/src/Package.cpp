#include "stdafx.h"
#include "Package.h"

#include "EnumerationType.h"
#include "StructureType.h"

Package::Package()
{
  this->setName("NewPackage");
}

Package::~Package()
{
}

void Package::appendEnumerationType(const boost::weak_ptr<EnumerationType>& enumerated_data_type_weak_ptr)
{
  this->vector_enumerated_data_type.emplace_back(enumerated_data_type_weak_ptr);

  this->vector_namespace.emplace_back(enumerated_data_type_weak_ptr);
}

const std::vector<boost::weak_ptr<EnumerationType>>& Package::getEnumerationType() const
{
  return vector_enumerated_data_type;
}

void Package::appendStructureType(const boost::weak_ptr<StructureType>& structured_data_type_weak_ptr)
{
  this->vector_structured_data_type.emplace_back(structured_data_type_weak_ptr);

  this->vector_namespace.emplace_back(structured_data_type_weak_ptr);
}

const std::vector<boost::weak_ptr<StructureType>>& Package::getStructureType() const
{
  return vector_structured_data_type;
}

void Package::appendPackage(const boost::weak_ptr<Package>& package_weak_ptr)
{
  this->vector_package.emplace_back(package_weak_ptr);

  this->vector_namespace.emplace_back(package_weak_ptr);
}

const std::vector<boost::weak_ptr<Package>>& Package::getChildPackage() const
{
  return vector_package;
}

//获取后代枚举
std::vector<boost::weak_ptr<EnumerationType>> Package::collectEnumerationType() const
{
  std::vector<boost::weak_ptr<EnumerationType>> vector_collected_enumerated_data_type = vector_enumerated_data_type;
  std::for_each(vector_package.begin(),vector_package.end(),[&](const boost::weak_ptr<Package>& package_weak_ptr_existed)
  {
    if(boost::shared_ptr<Package> package_shared_ptr_existed = package_weak_ptr_existed.lock())
    {
      std::vector<boost::weak_ptr<EnumerationType>> temp_vector_collected_enumerated_data_type = package_shared_ptr_existed->collectEnumerationType();

      vector_collected_enumerated_data_type.insert(vector_collected_enumerated_data_type.end(),temp_vector_collected_enumerated_data_type.begin(),temp_vector_collected_enumerated_data_type.end());
    }
  });

  return vector_collected_enumerated_data_type;
}

//获取后代结构体
std::vector<boost::weak_ptr<StructureType>> Package::collectStructureType() const
{
  std::vector<boost::weak_ptr<StructureType>> vector_collected_structured_data_type = vector_structured_data_type;
  std::for_each(vector_package.begin(),vector_package.end(),[&](const boost::weak_ptr<Package>& package_weak_ptr_existed)
  {
    if(boost::shared_ptr<Package> package_shared_ptr_existed = package_weak_ptr_existed.lock())
    {
      std::vector<boost::weak_ptr<StructureType>> temp_vector_collected_structured_data_type = package_shared_ptr_existed->collectStructureType();

      vector_collected_structured_data_type.insert(vector_collected_structured_data_type.end(),temp_vector_collected_structured_data_type.begin(),temp_vector_collected_structured_data_type.end());
    }
  });

  return vector_collected_structured_data_type;
}

//获取后代包空间
std::vector<boost::weak_ptr<Package>> Package::collectPackage() const
{
  std::vector<boost::weak_ptr<Package>> vector_collected_package = vector_package;
  std::for_each(vector_package.begin(),vector_package.end(),[&](const boost::weak_ptr<Package>& package_weak_ptr_existed)
  {
    if(boost::shared_ptr<Package> package_shared_ptr_existed = package_weak_ptr_existed.lock())
    {
      std::vector<boost::weak_ptr<Package>> temp_vector_collected_package = package_shared_ptr_existed->collectPackage();

      vector_collected_package.insert(vector_collected_package.end(),temp_vector_collected_package.begin(),temp_vector_collected_package.end());
    }
  });

  return vector_collected_package;
}

// std::vector<boost::weak_ptr<EnumerationType>> Package::getAvailableEnumerationType() const
// {
//   std::vector<boost::weak_ptr<EnumerationType>> vector_available_enumerated_data_type;
//
//   std::vector<boost::weak_ptr<Package>> vector_available_package = this->getAvailablePackage();
//   std::for_each(vector_available_package.begin(),vector_available_package.end(),[&](const boost::weak_ptr<Package>& package_weak_ptr_existed)
//   {
//     if(boost::shared_ptr<Package> package_shared_ptr_existed = package_weak_ptr_existed.lock())
//     {
//       std::vector<boost::weak_ptr<EnumerationType>> vector_enumerated_data_type = package_shared_ptr_existed->getEnumerationType();
//
//       vector_available_enumerated_data_type.insert(vector_available_enumerated_data_type.end(),vector_enumerated_data_type.begin(),vector_enumerated_data_type.end());
//     }
//   });
//
//   return vector_available_enumerated_data_type;
// }
//
// std::vector<boost::weak_ptr<StructureType>> Package::getAvailableStructureType() const
// {
//   std::vector<boost::weak_ptr<StructureType>> vector_available_structured_data_type;
//
//   std::vector<boost::weak_ptr<Package>> vector_available_package = this->getAvailablePackage();
//   std::for_each(vector_available_package.begin(),vector_available_package.end(),[&](const boost::weak_ptr<Package>& package_weak_ptr_existed)
//   {
//     if(boost::shared_ptr<Package> package_shared_ptr_existed = package_weak_ptr_existed.lock())
//     {
//       std::vector<boost::weak_ptr<StructureType>> vector_structured_data_type = package_shared_ptr_existed->getStructureType();
//
//       vector_available_structured_data_type.insert(vector_available_structured_data_type.end(),vector_structured_data_type.begin(),vector_structured_data_type.end());
//     }
//   });
//
//   return vector_available_structured_data_type;
// }
//
// std::vector<boost::weak_ptr<Package>> Package::getAvailablePackage() const
// {
//   std::vector<boost::weak_ptr<Package>> vector_available_package;
//   if(boost::shared_ptr<Package> parent_package_shared_ptr = boost::dynamic_pointer_cast<Package>(getParentNamespace()))
//   {
//     //添加定义在自己之前的兄弟节点
//     const std::vector<boost::weak_ptr<Package>>& vector_package = parent_package_shared_ptr->getChildPackage();
//     std::for_each(vector_package.begin(),vector_package.end(),[&](const boost::weak_ptr<Package>& package_weak_ptr_existed)
//     {
//       if(boost::shared_ptr<Package> package_shared_ptr_existed = package_weak_ptr_existed.lock())
//       {
//         //if(package_shared_ptr_existed->getName() != this->getName())
//         {
//           //添加长兄节点的所有后代节点(包空间)
//           std::vector<boost::weak_ptr<Package>> temp_vector_collected_package = package_shared_ptr_existed->collectPackage();
//           vector_available_package.insert(vector_available_package.end(),temp_vector_collected_package.begin(),temp_vector_collected_package.end());
//           //添加长兄节点
//           vector_available_package.emplace_back(package_shared_ptr_existed);
//         }
//       }
//     });
//
//     //添加父节点
//     vector_available_package.emplace_back(boost::dynamic_pointer_cast<Package>(this->getParentNamespace()));
//     //添加父节点的长兄节点
//     std::vector<boost::weak_ptr<Package>> parent_available_package = parent_package_shared_ptr->getAvailablePackage();
//     vector_available_package.insert(vector_available_package.end(),parent_available_package.begin(),parent_available_package.end());
//   }
//   return vector_available_package;
// }

std::string Package::toText(const std::string& current_indent) const
{
  std::string result;
  std::string child_indent = current_indent;

  boost::shared_ptr<Package> parent_package_shared_ptr = boost::dynamic_pointer_cast<Package>(getParentNamespace());

  if(parent_package_shared_ptr)// 存在父命名空间说明当前包不是默认的全局命名空间,才能存在包名a
  {
    child_indent += "  ";
    result += current_indent + "package " + this->getName() + "\n";
    result += current_indent + "{\n";
  }

  std::for_each(vector_namespace.begin(),vector_namespace.end(),[&](const boost::weak_ptr<AbstractNamespace>& namespace_weak_ptr_existed)
  {
    if(boost::shared_ptr<AbstractNamespace> namespace_shared_ptr_existed = namespace_weak_ptr_existed.lock())
    {
      result += namespace_shared_ptr_existed->toText(child_indent);
    }
  });

  // std::for_each(vector_enumerated_data_type.begin(),vector_enumerated_data_type.end(),[&](const boost::weak_ptr<EnumerationType> enumerated_data_type_weak_ptr_existed)
  // {
  //   if(boost::shared_ptr<EnumerationType> enumerated_data_type_shared_ptr_existed = enumerated_data_type_weak_ptr_existed.lock())
  //   {
  //     result += enumerated_data_type_shared_ptr_existed->toText(child_indent);
  //   }
  // });
  //
  // std::for_each(vector_structured_data_type.begin(),vector_structured_data_type.end(),[&](const boost::weak_ptr<StructureType> structured_data_type_weak_ptr_existed)
  // {
  //   if(boost::shared_ptr<StructureType> structured_data_type_shared_ptr_existed = structured_data_type_weak_ptr_existed.lock())
  //   {
  //     result += structured_data_type_shared_ptr_existed->toText(child_indent);
  //   }
  // });
  //
  // std::for_each(vector_package.begin(),vector_package.end(),[&](const boost::weak_ptr<Package> package_weak_ptr_existed)
  // {
  //   if(boost::shared_ptr<Package> package_shared_ptr_existed = package_weak_ptr_existed.lock())
  //   {
  //     result += package_shared_ptr_existed->toText(child_indent);
  //   }
  // });

  if(parent_package_shared_ptr)
  {
    result += current_indent + "};\n";
  }

  return result;
}
