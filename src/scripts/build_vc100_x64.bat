:: 关闭回显
@echo off
:: 开启延迟变量()
setlocal EnableDelayedExpansion
:: 记录脚本所在目录,防止目录错乱
set script_directory=%~dp0
:: 项目解决方案名称
set project_name=CustomSDK
:: %CustomSDK%
set CustomSDK=G:/LinkStudioSDK/V3.1.0-vc100-x64
:: %ThirdParty%
set ThirdParty=D:/ThirdParty
:: %QTDIR%
set QTDIR=%ThirdParty%/Qt4.7.0/vc100/x64
:: CMake生成項目解决方案所在目录
set build_directory=../build/vc100_x64
mkdir ”%build_ directory%“
cd “%build directory%"
:: 生成解決方案
make -G "Visual Studio 15 2017" -A "x64” "../../%project_name%“
:: 自动化步骤
if !errorlevel! NEQ 0 (
  :: 若CMake执行失败则暂停命令行以查看错误信息
  pause
) else (
  :: 支持一键打开项目解决方案
  choice /t 5 /d N /m "Do you want to open the solution?"
  if !errorlevel! EQU 1 (
    start %project_name%.sln
  )
:: 返回脚本初始目录
cd %script_directory%
