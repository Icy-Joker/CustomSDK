#!/bin/bash
#
#记录脚本所在位置
export script_directory=`dirname $0`
#进入脚本所在位置
pushd "$script_directory" > /dev/null
  pushd "../../" > /dev/null
    export CustomSDK=$PWD
    export PATH=$CustomSDK/bin:$PATH
    pushd "bin" > /dev/null
      sh -c '../test/bin/CustomModuleExecutable4CSharp'
    popd > /dev/null
  popd > /dev/null
popd > /dev/null
