#pragma once

#ifndef __BASICFRAMEWORK_EXPORT_H__
# define __BASICFRAMEWORK_EXPORT_H__

# ifdef _MSC_VER
#  ifdef BasicFramework_EXPORTS
#   define BasicFramework_API _declspec(dllexport)
#  elif defined USE_BasicFramework_STATIC
#   define BasicFramework_API
#  else
#   define BasicFramework_API _declspec(dllimport)
#  endif // BasicFramework_EXPORTS
# else
#  define BasicFramework_API
# endif //_MSC_VER

#endif // !__BASICFRAMEWORK_EXPORT_H__
