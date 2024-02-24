chcp 65001

@echo off

:: 开启延迟变量()
setlocal EnableDelayedExpansion

:: 项目解决方案名称
set project_name=CustomSDK
:: 安装目录
:: set project_install_directory=

:: %SecondParty%
set SecondParty=
:: %ThirdParty%
set ThirdParty=
:: %BOOST_DIR%
set BOOST_DIR=%ThirdParty%/boost
:: %QT_DIR%
set QT_DIR=%ThirdParty%/Qt

:: 此处必须注意.为了保持目录结构，脚本名称必须以"build_"开头
set script_name=%~n0
:: 记录脚本所在目录,防止目录错乱
set script_directory=%~dp0
pushd "%script_directory%"
  ::
  pushd "../%project_name%"
    set source_directory=%cd%
  popd
  :: CMake生成项目解決方案所在目录
  set build_directory=%TMP%/%project_name%/%script_name:~6%
  if NOT EXIST "%build_directory%" (
    mkdir "%build_directory%"
  )
  pushd "%build_directory%"
    :: 删除已有CMakeCache
    if EXIST "CMakeCache.txt" (
      del "CMakeCache.txt"
    )
    :: 生成解決方案
    cmake -G "Visual Studio 16 2019" -A "x64" "%source_directory%"
    :: 自动化步骤
    if !errorlevel! EQU 0 (
      ::支持一键打开顶目解决方案
      choice /t 5 /d N /m "Do you want to open the solution?"
      if !errorlevel! EQU 1 (
        start %project_name%.sln
      )
    ) else (
      :: 若CMake执行失败则暂停命令行以查看错误信息
      pause
    )
  popd
:: 返回脚本初始目录
popd
