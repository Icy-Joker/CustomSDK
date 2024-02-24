#pragma once

#ifndef __CUSTOMPROJECTPRIVATE_H__
# define __CUSTOMPROJECTPRIVATE_H__

#include <string>
#include <set>
#include <map>

struct CustomProjectPrivate
{
  std::string project_name;
  std::string project_description;
  std::string project_version;
  std::map<std::string,std::set<std::string>> map_project_child_folder;
public:
  CustomProjectPrivate();
  ~CustomProjectPrivate();
};

#endif // !__CUSTOMPROJECTPRIVATE_H__
