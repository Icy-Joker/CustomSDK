@chcp 65001
@echo off
::
:: 记录脚本所在位置
set script_directory=%~dp0
:: 进入脚本所在位置
pushd "%script_directory%"
  pushd "../../"
    set CustomSDK=%CD%
    set CLASSPATH=%CustomSDK%/bin/CustomFramework4Java.jar;%CustomSDK%/test/bin/CustomModule4Java.jar;%CustomSDK%/test/bin/CustomModuleExecutable4Java.jar;%CLASSPATH%
    pushd "bin"
      start /B /WAIT "CustomModuleExecutable4Java" "java" "examples.CustomModuleExecutable" "-c" "../test/config/config4Java.xml"
      pause
    popd
  popd
popd
