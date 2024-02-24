chcp 65001

@echo off

:: 开启延迟变量()
setlocal EnableDelayedExpansion

:: 项目解决方案名称
set PROJECT_NAME=CustomSDK
:: 安装目录
:: set INSTALL_DIRECTORY=

:: %SecondParty%
set SecondParty=
:: %ThirdParty%
set ThirdParty=
:: %BOOST_DIR%
set BOOST_DIR=%ThirdParty%/boost
:: %QT_DIR%
set QT_DIR=%ThirdParty%/Qt

:: 此处必须注意.为了保持目录结构，脚本名称必须以"build_"开头
set SCRIPT_NAME=%~n0
:: 记录脚本所在目录,防止目录错乱
set SCRIPT_DIRECTORY=%~dp0
pushd "%SCRIPT_DIRECTORY%"
  ::
  pushd "../%PROJECT_NAME%"
    set SOURCE_DIRECTORY=%cd%
  popd
  :: CMake生成项目解決方案所在目录
  set BUILD_DIRECTORY=../build/%SCRIPT_NAME:~6%
  if NOT EXIST "%BUILD_DIRECTORY%" (
    mkdir "%BUILD_DIRECTORY%"
  )
  pushd "%BUILD_DIRECTORY%"
    :: 删除已有CMakeCache
    if EXIST "CMakeCache.txt" (
      del "CMakeCache.txt"
    )
    :: 生成解決方案
    cmake -G "Visual Studio 14 2015" -A "x64" "%SOURCE_DIRECTORY%"
    :: 自动化步骤
    if !errorlevel! EQU 0 (
      ::支持一键打开顶目解决方案
      choice /t 5 /d N /m "Do you want to open the solution?"
      if !errorlevel! EQU 1 (
        start %PROJECT_NAME%.sln
      )
    ) else (
      :: 若CMake执行失败则暂停命令行以查看错误信息
      pause
    )
  popd
:: 返回脚本初始目录
popd