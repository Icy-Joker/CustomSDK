%{
#include <BasicSupport/BasicSupport_export.h>
#include <BasicSupport/Singleton.h>
#include <BasicFramework/BasicFramework_export.h>
#include <BasicFramework/LogManager.h>
%}

%include <BasicSupport/BasicSupport_export.h>
%include <BasicSupport/Singleton.h>
%template(LogManagerSingleton) Singleton<LogManager>;

%include <BasicFramework/BasicFramework_export.h>
%include <BasicFramework/LogManager.h>
