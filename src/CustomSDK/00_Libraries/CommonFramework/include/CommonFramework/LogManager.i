%{
#include <BasicSupport/BasicSupport_export.h>
#include <BasicSupport/Singleton.h>
#include <CommonFramework/CommonFramework_export.h>
#include <CommonFramework/LogManager.h>
%}

%include "std_string.i"

// 使java代理层也成为真正的单例
%typemap(javacode) LogManager%{
  private static volatile LogManager unique_instance;
  public static LogManager instance()
  {
    if (unique_instance == null)
    {
      synchronized (LogManagerSingleton.class)
      {
        if (unique_instance == null)
        {
          unique_instance = LogManagerSingleton.instance();
        }
      }
    }
    return unique_instance;
  }
%}

%include <BasicSupport/BasicSupport_export.h>
%include <BasicSupport/Singleton.h>
%template(LogManagerSingleton) Singleton<LogManager>;

%include <CommonFramework/CommonFramework_export.h>
%include <CommonFramework/LogManager.h>
