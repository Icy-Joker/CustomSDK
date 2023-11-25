#pragma once

#include <BasicSupport/BasicSupport_export.h>
#include <BasicFramework/BasicFramework_export.h>
#include <BasicUIFramework/BasicUIFramework_export.h>

#include "PortScanner_export.h"

#ifdef WIN32
# define WIN32_LEAN_AND_MEAN//从Windows头文件中排除极少使用的信息
# include <windows.h>
#else
#endif
