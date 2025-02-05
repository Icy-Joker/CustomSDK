#pragma once

#ifndef __MICROSERVICEFRAMEWORK_EXPORT_H__
# define __MICROSERVICEFRAMEWORK_EXPORT_H__

# ifdef _MSC_VER
#  ifdef MicroserviceFramework_EXPORTS
#   define MicroserviceFramework_API _declspec(dllexport)
#  elif defined USE_MicroserviceFramework_STATIC
#   define MicroserviceFramework_API
#  else
#   define MicroserviceFramework_API _declspec(dllimport)
#  endif // MicroserviceFramework_EXPORTS
# else
#  define MicroserviceFramework_API
# endif //_MSC_VER

#endif // !__MICROSERVICEFRAMEWORK_EXPORT_H__
