#pragma once

#ifndef __IDLFILEDEFINITION_H__
# define __IDLFILEDEFINITION_H__

#include "Package.h"

#include <list>

class TopicDefinition;

class IDLFileDefinition : public Package
{
public:
  explicit IDLFileDefinition();
  ~IDLFileDefinition() override;
public:
  void appendFileReference(const boost::shared_ptr<IDLFileDefinition>&);
  const std::list<boost::shared_ptr<IDLFileDefinition>>& getFileReferences();

  void appendTopicDefinition(const boost::shared_ptr<TopicDefinition>&);
  const std::list<boost::shared_ptr<TopicDefinition>>& getTopicDefinitions();
public:
  void setFilePath(const std::string&);
  const std::string& getFilePath() const;
public:
  bool doSaveAs(const std::string&) const;
  bool doSave() const;
public:
  std::string getCompleteName() const override;
public:
  std::string toText(const std::string& current_indent = "") const override;
private:
  std::string file_path;
  std::list<boost::shared_ptr<IDLFileDefinition>> file_references;

  std::list<boost::shared_ptr<TopicDefinition>> topics;
};

#endif // !__IDLFILEDEFINITION_H__
