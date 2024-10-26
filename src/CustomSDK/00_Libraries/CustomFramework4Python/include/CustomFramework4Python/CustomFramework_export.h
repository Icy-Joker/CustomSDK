#pragma once

#ifndef CUSTOMFRAMEWORK_EXPORT_H
# define __CUSTOMFRAMEWORK_EXPORT_H__

# ifdef _MSC_VER
#  ifdef CustomFramework_EXPORTS
#   define CustomFramework_API _declspec(dllexport)
#  elif defined USE_CustomFramework_STATIC
#   define CustomFramework_API
#  else
#   define CustomFramework_API _declspec(dllimport)
#  endif // CustomFramework_EXPORTS
# else
#  define CustomFramework_API
# endif //_MSC_VER

#endif//!__CUSTOMFRAMEWORK_EXPORT_H__
