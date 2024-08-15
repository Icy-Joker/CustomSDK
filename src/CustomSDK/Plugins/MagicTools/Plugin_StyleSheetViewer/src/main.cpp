#include "stdafx.h"

#include "StyleSheetViewer/StyleSheetViewer.h"

#include <QApplication>

#ifdef WIN32
#include <windows.h>
# define ATTRIBUTE_CONSTRUCTOR_DECLARE
# define ATTRIBUTE_DESTRUCTOR_DECLARE
#else
#include <dlfcn.h>
# define ATTRIBUTE_CONSTRUCTOR_DECLARE __attribute__((constructor))
# define ATTRIBUTE_DESTRUCTOR_DECLARE __attribute__((destructor))
#endif

extern "C"
{
  StyleSheetViewer_API void ATTRIBUTE_CONSTRUCTOR_DECLARE initializeStyleSheetViewer()
  {
#ifdef WIN32
#else
    Dl_info dl_info;
    if(dladdr((void*)initializeStyleSheetViewer,&dl_info))
    {
      //printf("Library:[%s] loaded\n",dl_info.dli_fname);
    }
#endif
  }

  StyleSheetViewer_API void ATTRIBUTE_DESTRUCTOR_DECLARE finalizeStyleSheetViewer()
  {
#ifdef WIN32
#else
    Dl_info dl_info;
    if(dladdr((void*)finalizeStyleSheetViewer,&dl_info))
    {
      //printf("Library:[%s] unloaded\n",dl_info.dli_fname);
    }
#endif
  }

#ifdef WIN32
  BOOL APIENTRY DllMain(HMODULE handle_module, DWORD  reason_for_call, LPVOID flags_reserved)
  {
    bool resulut = true;

    switch (reason_for_call)
    {
      case DLL_PROCESS_ATTACH:
      {
        char path[MAX_PATH];
        if(GetModuleFileNameA(handle_module,path,MAX_PATH) != 0)///获取当前模块的全路径
        {
          //printf("Library:[%s] loaded\n",path);
        }
        else
        {
          MessageBoxA(NULL,"failed to get library path","Error",MB_OK);
        }
        break;
      }
      case DLL_THREAD_ATTACH:
      {
        break;
      }
      case DLL_THREAD_DETACH:
      {
        break;
      }
      case DLL_PROCESS_DETACH:
      {
        char path[MAX_PATH];
        if(GetModuleFileNameA(handle_module,path,MAX_PATH) != 0)///获取当前模块的全路径
        {
          //printf("Library:[%s] unloaded\n",path);
        }
        else
        {
          MessageBoxA(NULL,"failed to get library path","Error",MB_OK);
        }
        break;
      }
      default:
      {
        break;
      }
    }
    return true;
  }
#endif
}

int main(int argc,char* argv[])
{
  int result = 0;

  QApplication app(argc,argv);

  StyleSheetViewer main_window;
  //main_window.show();

  result = app.exec();

  return result;
}
