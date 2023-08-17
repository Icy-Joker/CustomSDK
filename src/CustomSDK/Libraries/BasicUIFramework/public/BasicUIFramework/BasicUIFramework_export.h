#pragma once

#	ifdef _MSC_VER
#	  ifdef BasicUIFramework_EXPORTS
#     include <BasicSupport/CommonTypes.h>
#       define BasicUIFramework_API SYMBOL_EXPORT
#	  else
#		define __LIB_NAME__	"BasicUIFramework"
#		include <BasicSupport/AutoLink.h>
#		define BasicUIFramework_API SYMBOL_IMPORT
#	  endif // BasicUIFramework_EXPORTS
#	else
#	  define BasicUIFramework_API
#	endif //_MSC_VER

namespace BasicUIFramework
{
  bool initialize(int argc,char* argv[]);
  int exec();
}
