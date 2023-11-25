#pragma once

#ifdef _MSC_VER
# ifdef BasicSupport_EXPORTS
#  define BasicSupport_API _declspec(dllexport)
# elif defined USE_BasicSupport_STATIC
#  define BasicSupport_API
# else
#  define BasicSupport_API _declspec(dllimport)
# endif // BasicSupport_EXPORTS
#else
# define BasicSupport_API
#endif //_MSC_VER
