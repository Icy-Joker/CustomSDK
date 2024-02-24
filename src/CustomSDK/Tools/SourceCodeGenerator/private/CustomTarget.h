#pragma once

#ifndef __CUSTOMTARGET_H__
# define __CUSTOMTARGET_H__

#include <string>
#include <set>

struct CustomTargetPrivate;

class CustomTarget
{
private:
  CustomTarget() = delete;
public:
  CustomTarget(const std::string& target_name, const std::string& target_type);
  ~CustomTarget();
public:
  void setName(const std::string& class_name);
  void setType(const std::string& class_name);
  void setEnableExport(const bool& enable_export);
  void appendPublicClassName(const std::string& class_name);
  void removePublicClassName(const std::string& class_name);
  void appendPrivateClassName(const std::string& class_name);
  void removePrivateClassName(const std::string& class_name);
public:
  const std::string& getName() const;
  const std::string& getType() const;
  const bool& getEnableExport() const;
  const std::set<std::string>& getAllPublicClassName() const;
  const std::set<std::string>& getAllPrivateClassName() const;
public:
  bool isValid() const;
public:
  bool generatePreCompiledHeader(const std::string& output_directory) const;
  bool generatePreCompiledSource(const std::string& output_directory) const;
  bool generateTargetExport(const std::string& output_directory) const;
  bool generateTargetHeader(const std::string& output_directory) const;
  bool generateTargetSource(const std::string& output_directory) const;
  bool generateClassPrivateHeader(const std::string& class_name, const std::string& output_directory) const;
  bool generateClassPrivateSource(const std::string& class_name, const std::string& output_directory) const;
  bool generateClassHeader(const std::string& class_name,bool export_flag, const std::string& output_directory) const;
  bool generateClassSource(const std::string& class_name, const std::string& output_directory) const;
  bool generateEntryMethod(const std::string& output_directory) const;
  bool generateCMakeConfiguration(const std::string& output_directory) const;
public:
  bool generate(const std::string& output_directory = "") const;
private:
  CustomTargetPrivate* _p;
};

#endif // !__CUSTOMTARGET_H__
