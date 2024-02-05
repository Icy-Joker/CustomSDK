#pragma once

#ifndef __CUSTOMPROJECT_H__
# define __CUSTOMPROJECT_H__

#include <string>
#include <set>

struct CustomProjectPrivate;

class CustomProject
{
public:
  CustomProject() = delete;
public:
  CustomProject(const std::string& project_name);
  ~CustomProject();
public:
  void setName(const std::string& project_name);
  void setDescription(const std::string& project_description);
  void setVersion(const std::string& project_version);
  void appendChildFolder(const std::string& child_folder);
  void removeChildFolder(const std::string& child_folder);
public:
  const std::string& getName() const;
  const std::string& getDescription() const;
  const std::string& getVersion() const;
  const std::set<std::string>& getAllChildFolder() const;
public:
  bool generateVersionInfoResource(const std::string& output_directory) const;
  bool generateCMakeModule(const std::string& output_directory) const;
  bool generateGroupCMakeConfiguration(const std::string& output_directory) const;
  bool generateCMakeConfiguration(const std::string& output_directory) const;
public:
  bool generate(const std::string& output_directory) const;
protected:
private:
  CustomProjectPrivate* _p;
};

#endif // !__CUSTOMPROJECT_H__
