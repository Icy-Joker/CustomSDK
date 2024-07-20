namespace CustomFramework4CSharp;

using System;
using System.Collections.Generic;
using System.Reflection;
using System.Globalization;

public class CustomFrameworkManager : AbstractFrameworkManager
{
  private static readonly CustomFrameworkManager unique_instance = new CustomFrameworkManager();

  private CustomFrameworkManager() : base()
  {
  }

  public static CustomFrameworkManager instance()
  {
    return unique_instance;
  }

  protected override void doLoadModules(string module_path)
  {
    try
    {
      Assembly assembly = Assembly.LoadFrom(module_path);
      if (assembly != null)
      {
        LogManager.instance().info("Loading Module["+ module_path +"]");
      }
    }
    catch (Exception e)
    {
      LogManager.instance().warn("Load Module[" + module_path + "] Failed");
    }
  }
}
