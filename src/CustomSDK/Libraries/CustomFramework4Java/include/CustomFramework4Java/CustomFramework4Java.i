%module(directors = "1") "CustomFramework4Java"

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

%include "BasicFramework/AbstractFrameworkManager.i"
%include "BasicFramework/AbstractCustomModule.i"
%include "BasicFramework/LogManager.i"
