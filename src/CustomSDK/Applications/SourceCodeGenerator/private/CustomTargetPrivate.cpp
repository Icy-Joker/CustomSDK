#include "stdafx.h"

#include "CustomTargetPrivate.h"

CustomTargetPrivate::CustomTargetPrivate():
  target_name(""),
  target_type("UnknownType"),
  target_enable_export(true),
  target_public_class_list(std::set<std::string>()),
  target_private_class_list(std::set<std::string>())
{
}

CustomTargetPrivate::~CustomTargetPrivate()
{
}
