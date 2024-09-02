#pragma once

#ifndef __UDPSOCKETSERVER_EXPORT_H__
# define __UDPSOCKETSERVER_EXPORT_H__

# ifdef _MSC_VER
#  ifdef UdpSocketServer_EXPORTS
#   define UdpSocketServer_API _declspec(dllexport)
#  elif defined USE_UdpSocketServer_STATIC
#   define UdpSocketServer_API
#  else
#   define UdpSocketServer_API _declspec(dllimport)
#  endif // UdpSocketServer_EXPORTS
# else
#  define UdpSocketServer_API
# endif //_MSC_VER

#endif // !__UDPSOCKETSERVER_EXPORT_H__
