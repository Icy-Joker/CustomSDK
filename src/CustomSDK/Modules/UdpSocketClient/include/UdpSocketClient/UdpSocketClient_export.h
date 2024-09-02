#pragma once

#ifndef __UDPSOCKETCLIENT_EXPORT_H__
# define __UDPSOCKETCLIENT_EXPORT_H__

# ifdef _MSC_VER
#  ifdef UdpSocketClient_EXPORTS
#   define UdpSocketClient_API _declspec(dllexport)
#  elif defined USE_UdpSocketClient_STATIC
#   define UdpSocketClient_API
#  else
#   define UdpSocketClient_API _declspec(dllimport)
#  endif // UdpSocketClient_EXPORTS
# else
#  define UdpSocketClient_API
# endif //_MSC_VER

#endif // !__UDPSOCKETCLIENT_EXPORT_H__
