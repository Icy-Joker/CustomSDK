#pragma once

#ifndef BASICSUPPORT_EXPORT_H
# define BASICSUPPORT_EXPORT_H

# ifdef _MSC_VER
#  define SYMBOL_EXPORT_DECLARE _declspec(dllexport)
#  define SYMBOL_IMPOER_DECLARE _declspec(dllimport)
# else
#  define SYMBOL_EXPORT_DECLARE
#  define SYMBOL_IMPOER_DECLARE
# endif

# ifdef _MSC_VER
#  ifdef BasicSupport_EXPORTS
#   define BasicSupport_API SYMBOL_EXPORT_DECLARE
#  elif defined USE_BasicSupport_STATIC
#   define BasicSupport_API
#  else
#   define BasicSupport_API SYMBOL_IMPOER_DECLARE
#  endif // BasicSupport_EXPORTS
# else
#  define BasicSupport_API
# endif //_MSC_VER

#endif//!BASICSUPPORT_EXPORT_H
