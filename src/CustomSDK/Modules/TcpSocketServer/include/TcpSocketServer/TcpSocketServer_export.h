#pragma once

#ifndef __TCPSOCKETSERVER_EXPORT_H__
# define __TCPSOCKETSERVER_EXPORT_H__

# ifdef _MSC_VER
#  ifdef TcpSocketServer_EXPORTS
#   define TcpSocketServer_API _declspec(dllexport)
#  elif defined USE_TcpSocketServer_STATIC
#   define TcpSocketServer_API
#  else
#   define TcpSocketServer_API _declspec(dllimport)
#  endif // TcpSocketServer_EXPORTS
# else
#  define TcpSocketServer_API
# endif //_MSC_VER

#endif // !__TCPSOCKETSERVER_EXPORT_H__
