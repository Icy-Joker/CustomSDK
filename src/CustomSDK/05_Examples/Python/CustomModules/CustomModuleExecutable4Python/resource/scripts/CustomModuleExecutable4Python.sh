#!/bin/bash
#
#记录脚本所在位置
export script_directory=`dirname $0`
#进入脚本所在位置
pushd "$script_directory" > /dev/null
  pushd "../../" > /dev/null
    export CustomSDK=$PWD
    export PYTHONPATH=$CustomSDK/bin:$PYTHONPATH
    pushd "bin" > /dev/null
      sh -c 'python3 "../test/bin/CustomModuleExecutable.py" -c "../test/config/config4Python.xml"'
    popd > /dev/null
  popd > /dev/null
popd > /dev/null
