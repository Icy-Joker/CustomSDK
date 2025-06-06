#!/bin/bash

PROJECT_NAME=CustomSDK #工程名称

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
    cmake  -G "Sublime Text 2 - Unix Makefiles" -DCMAKE_BUILD_TYPE="Release" "$SOURCE_DIRECTORY" #构建项目工程
    if [ $? -eq 0 ];
    then
      read -t 5 -n 1 -p "Do you want to open the project with \"Sublime Text\"? [Y/N]: " option
      case "$option" in
        [Yy])
          echo ""
          if test "subl"
          then
            subl --launch-or-new-window --project "$PROJECT_NAME.sublime-project"
          else
            open "$PROJECT_NAME.sublime-project"
          fi
          ;;
      esac
    fi
  popd
popd
