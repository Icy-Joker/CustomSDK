#pragma once

#ifndef CUSTOMMODULE_EXPORT_H
# define CUSTOMMODULE_EXPORT_H

# ifdef _MSC_VER
#  define SYMBOL_EXPORT_DECLARE _declspec(dllexport)
#  define SYMBOL_IMPOER_DECLARE _declspec(dllimport)
# else
#  define SYMBOL_EXPORT_DECLARE
#  define SYMBOL_IMPOER_DECLARE
# endif

# ifdef _MSC_VER
#  ifdef CustomModule_EXPORTS
#   define CustomModule_API SYMBOL_EXPORT_DECLARE
#  elif defined USE_CustomModule_STATIC
#   define CustomModule_API
#  else
#   define CustomModule_API SYMBOL_IMPOER_DECLARE
#  endif // CustomFramework_EXPORTS
# else
#  define CustomModule_API
# endif //_MSC_VER

#endif//!CUSTOMMODULE_EXPORT_H
