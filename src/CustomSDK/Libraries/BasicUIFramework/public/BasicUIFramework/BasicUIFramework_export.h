#pragma once

#ifdef _MSC_VER
# ifdef BasicUIFramework_EXPORTS
#  define BasicUIFramework_API _declspec(dllexport)
# elif defined USE_BasicUIFramework_STATIC
#  define BasicUIFramework_API
# else
#  define BasicUIFramework_API _declspec(dllimport)
# endif // BasicUIFramework_EXPORTS
#else
# define BasicUIFramework_API
#endif //_MSC_VER
