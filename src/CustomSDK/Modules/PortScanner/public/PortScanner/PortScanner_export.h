#pragma once

#ifndef __PORTSCANNER_EXPORT_H__
# define __PORTSCANNER_EXPORT_H__

#	ifdef _MSC_VER
#  ifdef PortScanner_EXPORTS
#   define PortScanner_API _declspec(dllexport)
#  elif defined USE_PortScanner_STATIC
#   define PortScanner_API
#  else
#   define PortScanner_API _declspec(dllimport)
#	 endif // PortScanner_EXPORTS
#	else
#  define PortScanner_API
#	endif //_MSC_VER

#endif //!__PORTSCANNER_EXPORT_H__
