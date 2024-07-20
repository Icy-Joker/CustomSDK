@chcp 65001
@echo off
::
:: 记录脚本所在位置
set script_directory=%~dp0
:: 进入脚本所在位置
pushd "%script_directory%"
  pushd "../../"
    set CustomSDK=%CD%
    set PYTHONPATH=%CustomSDK%/bin;%PYTHONPATH%
    pushd "bin"
      start /B /WAIT "CustomModuleExecutable4Python" "python" "../test/bin/CustomModuleExecutable.py" "-c" "../test/config/config4Python.xml"
      pause
    popd
  popd
popd
