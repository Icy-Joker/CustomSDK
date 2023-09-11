#!/bin/bash

# 记录脚本初始目录
script_directory=`dirname $0`
cd $script_directory
# 确定脚本名称
script_name=`basename -s ".sh" $0`
# 工程名称
project_name=CustomSDK
# 指定安装目录
#project_install_directory=
# $CustomSDK
export CustomSDK=~/WorkPlace/CustomSDK
# $ThirdParty
export ThirdParty=/usr/local
# $QTDIR
export QTDIR=$ThirdParty/qt-6.5.2
# 项目工程目录
export build_directory=../$script_name
if ! test -d "$build_directory"
then
  mkdir "$build_directory"
fi
cd "$build_directory"
# 清理CMakeCache.txt
#if test -f "CMakeCache.txt"
#then
#  rm "CMakeCache.txt"
#fi
# 构建项目工程
cmake  -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="Release" "../$project_name"
if [ $? -eq 0 ]; 
then
  read -t 5 -n 1 -p "Do you want to execute make command? [Y/N]: " option
  case "$option" in
    [Yy])
      echo ""
      make -j12
      make install
      ;;
  esac
fi
