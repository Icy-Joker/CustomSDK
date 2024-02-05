#include "stdafx.h"

#include "CustomProjectPrivate.h"

CustomProjectPrivate::CustomProjectPrivate():
  project_name(),
  project_description(),
  project_version(),
  project_child_folder_list(std::set<std::string>{"Applications","Libraries","Modules","Plugins","Tools"})
{
}

CustomProjectPrivate::~CustomProjectPrivate()
{
}
