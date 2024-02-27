chcp 65001
:: 关闭回显
@echo off

:: 记录脚本所在目录,防止目录错乱
set script_directory=%~dp0
pushd "%script_directory%"
  pushd "../.."
    :: 设置CustomSDK环境变量
    set CustomSDK=%cd%
    pushd "tools"
      :: SourceCodeGenerator --project_name ""
      :: SourceCodeGenerator --project_name "%CustomSDK%/src/CustomSDK"

      :: SourceCodeGenerator --target_name "XXX" -t "StaticLibrary|DynamicLibrary|PluginLibrary|ExecutableProgram" -o ""

      :: SourceCodeGenerator --target_name "BasicSupport" -t "DynamicLibrary" -o "%CustomSDK%/src/CustomSDK/Libraries"
      :: SourceCodeGenerator --target_name "BasicFramework" -t "DynamicLibrary" -o "%CustomSDK%/src/CustomSDK/Libraries"
      :: SourceCodeGenerator --target_name "BasicUIFramework" -t "DynamicLibrary" -o "%CustomSDK%/src/CustomSDK/Libraries"

      :: SourceCodeGenerator --target_name "SourceCodeGenerator" -t "ExecutableProgram" -o "%CustomSDK%/src/CustomSDK/Tools"
      :: SourceCodeGenerator --target_name "SerialPortDebugger" -t "ExecutableProgram" -o "%CustomSDK%/src/CustomSDK/Tools"
      :: SourceCodeGenerator --target_name "VisualDefinationTool" -t "ExecutableProgram" -o "%CustomSDK%/src/CustomSDK/Tools"
      :: SourceCodeGenerator --target_name "PortScanner" -t "ExecutableProgram" -o "%CustomSDK%/src/CustomSDK/Tools"
      :: SourceCodeGenerator --target_name "QRCodeGenerator" -t "ExecutableProgram" -o "%CustomSDK%/src/CustomSDK/Tools"
      :: SourceCodeGenerator --target_name "RegularExpressionValidator" -t "ExecutableProgram" -o "%CustomSDK%/src/CustomSDK/Tools"
      :: SourceCodeGenerator --target_name "IdentifierChecker" -t "ExecutableProgram" -o "%CustomSDK%/src/CustomSDK/Tools"
      :: SourceCodeGenerator --target_name "VisualConfigEditor" -t "ExecutableProgram" -o "%CustomSDK%/src/CustomSDK/Tools"

      :: SourceCodeGenerator --target_name "UDPSender" -t "ExecutableProgram" -o "%CustomSDK%/src/CustomSDK/Examples/Boost"
      :: SourceCodeGenerator --target_name "UDPReceiver" -t "ExecutableProgram" -o "%CustomSDK%/src/CustomSDK/Examples/Boost"
      :: SourceCodeGenerator --target_name "TCPServer" -t "ExecutableProgram" -o "%CustomSDK%/src/CustomSDK/Examples/Boost"
      :: SourceCodeGenerator --target_name "TCPClient" -t "ExecutableProgram" -o "%CustomSDK%/src/CustomSDK/Examples/Boost"
    popd
  popd
popd

