#pragma once

#include "BasicSupport_export.h"

#ifdef WIN32
# define WIN32_LEAN_AND_MEAN//从Windows头文件中排除极少使用的信息
# include <windows.h>
#else
# include <dlfcn.h>
#endif
