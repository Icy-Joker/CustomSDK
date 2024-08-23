#pragma once

#ifndef __CUSTOMDELEGATEDEMO_EXPORT_H__
# define __CUSTOMDELEGATEDEMO_EXPORT_H__

# ifdef _MSC_VER
#  ifdef CustomDelegateDemo_EXPORTS
#   define CustomDelegateDemo_API _declspec(dllexport)
#  elif defined USE_CustomDelegateDemo_STATIC
#   define CustomDelegateDemo_API
#  else
#   define CustomDelegateDemo_API _declspec(dllimport)
#  endif // CustomDelegateDemo_EXPORTS
# else
#  define CustomDelegateDemo_API
# endif //_MSC_VER

#endif // !__CUSTOMDELEGATEDEMO_EXPORT_H__
