@chcp 65001
@echo off
::
:: 记录脚本所在位置
set script_directory=%~dp0
:: 进入脚本所在位置
pushd "%script_directory%"
  pushd "../../"
    set CustomSDK=%CD%
    set PATH=%CustomSDK%/bin;%PATH%
    pushd "bin"
      start /B /WAIT "CustomModuleExecutable" "../test/bin/CustomModuleExecutable" "-c" "../test/config/config4CPlusPlus.xml"
      pause
    popd
  popd
popd
