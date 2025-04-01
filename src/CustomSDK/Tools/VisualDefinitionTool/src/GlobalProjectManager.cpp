#include "stdafx.h"

#include "GlobalProjectManager.h"
#include "ProjectDefinition.h"

GlobalProjectManager* GlobalProjectManager::getInstance()
{
  static GlobalProjectManager instance;

  return &instance;
}

void GlobalProjectManager::setCurrentProject(const boost::shared_ptr<ProjectDefinition>& current_project_shared_ptr)
{
  this->current_project_weak_ptr = current_project_shared_ptr;
}

boost::shared_ptr<ProjectDefinition> GlobalProjectManager::getCurrentProject() const
{
  boost::shared_ptr<ProjectDefinition> current_project_shared_ptr = nullptr;

  {
    current_project_shared_ptr = this->current_project_weak_ptr.lock();
  }

  return current_project_shared_ptr;
}

boost::shared_ptr<ProjectDefinition> GlobalProjectManager::loadProject(const std::string& project_path)
{
  boost::shared_ptr<ProjectDefinition> current_project_shared_ptr = nullptr;

  {
    current_project_shared_ptr = boost::make_shared<ProjectDefinition>();
    {
      this->projects[project_path] = current_project_shared_ptr;
    }
  }

  return current_project_shared_ptr;
}

void GlobalProjectManager::unloadProject(const boost::shared_ptr<ProjectDefinition>& project_shared_ptr)
{
  if(project_shared_ptr)
  {
    this->projects.erase("");
  }
}

void GlobalProjectManager::unloadAllProjects()
{
  std::for_each(this->projects.begin(),this->projects.end(),[&](const std::pair<std::string,boost::shared_ptr<ProjectDefinition>>& project)
  {
    this->unloadProject(project.second);
  });
}
