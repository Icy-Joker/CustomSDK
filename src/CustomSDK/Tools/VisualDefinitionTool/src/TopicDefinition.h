#pragma once

#ifndef TOPICDEFINITION_H
# define TOPICDEFINITION_H

class StructureType;

class TopicDefinition
{
public:
  void setName(const std::string&);
  const std::string& getName() const;

  void setStructure(const boost::shared_ptr<StructureType>&);
  boost::shared_ptr<StructureType> getStructure() const;

  std::string getStructureCompleteName() const;
private:
  std::string name;
  boost::weak_ptr<StructureType> topic_structure_weak_ptr;
  std::string description;
};

#endif // !TOPICDEFINITION_H
