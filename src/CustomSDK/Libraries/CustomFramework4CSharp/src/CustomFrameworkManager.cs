namespace CustomFramework4CSharp;

using System;
using System.Collections.Generic;
using System.Reflection;
using System.Globalization;

public class CustomFrameworkManager : AbstractFrameworkManager
{
  private static readonly CustomFrameworkManager instance = new CustomFrameworkManager();

  private CustomFrameworkManager() : base()
  {
  }

  public static CustomFrameworkManager getInstance()
  {
    return instance;
  }

  protected override void doLoadModules(string module_path)
  {
    try
    {
      Assembly assembly = Assembly.LoadFrom(module_path);
      if (assembly != null)
      {
        LogManager.getInstance().info("Loading Module["+ module_path +"]");
      }
    }
    catch (Exception e)
    {
      LogManager.getInstance().warn("Load Module[" + module_path + "] Failed");
    }
  }
}
