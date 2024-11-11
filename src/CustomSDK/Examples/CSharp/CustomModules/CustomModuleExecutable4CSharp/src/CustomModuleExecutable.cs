using System;

using CustomFramework4CSharp;
using CustomModule4CSharp;

class CustomModuleExecutable
{
  void doSomething()
  {
    CustomModule custom_module = new CustomModule();
    custom_module.doSayHello();
  }

  static void Main(String[] args)
  {
    CustomFrameworkManager custom_framework_manager = CustomFrameworkManager.getInstance();
    if (custom_framework_manager != null)
    {
      custom_framework_manager.initializeWithConfig("../test/config/config4CSharp.xml");

      CustomModuleExecutable custom_module_executable = new CustomModuleExecutable();
      custom_module_executable.doSomething();
    }
    else
    {
      System.Console.WriteLine("[CSharp]:Error\n");
    }
  }
}
