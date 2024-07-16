#pragma once

#ifndef __CHARTDEMO_EXPORT_H__
# define __CHARTDEMO_EXPORT_H__

# ifdef _MSC_VER
#  ifdef ChartDemo_EXPORTS
#   define ChartDemo_API _declspec(dllexport)
#  elif defined USE_ChartDemo_STATIC
#   define ChartDemo_API
#  else
#   define ChartDemo_API _declspec(dllimport)
#  endif // ChartDemo_EXPORTS
# else
#  define ChartDemo_API
# endif //_MSC_VER

#endif // !__CHARTDEMO_EXPORT_H__
