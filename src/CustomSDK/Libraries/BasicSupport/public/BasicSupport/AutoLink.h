#ifdef _MSC_VER
# ifdef __LIB_NAME__
#  include <BasicSupport/CommonTypes.h>
#  pragma comment(lib, __LIB_NAME__ "-" _COMPILER_NAME _CRT_VER_NAME "-" _PLATFORM _DEBUG_FLAG ".lib")
#  pragma message("Linking to lib file: " __LIB_NAME__ _DEBUG_FLAG ".lib")
#  undef __LIB_NAME__
# else 
#  pragma error("__LIB_NAME__ undefined")
# endif // __LIB_NAME__
#else
#endif // _MSC_VER