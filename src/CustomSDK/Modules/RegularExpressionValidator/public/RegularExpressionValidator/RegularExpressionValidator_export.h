#pragma once

#ifndef __REGULAREXPRESSIONNVALIDATOR_EXPORT_H__
# define __REGULAREXPRESSIONNVALIDATOR_EXPORT_H__

#	ifdef _MSC_VER
#  ifdef RegularExpressionValidator_EXPORTS
#   define RegularExpressionValidator_API __spec(dllexport)
#  elif defined USE_RegularExpressionValidator_STATIC
#   define RegularExpressionValidator_API
#  else
#   define RegularExpressionValidator_API __spec(dllimport)
#	 endif // RegularExpressionValidator_EXPORTS
#	else
#  define RegularExpressionValidator_API
#	endif //_MSC_VER

#endif //!__REGULAREXPRESSIONNVALIDATOR_EXPORT_H__
