#pragma once

#include "BasicSupport_export.h"

#ifdef WIN32
# define WIN32_LEAN_AND_MEAN//��Windowsͷ�ļ����ų�����ʹ�õ���Ϣ
# include <windows.h>
#else
# include <dlfcn.h>
#endif
