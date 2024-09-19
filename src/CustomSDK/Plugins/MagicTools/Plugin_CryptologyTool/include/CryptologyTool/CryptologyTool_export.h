#pragma once

#ifndef __CRYPTOLOGYTOOL_EXPORT_H__
# define __CRYPTOLOGYTOOL_EXPORT_H__

# ifdef _MSC_VER
#  ifdef CryptologyTool_EXPORTS
#   define CryptologyTool_API _declspec(dllexport)
#  elif defined USE_CryptologyTool_STATIC
#   define CryptologyTool_API
#  else
#   define CryptologyTool_API _declspec(dllimport)
#  endif // CryptologyTool_EXPORTS
# else
#  define CryptologyTool_API
# endif //_MSC_VER

#endif // !__CRYPTOLOGYTOOL_EXPORT_H__
