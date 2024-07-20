#pragma once

#ifndef CUSTOMSDK_ABSTRACTPLUGINPRIVATE_H
# define CUSTOMSDK_ABSTRACTPLUGINPRIVATE_H

# include <string>

class AbstractPluginPrivate
{
private:
  std::string name;
  std::string description;
private:
  friend class AbstractPlugin;
};

#endif
