#pragma once

#ifndef TOPICDEFINITION_H
# define TOPICDEFINITION_H

class StructuredDataType;

class TopicDefinition
{
public:
  void setName(const std::string&);
  const std::string& getName() const;

  void setStructure(const boost::shared_ptr<StructuredDataType>&);
  boost::shared_ptr<StructuredDataType> getStructure() const;

  std::string getStructureCompleteName() const;
private:
  std::string name;
  boost::weak_ptr<StructuredDataType> topic_structure_weak_ptr;
  std::string description;
};

#endif // !TOPICDEFINITION_H
