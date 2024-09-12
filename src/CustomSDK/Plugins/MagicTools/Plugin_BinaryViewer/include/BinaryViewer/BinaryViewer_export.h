#pragma once

#ifndef __BINARYVIEWER_EXPORT_H__
# define __BINARYVIEWER_EXPORT_H__

# ifdef _MSC_VER
#  ifdef BinaryViewer_EXPORTS
#   define BinaryViewer_API _declspec(dllexport)
#  elif defined USE_BinaryViewer_STATIC
#   define BinaryViewer_API
#  else
#   define BinaryViewer_API _declspec(dllimport)
#  endif // BinaryViewer_EXPORTS
# else
#  define BinaryViewer_API
# endif //_MSC_VER

#endif // !__BINARYVIEWER_EXPORT_H__
