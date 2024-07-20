package CustomFramework4Java;

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
  private static volatile CustomFrameworkManager unique_instance;

  private CustomFrameworkManager()
  {
    super();
  }

  public static CustomFrameworkManager instance()
  {
    if (unique_instance == null)
    {
      synchronized (CustomFrameworkManager.class)
      {
        if (unique_instance == null)
        {
          unique_instance = new CustomFrameworkManager();
        }
      }
    }
    return unique_instance;
  }

  @Override
  protected void doLoadModules(String module_path)
  {
    LogManager.instance().info("Loading Module["+ module_path +"]");
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
               LogManager.instance().trace("Registering Class[" + class_name+ "]");
               method.invoke(class_handle);
             }
          }
          catch(NoSuchMethodException e)
          {
            continue;
          }
        }
      }
    }
    catch(Exception e)
    {
      LogManager.instance().warn(e.toString());
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
