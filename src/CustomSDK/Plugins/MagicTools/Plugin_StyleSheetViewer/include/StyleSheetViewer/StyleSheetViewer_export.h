#pragma once

#ifndef __STYLESHEETVIEWER_EXPORT_H__
# define __STYLESHEETVIEWER_EXPORT_H__

# ifdef _MSC_VER
#  ifdef StyleSheetViewer_EXPORTS
#   define StyleSheetViewer_API _declspec(dllexport)
#  elif defined USE_StyleSheetViewer_STATIC
#   define StyleSheetViewer_API
#  else
#   define StyleSheetViewer_API _declspec(dllimport)
#  endif // StyleSheetViewer_EXPORTS
# else
#  define StyleSheetViewer_API
# endif //_MSC_VER

#endif // !__STYLESHEETVIEWER_EXPORT_H__
