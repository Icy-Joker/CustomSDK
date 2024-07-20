package CustomFramework4Java;

import java.net.URL;
import java.net.URLClassLoader;

public class CustomClassLoader extends URLClassLoader
{
  public CustomClassLoader(URL[] urls, ClassLoader parent)
  {
    super(urls,parent);
  }

  public CustomClassLoader(URL[] urls)
  {
    super(urls);
  }

  @Override
  public void addURL(URL url)
  {
    super.addURL(url);
  }
}
