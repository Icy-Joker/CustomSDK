#!/bin/bash

PROJECT_NAME=CustomSDK #工程名称
#INSTALL_DIRECTORY= #指定安装目录

export SecondParty=~/WorkSpace/CustomSDK #$SecondParty
export ThirdParty=/opt/homebrew/opt #$ThirdParty
export BOOST_DIR=$ThirdParty/boost #$BOOST_DIR
export QT_DIR=$ThirdParty/qt #$QT_DIR

SCRIPT_NAME=`basename -s ".sh" $0` #确定脚本名称
SCRIPT_DIRECTORY=`dirname $0` #记录脚本初始目录
pushd "$SCRIPT_DIRECTORY"
  pushd "../$PROJECT_NAME"
    SOURCE_DIRECTORY=$PWD #记录项目源码目录
  popd
  BUILD_DIRECTORY=../$SCRIPT_NAME #项目工程目录
  if ! test -d "$BUILD_DIRECTORY"
  then
    mkdir -p "$BUILD_DIRECTORY"
  fi
  pushd "$BUILD_DIRECTORY"
    #if test -f "CMakeCache.txt" #清理CMakeCache.txt
    #then
    # rm "CMakeCache.txt"
    #fi
    cmake  -G "Xcode" -DCMAKE_BUILD_TYPE="Release" "$SOURCE_DIRECTORY" #构建项目工程
  popd
popd
