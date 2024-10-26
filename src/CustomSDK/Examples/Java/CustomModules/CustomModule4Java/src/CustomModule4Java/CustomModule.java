package CustomModule4Java;

import CustomFramework4Java.AbstractCustomModule;
import CustomFramework4Java.LogManager;

public class CustomModule extends AbstractCustomModule
{
  public CustomModule()
  {
    super();
  }

  @Override
  public void doSayHello()
  {
    System.out.println("[Java]:CustomModule::Hello World!");
  }

  public static void doRegister()
  {
    LogManager.getInstance().trace("[Java]:"+ CustomModule.class.getName() +" Registered...");
  }
}
