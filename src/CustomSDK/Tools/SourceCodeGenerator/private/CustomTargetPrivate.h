#pragma once

#ifndef __CUSTOMTARGETPRIVATE_H__
# define __CUSTOMTARGETPRIVATE_H__

#include <string>
#include <set>

struct CustomTargetPrivate
{
  std::string target_name;
  std::string target_type;
  bool target_enable_export;
  std::set<std::string> target_public_class_list;
  std::set<std::string> target_private_class_list;
public:
  CustomTargetPrivate();
  ~CustomTargetPrivate();
};

#endif // !__CUSTOMTARGETPRIVATE_H__

