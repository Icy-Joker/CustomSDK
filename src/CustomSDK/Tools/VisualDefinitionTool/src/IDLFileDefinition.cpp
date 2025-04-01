#include "stdafx.h"

#include "IDLFileDefinition.h"

#include <fstream>
#include <TopicDefinition.h>

#include <boost/filesystem.hpp>

IDLFileDefinition::IDLFileDefinition()
{
}

IDLFileDefinition::~IDLFileDefinition()
{
}

void IDLFileDefinition::appendFileReference(const boost::shared_ptr<IDLFileDefinition>& file_reference_definition_shared_ptr)
{
  this->file_references.emplace_back(file_reference_definition_shared_ptr);
}

const std::list<boost::shared_ptr<IDLFileDefinition>>& IDLFileDefinition::getFileReferences()
{
  return this->file_references;
}

void IDLFileDefinition::appendTopicDefinition(const boost::shared_ptr<TopicDefinition>& topic_definition_shared_ptr)
{
  this->topics.emplace_back(topic_definition_shared_ptr);
}

const std::list<boost::shared_ptr<TopicDefinition>>& IDLFileDefinition::getTopicDefinitions()
{
  return this->topics;
}

void IDLFileDefinition::setFilePath(const std::string& file_path_string)
{
  try
  {
    boost::filesystem::path file_path(file_path_string);

    this->file_path = file_path_string;

    this->setName(file_path.filename().string());
  }
  catch(const boost::filesystem::filesystem_error&)
  {
  }
}

const std::string& IDLFileDefinition::getFilePath() const
{
  return this->file_path;
}

bool IDLFileDefinition::doSaveAs(const std::string& file_path_string) const
{
  bool result = false;

  try
  {
    const boost::filesystem::path file_path(file_path_string);

    const boost::filesystem::path parent_directory = file_path.parent_path();
    if(!boost::filesystem::exists(parent_directory))
    {
      boost::filesystem::create_directories(parent_directory);
    }

    std::ofstream file_output_stream(file_path.string(),std::ios::binary);
    if(file_output_stream.is_open())
    {
      file_output_stream << this->toText();

      result = true;
    }
  }
  catch(const boost::filesystem::filesystem_error&)
  {
  }

  return result;
}

bool IDLFileDefinition::doSave() const
{
  bool result = false;

  result = doSaveAs(this->file_path);

  return result;
}

std::string IDLFileDefinition::getCompleteName() const
{
  return "";
}

std::string IDLFileDefinition::toText(const std::string& current_indent) const
{
  std::string result;
  const std::string& child_indent = current_indent;

  {
    // 添加文件引用关系
    std::string file_references_string;
    std::for_each(file_references.begin(),file_references.end(),[&](const boost::shared_ptr<IDLFileDefinition>& file_reference_shared_ptr)
    {
      const std::string& file_reference_complete_name = file_reference_shared_ptr->getFilePath();

      file_references_string += "import<" + file_reference_complete_name + ">;\n";
    });
    if(!file_references_string.empty())
    {
      result += file_references_string;
      result += "\n";
    }
  }

  {
    // 添加数据结构定义
    const std::string datatype_definition_string = this->Package::toText(child_indent);
    if(!datatype_definition_string.empty())
    {
      result += datatype_definition_string;
      result += current_indent + "\n";
    }
  }

  {
    // 添加主题定义
    std::string topic_definition_string;
    std::for_each(topics.begin(),topics.end(),[&](const boost::shared_ptr<TopicDefinition>& topic_definition_shared_ptr)
    {
      const std::string& topic_name = topic_definition_shared_ptr->getName();
      const std::string topic_structure_complete_name = topic_definition_shared_ptr->getStructureCompleteName();

      topic_definition_string += "topic " + topic_name + " = " + topic_structure_complete_name + ";\n";
    });
    if(!topic_definition_string.empty())
    {
      result += topic_definition_string;
      result += "\n";
    }
  }

  {
    //添加服务定义
  }

  return result;
}
