#pragma once

#ifndef GLOBALPROJECTMANAGER_H
# define GLOBALPROJECTMANAGER_H

#include <map>

class ProjectDefinition;

class GlobalProjectManager
{
private:
  //explicit GlobalProjectManager();
  //~GlobalProjectManager();
public:
  static GlobalProjectManager* getInstance();
public:
  void setCurrentProject(const boost::shared_ptr<ProjectDefinition>&);
  boost::shared_ptr<ProjectDefinition> getCurrentProject() const;
public:
  boost::shared_ptr<ProjectDefinition> loadProject(const std::string&);
  void unloadProject(const boost::shared_ptr<ProjectDefinition>&);
  void unloadAllProjects();
private:
  boost::weak_ptr<ProjectDefinition> current_project_weak_ptr;
  std::map<std::string,boost::shared_ptr<ProjectDefinition>> projects;
};

#endif // !GLOBALPROJECTMANAGER_H
