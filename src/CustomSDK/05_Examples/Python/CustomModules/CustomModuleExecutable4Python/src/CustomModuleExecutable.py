from CustomFramework4Python import CustomFrameworkManager

import os
import sys
import time
import argparse

class CustomModuleExecutable:
  def doSomething(self):
    pass

def main():
  parser = argparse.ArgumentParser()
  parser.add_argument("-c", "--config_path", type=str, required=True, help="Path to the configuration file")
  
  args = parser.parse_args()
  if not hasattr(args, "-h"):
    config_path = args.config_path
    
    custom_framework_manager = CustomFrameworkManager.instance()
    custom_framework_manager.initializeWithConfig(config_path)
    
    custom_module_executable = CustomModuleExecutable()
    custom_module_executable.doSomething()
  else:
    parser.print_help()

if __name__ == "__main__":
  main()
