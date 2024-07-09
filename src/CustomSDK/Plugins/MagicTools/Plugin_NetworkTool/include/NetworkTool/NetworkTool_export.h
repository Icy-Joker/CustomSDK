#pragma once

#ifndef __NETWORKTOOL_EXPORT_H__
# define __NETWORKTOOL_EXPORT_H__

# ifdef _MSC_VER
#  ifdef NetworkTool_EXPORTS
#   define NetworkTool_API _declspec(dllexport)
#  elif defined USE_NetworkTool_STATIC
#   define NetworkTool_API
#  else
#   define NetworkTool_API _declspec(dllimport)
#  endif // NetworkTool_EXPORTS
# else
#  define NetworkTool_API
# endif //_MSC_VER

#endif // !__NETWORKTOOL_EXPORT_H__
