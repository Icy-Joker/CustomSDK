#pragma once

#ifndef __TCPSOCKETCLIENT_EXPORT_H__
# define __TCPSOCKETCLIENT_EXPORT_H__

# ifdef _MSC_VER
#  ifdef TcpSocketClient_EXPORTS
#   define TcpSocketClient_API _declspec(dllexport)
#  elif defined USE_TcpSocketClient_STATIC
#   define TcpSocketClient_API
#  else
#   define TcpSocketClient_API _declspec(dllimport)
#  endif // TcpSocketClient_EXPORTS
# else
#  define TcpSocketClient_API
# endif //_MSC_VER

#endif // !__TCPSOCKETCLIENT_EXPORT_H__
