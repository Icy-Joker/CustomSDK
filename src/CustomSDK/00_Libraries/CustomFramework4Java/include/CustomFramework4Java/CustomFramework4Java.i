%module(directors = "1") "CustomFramework4Java"

%include <std_string.i>

%include "CommonFramework/AbstractFrameworkManager.i"
%include "CommonFramework/AbstractCustomModule.i"
%include "CommonFramework/LogManager.i"

#ifdef SWIGCSHARP
#elif defined SWIGJAVA
  %pragma(java) jniclasscode =
  %{
  static
  {
    try
    {
      System.loadLibrary("CustomFramework4Java");
    }
    catch(Exception e)
    {
      System.out.println("Failed to load CustomFramework4Java");
    }
  }
  %};
#elif defined SWIGPYTHON
#endif
