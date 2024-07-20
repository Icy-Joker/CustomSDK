#!/bin/bash
#
#记录脚本所在位置
export script_directory=`dirname $0`
#进入脚本所在位置
pushd "$script_directory" > /dev/null
  pushd "../../" > /dev/null
    export CustomSDK=$PWD
    export CLASSPATH=$CustomSDK/bin/CustomFramework4Java.jar:$CustomSDK/test/bin/CustomModule4Java.jar:$CustomSDK/test/bin/CustomModuleExecutable4Java.jar:$CLASSPATH
    pushd "bin" > /dev/null
      sh -c 'java "examples.CustomModuleExecutable" -c "../test/config/config4Java.xml"'
    popd > /dev/null
  popd > /dev/null
popd > /dev/null
