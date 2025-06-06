chcp 65001

@echo off

::
setlocal EnableExtensions
:: 开启延迟变量()
setlocal EnableDelayedExpansion

:: 项目解决方案名称
set PROJECT_NAME=CustomSDK

:: %SecondParty%
if not defined SecondParty (
  set SecondParty=
)
:: %ThirdParty%
if not defined ThirdParty (
  set ThirdParty=
)
:: %BOOST_DIR%
if not defined BOOST_DIR (
  set BOOST_DIR=%ThirdParty%/boost
)
:: %QT_DIR%
if not defined QT_DIR (
  set QT_DIR=%ThirdParty%/Qt
)

pushd "%~dp0%"
  :: 此处必须注意.为了保持目录结构，脚本名称必须以"build_"开头
  set SCRIPT_NAME=%~n0
  :: 源码目录
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
    cmake -A "win32" "%SOURCE_DIRECTORY%"
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
popd
