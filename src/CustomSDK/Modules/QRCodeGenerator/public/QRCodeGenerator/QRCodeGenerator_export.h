#pragma once

#ifndef __QRCODEGENERATOR_EXPORT_H__
# define __QRCODEGENERATOR_EXPORT_H__

#	ifdef _MSC_VER
#  ifdef QRCodeGenerator_EXPORTS
#   define QRCodeGenerator_API __spec(dllexport)
#  elif defined USE_QRCodeGenerator_STATIC
#   define QRCodeGenerator_API
#  else
#   define QRCodeGenerator_API __spec(dllimport)
#	 endif // QRCodeGenerator_EXPORTS
#	else
#  define QRCodeGenerator_API
#	endif //_MSC_VER

#endif //!__QRCODEGENERATOR_EXPORT_H__
