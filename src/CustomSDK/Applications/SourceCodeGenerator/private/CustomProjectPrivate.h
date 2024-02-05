#pragma once

#ifndef __CUSTOMPROJECTPRIVATE_H__
# define __CUSTOMPROJECTPRIVATE_H__

#include <string>
#include <set>

struct CustomProjectPrivate
{
  std::string project_name;
  std::string project_description;
  std::string project_version;
  std::set<std::string> project_child_folder_list;
public:
  CustomProjectPrivate();
  ~CustomProjectPrivate();
};

#endif // !__CUSTOMPROJECTPRIVATE_H__
