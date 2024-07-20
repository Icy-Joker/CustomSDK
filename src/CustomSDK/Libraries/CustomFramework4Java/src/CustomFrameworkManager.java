package CustomFramework4Java;

import CustomFramework4Java.CustomClassLoader;
import CustomFramework4Java.LogManager;

import java.net.URL;
import java.net.URLClassLoader;
import java.lang.reflect.Method;
import java.io.File;
import java.io.FileInputStream;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class CustomFrameworkManager extends AbstractFrameworkManager
{
  private static volatile CustomFrameworkManager instance;
  private CustomClassLoader custom_class_loader;

  private CustomFrameworkManager()
  {
    super();

    custom_class_loader = new CustomClassLoader(new URL[]{}, ClassLoader.getSystemClassLoader());
  }

  public static CustomFrameworkManager getInstance()
  {
    if (instance == null)
    {
      synchronized (CustomFrameworkManager.class)
      {
        if (instance == null)
        {
          instance = new CustomFrameworkManager();
        }
      }
    }
    return instance;
  }

  @Override
  protected void doLoadModules(String module_path)
  {
    try
    {
      ZipInputStream zip_input_stream = new ZipInputStream(new FileInputStream(module_path));
      for(ZipEntry zip_entry = zip_input_stream.getNextEntry(); zip_entry != null; zip_entry = zip_input_stream.getNextEntry())
      {
        if(!zip_entry.isDirectory() && zip_entry.getName().endsWith(".class"))
        {
          String class_name = zip_entry.getName().replace('/', '.').substring(0, zip_entry.getName().length() - 6);

          Class<?> class_handle = Class.forName(class_name);
          try
          {
             Method method = class_handle.getMethod("doRegister");
             if(!method.equals(null))
             {
               method.invoke(class_handle);
             }
          }
          catch(NoSuchMethodException e)
          {
            continue;
          }
        }
      }
      LogManager.getInstance().info("Loading Module["+ module_path +"]");
    }
    catch(Exception e)
    {
      LogManager.getInstance().debug(e.toString());
      LogManager.getInstance().warn("Load Module[" + module_path + "] Failed");
    }
  }

  static
  {
    try
    {
      System.loadLibrary("CustomFramework4Java");
    }
    catch(Exception e)
    {
      e.printStackTrace();
    }
  }
}
