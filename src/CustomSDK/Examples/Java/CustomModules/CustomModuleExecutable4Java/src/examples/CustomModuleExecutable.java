package examples;

import CustomFramework4Java.CustomFrameworkManager;
import CustomFramework4Java.AbstractCustomModule;
import CustomModule4Java.CustomModule;

import org.apache.commons.cli.*;

public class CustomModuleExecutable
{
  void doSomething()
  {
    CustomModule custom_module = new CustomModule();
    custom_module.doSayHello();
  }

  public static void main(String[] args)
  {
    Options options = new Options();

    Option option_config_path = new Option("c", "config_path", true, "Path to config file");
    option_config_path.setRequired(true);

    Option option_help = new Option("h", "help", false, "Show help");

    options.addOption(option_config_path);
    options.addOption(option_help);

    try
    {
      CommandLineParser parser = new DefaultParser();
      CommandLine command_line = parser.parse(options, args);
      String config_path = command_line.getOptionValue("config_path");
      try
      {
        CustomFrameworkManager.getInstance().initializeWithConfig(config_path);

        CustomModuleExecutable custom_module_executable = new CustomModuleExecutable();
        custom_module_executable.doSomething();
      }
      catch(Exception e)
      {
        e.printStackTrace();
      }
    }
    catch (ParseException e)
    {
      HelpFormatter formatter = new HelpFormatter();
      System.out.println(e.getMessage());
      formatter.printHelp("Allowed options", options);
    }
  }
}
