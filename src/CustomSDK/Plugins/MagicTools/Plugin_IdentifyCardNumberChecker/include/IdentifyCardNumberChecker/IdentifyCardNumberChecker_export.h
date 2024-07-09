#pragma once

#ifndef __IDENTIFYCARDNUMBERCHECKER_EXPORT_H__
# define __IDENTIFYCARDNUMBERCHECKER_EXPORT_H__

# ifdef _MSC_VER
#  ifdef IdentifyCardNumberChecker_EXPORTS
#   define IdentifyCardNumberChecker_API _declspec(dllexport)
#  elif defined USE_IdentifyCardNumberChecker_STATIC
#   define IdentifyCardNumberChecker_API
#  else
#   define IdentifyCardNumberChecker_API _declspec(dllimport)
#  endif // IdentifyCardNumberChecker_EXPORTS
# else
#  define IdentifyCardNumberChecker_API
# endif //_MSC_VER

#endif // !__IDENTIFYCARDNUMBERCHECKER_EXPORT_H__