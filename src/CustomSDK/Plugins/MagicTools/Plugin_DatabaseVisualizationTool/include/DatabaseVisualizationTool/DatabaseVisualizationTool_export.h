#pragma once

#ifndef __DATABASEVISUALIZATIONTOOL_EXPORT_H__
# define __DATABASEVISUALIZATIONTOOL_EXPORT_H__

# ifdef _MSC_VER
#  ifdef DatabaseVisualizationTool_EXPORTS
#   define DatabaseVisualizationTool_API _declspec(dllexport)
#  elif defined USE_DatabaseVisualizationTool_STATIC
#   define DatabaseVisualizationTool_API
#  else
#   define DatabaseVisualizationTool_API _declspec(dllimport)
#  endif // DatabaseVisualizationTool_EXPORTS
# else
#  define DatabaseVisualizationTool_API
# endif //_MSC_VER

#endif // !__DATABASEVISUALIZATIONTOOL_EXPORT_H__
