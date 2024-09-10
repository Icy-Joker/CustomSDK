#pragma once

#ifndef __HTTPCLIENT_EXPORT_H__
# define __HTTPCLIENT_EXPORT_H__

# ifdef _MSC_VER
#  ifdef HttpClient_EXPORTS
#   define HttpClient_API _declspec(dllexport)
#  elif defined USE_HttpClient_STATIC
#   define HttpClient_API
#  else
#   define HttpClient_API _declspec(dllimport)
#  endif // HttpClient_EXPORTS
# else
#  define HttpClient_API
# endif //_MSC_VER

#endif // !__HTTPCLIENT_EXPORT_H__
