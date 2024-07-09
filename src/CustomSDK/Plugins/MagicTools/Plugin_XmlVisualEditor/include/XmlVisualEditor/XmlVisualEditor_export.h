#pragma once

#ifndef __VISUALXMLEDITOR_EXPORT_H__
# define __VISUALXMLEDITOR_EXPORT_H__

# ifdef _MSC_VER
#  ifdef XmlVisualEditor_EXPORTS
#   define XmlVisualEditor_API _declspec(dllexport)
#  elif defined USE_XmlVisualEditor_STATIC
#   define XmlVisualEditor_API
#  else
#   define XmlVisualEditor_API _declspec(dllimport)
#  endif // XmlVisualEditor_EXPORTS
# else
#  define XmlVisualEditor_API
# endif //_MSC_VER

#endif // !__VISUALXMLEDITOR_EXPORT_H__