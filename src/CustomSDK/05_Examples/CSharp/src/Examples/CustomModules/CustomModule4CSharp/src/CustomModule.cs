namespace CustomModule4CSharp;

using System;
using CustomFramework4CSharp;

public class CustomModule : AbstractCustomModule
{
  public CustomModule() : base()
  {
  }

  public override void doSayHello()
  {
    System.Console.WriteLine("[CSharp]:CustomModule::Hello World");
  }
}
