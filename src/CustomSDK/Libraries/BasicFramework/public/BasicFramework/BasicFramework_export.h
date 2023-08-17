#pragma once

#	ifdef _MSC_VER
#	  ifdef BASICFRAMEWORK_EXPORTS
#     include <BasicSupport/CommonTypes.h>
#			define BasicFramework_API SYMBOL_EXPORT
#		else
#			define __LIB_NAME__	"BasicFramework"
#			include <BasicSupport/AutoLink.h>
#			define BasicFramework_API SYMBOL_IMPORT
#		endif // BASICFRAMEWORK_EXPORTS
#	else
#		define BasicFramework_API
#	endif //_MSC_VER