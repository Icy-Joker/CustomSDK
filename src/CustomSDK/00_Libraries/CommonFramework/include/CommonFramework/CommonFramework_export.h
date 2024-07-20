#pragma once

#ifndef COMMONFRAMEWORK_EXPORT_H
# define COMMONFRAMEWORK_EXPORT_H

# ifdef _MSC_VER
#  ifdef CommonFramework_EXPORTS
#   define CommonFramework_API _declspec(dllexport)
#  elif defined USE_CommonFramework_STATIC
#   define CommonFramework_API
#  else
#   define CommonFramework_API _declspec(dllimport)
#  endif // CommonFramework_EXPORTS
# else
#  define CommonFramework_API
# endif //_MSC_VER

#endif//!COMMONFRAMEWORK_EXPORT_H
