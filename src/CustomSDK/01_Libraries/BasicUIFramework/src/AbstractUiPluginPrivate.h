#pragma once

#ifndef CUSTOMSDK_ABSTRACTUIPLUGINPRIVATE_H
# define CUSTOMSDK_ABSTRACTUIPLUGINPRIVATE_H

# include <string>
# include <QIcon>

class AbstractUIPluginPrivate
{
private:
  std::string type;
  QIcon icon;
private:
  friend class AbstractUIPlugin;
};

#endif
