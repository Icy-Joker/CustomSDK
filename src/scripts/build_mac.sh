#!/bin/bash

project_name=CustomSDK #工程名称
#project_install_directory= #指定安装目录

export SecondParty=~/WorkSpace/CustomSDK #$SecondParty
export ThirdParty=/opt/homebrew/opt #$ThirdParty
export BOOST_DIR=$ThirdParty/boost #$BOOST_DIR
export QT_DIR=$ThirdParty/qt #$QT_DIR

script_name=`basename -s ".sh" $0` #确定脚本名称
script_directory=`dirname $0` #记录脚本初始目录
pushd "$script_directory"
  pushd "../$project_name"
    source_directory=$PWD #记录项目源码目录
  popd
  build_directory=$TMPDIR/$project_name/$script_name #项目工程目录
  if ! test -d "$build_directory"
  then
    mkdir -p "$build_directory"
  fi
  pushd "$build_directory"
    #if test -f "CMakeCache.txt" #清理CMakeCache.txt
    #then
    # rm "CMakeCache.txt"
    #fi
    cmake  -G "Xcode" -DCMAKE_BUILD_TYPE="Release" "$source_directory" #构建项目工程
  popd
popd