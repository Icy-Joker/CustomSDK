#pragma once

#ifdef _MSC_VER
# ifdef BasicFramework_EXPORTS
#  define BasicFramework_API _declspec(dllexport)
# elif defined USE_BasicFramework_STATIC
#  define BasicFramework_API
# else
#  define BasicFramework_API _declspec(dllimport)
# endif // BasicFramework_EXPORTS
#else
# define BasicFramework_API
#endif //_MSC_VER
