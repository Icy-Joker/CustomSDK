#include "stdafx.h"
#include "Package.h"

#include "EnumeratedDataType.h"
#include "StructuredDataType.h"

Package::Package()
{
  this->setName("NewPackage");
}

Package::~Package()
{
}

// void Package::setParentPackage(const boost::shared_ptr<Package>& parent_package_shared_ptr)
// {
//   this->parent_package_weak_ptr=parent_package_shared_ptr;
// }

// boost::shared_ptr<Package> Package::getParentPackage()const
// {
//   return parent_package_weak_ptr.lock();
// }
//
// const std::string& Package::getPackageName()const
// {
//   return package_name;
// }
//
// const std::string Package::getParentPackageCompleteName()const
// {
//   std::string result="";
//
//   if(boost::shared_ptr<Package> parent_package_shared_ptr = getParentPackage())
//   {
//      result=parent_package_shared_ptr->getPackageCompleteName();
//   }
//
//   return result;
// }
//
// const std::string Package::getPackageCompleteName()const
// {
//   const std::string parent_package_complete_name=getParentPackageCompleteName();
//   return parent_package_complete_name.empty()?package_name : parent_package_complete_name + "::" + package_name;
// }

void Package::appendEnumeratedDataType(boost::weak_ptr<EnumeratedDataType> enumerated_data_type_weak_ptr)
{
  this->vector_enumerated_data_type.push_back(enumerated_data_type_weak_ptr);
}

void Package::appendStructuredDataType(boost::weak_ptr<StructuredDataType> structured_data_type_weak_ptr)
{
  this->vector_structured_data_type.push_back(structured_data_type_weak_ptr);
}

void Package::appendPackage(boost::weak_ptr<Package> package_weak_ptr)
{
  this->vector_package.push_back(package_weak_ptr);
}

const std::vector<boost::weak_ptr<EnumeratedDataType>>& Package::getEnumeratedDataType() const
{
  return vector_enumerated_data_type;
}

const std::vector<boost::weak_ptr<StructuredDataType>>& Package::getStructuredDataType() const
{
  return vector_structured_data_type;
}

const std::vector<boost::weak_ptr<Package>>& Package::getChildPackage() const
{
  return vector_package;
}

//获取后代枚举
const std::vector<boost::weak_ptr<EnumeratedDataType>> Package::collectEnumeratedDataType() const
{
  std::vector<boost::weak_ptr<EnumeratedDataType>> vector_collected_enumerated_data_type = vector_enumerated_data_type;
  std::for_each(vector_package.begin(),vector_package.end(),[&](boost::weak_ptr<Package> package_weak_ptr_existed)
  {
    if(boost::shared_ptr<Package> package_shared_ptr_existed = package_weak_ptr_existed.lock())
    {
      std::vector<boost::weak_ptr<EnumeratedDataType>> temp_vector_collected_enumerated_data_type = package_shared_ptr_existed->collectEnumeratedDataType();

      vector_collected_enumerated_data_type.insert(vector_collected_enumerated_data_type.end(),temp_vector_collected_enumerated_data_type.begin(),temp_vector_collected_enumerated_data_type.end());
    }
  });

  return vector_collected_enumerated_data_type;
}

//获取后代结构体
const std::vector<boost::weak_ptr<StructuredDataType>> Package::collectStructuredDataType() const
{
  std::vector<boost::weak_ptr<StructuredDataType>> vector_collected_structured_data_type = vector_structured_data_type;
  std::for_each(vector_package.begin(),vector_package.end(),[&](boost::weak_ptr<Package> package_weak_ptr_existed)
  {
    if(boost::shared_ptr<Package> package_shared_ptr_existed = package_weak_ptr_existed.lock())
    {
      std::vector<boost::weak_ptr<StructuredDataType>> temp_vector_collected_structured_data_type = package_shared_ptr_existed->collectStructuredDataType();

      vector_collected_structured_data_type.insert(vector_collected_structured_data_type.end(),temp_vector_collected_structured_data_type.begin(),temp_vector_collected_structured_data_type.end());
    }
  });

  return vector_collected_structured_data_type;
}

//获取后代包空间
const std::vector<boost::weak_ptr<Package>> Package::collectPackage() const
{
  std::vector<boost::weak_ptr<Package>> vector_collected_package = vector_package;
  std::for_each(vector_package.begin(),vector_package.end(),[&](boost::weak_ptr<Package> package_weak_ptr_existed)
  {
    if(boost::shared_ptr<Package> package_shared_ptr_existed = package_weak_ptr_existed.lock())
    {
      std::vector<boost::weak_ptr<Package>> temp_vector_collected_package = package_shared_ptr_existed->collectPackage();

      vector_collected_package.insert(vector_collected_package.end(),temp_vector_collected_package.begin(),temp_vector_collected_package.end());
    }
  });

  return vector_collected_package;
}

