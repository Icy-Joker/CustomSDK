#pragma once

#ifndef __BASICUIFRAMEWORK_EXPORT_H__
# define __BASICUIFRAMEWORK_EXPORT_H__

# ifdef _MSC_VER
#  ifdef BasicUIFramework_EXPORTS
#   define BasicUIFramework_API _declspec(dllexport)
#  elif defined USE_BasicUIFramework_STATIC
#   define BasicUIFramework_API
#  else
#   define BasicUIFramework_API _declspec(dllimport)
#  endif // BasicUIFramework_EXPORTS
# else
#  define BasicUIFramework_API
# endif //_MSC_VER

#endif // !__BASICUIFRAMEWORK_EXPORT_H__
