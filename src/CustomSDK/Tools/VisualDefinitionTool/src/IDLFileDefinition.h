#pragma once

#ifndef __IDLFILEDEFINITION_H__
# define __IDLFILEDEFINITION_H__

#include "Package.h"

class TopicDefinition;

class IDLFileDefinition : public Package
{
public:
  explicit IDLFileDefinition();
  ~IDLFileDefinition() override;
public:
  void appendFileReference(boost::shared_ptr<IDLFileDefinition>);
  void appendTopicDefinition(boost::shared_ptr<TopicDefinition>);

  const std::vector<boost::shared_ptr<IDLFileDefinition>>& getFileReferences();
  const std::vector<boost::shared_ptr<TopicDefinition>>& getTopicDefinitions();
public:
  void setFilePath(const std::string&);
  const std::string& getFilePath() const;
public:
  bool doSaveAs(const std::string&);
  bool doSave();
public:
  std::string getCompleteName() const override;
public:
  std::string toText(const std::string& current_indent = "") const override;
private:
  std::string file_path;
  std::vector<boost::shared_ptr<IDLFileDefinition>> file_references;

  std::vector<boost::shared_ptr<TopicDefinition>> topics;
};

#endif // !__IDLFILEDEFINITION_H__