const std::vector<boost::weak_ptr<EnumeratedDataType>> Package::getAvailableEnumeratedDataType() const
{
  std::vector<boost::weak_ptr<EnumeratedDataType>> vector_available_enumerated_data_type;

  std::vector<boost::weak_ptr<Package>> vector_available_package = getAvailablePackage();
  std::for_each(vector_available_package.begin(),vector_available_package.end(),[&](const boost::weak_ptr<Package> package_weak_ptr_existed)
  {
    if(boost::shared_ptr<Package> package_shared_ptr_existed = package_weak_ptr_existed.lock())
    {
      std::vector<boost::weak_ptr<EnumeratedDataType>> vector_enumerated_data_type = package_shared_ptr_existed->getEnumeratedDataType();

      vector_available_enumerated_data_type.insert(vector_available_enumerated_data_type.end(),vector_enumerated_data_type.begin(),vector_enumerated_data_type.end());
    }
  });

  return vector_available_enumerated_data_type;
}

const std::vector<boost::weak_ptr<StructuredDataType>> Package::getAvailableStructuredDataType() const
{
  std::vector<boost::weak_ptr<StructuredDataType>> vector_available_structured_data_type;

  std::vector<boost::weak_ptr<Package>> vector_available_package = getAvailablePackage();
  std::for_each(vector_available_package.begin(),vector_available_package.end(),[&](const boost::weak_ptr<Package> package_weak_ptr_existed)
  {
    if(boost::shared_ptr<Package> package_shared_ptr_existed = package_weak_ptr_existed.lock())
    {
      std::vector<boost::weak_ptr<StructuredDataType>> vector_structured_data_type = package_shared_ptr_existed->getStructuredDataType();

      vector_available_structured_data_type.insert(vector_available_structured_data_type.end(),vector_structured_data_type.begin(),vector_structured_data_type.end());
    }
  });

  return vector_available_structured_data_type;
}

const std::vector<boost::weak_ptr<Package>> Package::getAvailablePackage() const
{
  std::vector<boost::weak_ptr<Package>> vector_available_package;
  if(boost::shared_ptr<Package> parent_package_shared_ptr = boost::dynamic_pointer_cast<Package>(getParentNamespace()))
  {
    //添加定义在自己之前的兄弟节点
    std::vector<boost::weak_ptr<Package>> vector_package = parent_package_shared_ptr->getChildPackage();
    for(int i = 0;i < vector_package.size();i++)
    {
      if(boost::shared_ptr<Package> temp_package_shared_ptr = vector_package[i].lock())
      {
        if(temp_package_shared_ptr->getName() == this->getName())
        {
          break;
        }
        else
        {
          //添加长兄节点的所有后代节点(包空间)
          std::vector<boost::weak_ptr<Package>> temp_vector_collected_package = temp_package_shared_ptr->collectPackage();
          vector_available_package.insert(vector_available_package.end(),temp_vector_collected_package.begin(),temp_vector_collected_package.end());
          //添加长兄节点
          vector_available_package.push_back(temp_package_shared_ptr);
        }
      }
    }
    //添加父节点
    vector_available_package.emplace_back(boost::dynamic_pointer_cast<Package>(this->getParentNamespace()));
    //添加父节点的长兄节点
    std::vector<boost::weak_ptr<Package>> parent_available_package = parent_package_shared_ptr->getAvailablePackage();
    vector_available_package.insert(vector_available_package.end(),parent_available_package.begin(),parent_available_package.end());
  }
  return vector_available_package;
}

std::string Package::getCompleteName() const
{
  std::string result = this->getName() == "全局命名空间" ? "" : AbstractNamespace::getCompleteName();

  return result;
}

std::string Package::toText(const std::string& current_indent) const
{
  std::string result;
  std::string child_indent = current_indent;

  child_indent += "  ";
  result += current_indent + "package " + this->getName() + "\n";
  result += current_indent + "{\n";

  std::for_each(vector_enumerated_data_type.begin(),vector_enumerated_data_type.end(),[&](const boost::weak_ptr<EnumeratedDataType> enumerated_data_type_weak_ptr_existed)
  {
    if(boost::shared_ptr<EnumeratedDataType> enumerated_data_type_shared_ptr_existed = enumerated_data_type_weak_ptr_existed.lock())
    {
      result += enumerated_data_type_shared_ptr_existed->toText(child_indent);
    }
  });

  std::for_each(vector_structured_data_type.begin(),vector_structured_data_type.end(),[&](const boost::weak_ptr<StructuredDataType> structured_data_type_weak_ptr_existed)
  {
    if(boost::shared_ptr<StructuredDataType> structured_data_type_shared_ptr_existed = structured_data_type_weak_ptr_existed.lock())
    {
      result += structured_data_type_shared_ptr_existed->toText(child_indent);
    }
  });

  std::for_each(vector_package.begin(),vector_package.end(),[&](const boost::weak_ptr<Package> package_weak_ptr_existed)
  {
    if(boost::shared_ptr<Package> package_shared_ptr_existed = package_weak_ptr_existed.lock())
    {
      result += package_shared_ptr_existed->toText(child_indent);
    }
  });

  result += current_indent + "};\n";

  return result;
}
