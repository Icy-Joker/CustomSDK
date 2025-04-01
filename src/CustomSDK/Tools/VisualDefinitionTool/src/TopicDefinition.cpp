#include "stdafx.h"

#include "TopicDefinition.h"
#include "StructureType.h"

void TopicDefinition::setName(const std::string& topic_name)
{
  this->name = topic_name;
}

const std::string& TopicDefinition::getName() const
{
  return this->name;
}

void TopicDefinition::setStructure(const boost::shared_ptr<StructureType>& topic_structure_shared_ptr)
{
  this->topic_structure_weak_ptr = topic_structure_shared_ptr;
}

boost::shared_ptr<StructureType> TopicDefinition::getStructure() const
{
  return this->topic_structure_weak_ptr.lock();
}

std::string TopicDefinition::getStructureCompleteName() const
{
  std::string result;

  if(const boost::shared_ptr<StructureType>& structured_data_shared_ptr = this->getStructure())
  {
    result = structured_data_shared_ptr->getCompleteName();
  }

  return result;
}
