cmake_minimum_required(VERSION "3.13.0")

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.13.0)#此模块要求CMake版本至少3.13.0
  if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.9)#
    cmake_policy(SET CMP0068 NEW)
    if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.12)#
      cmake_policy(SET CMP0074 NEW)
      if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.13)#
        cmake_policy(SET CMP0078 NEW)
        if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.13)#
          cmake_policy(SET CMP0086 NEW)
          if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.21)#
            cmake_policy(SET CMP0122 NEW)
            if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.27)#
              cmake_policy(SET CMP0144 NEW)
              if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.30)#
                cmake_policy(SET CMP0167 OLD)
                if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.31)#
                  cmake_policy(SET CMP0174 NEW)
                endif()
              endif()
            endif()
          endif()
        endif()
      endif()
    endif()
  endif()
  
  if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})#编译环境与目标配置初始化
    set(CMAKE_WARN_VS10 OFF CACHE BOOL "CMAKE_WARN_VS10")#忽略将不支持VS2010的警告
    
    set(CMAKE_C_STANDARD "11")#设置语言标准要求"C11"
    set(CMAKE_CXX_STANDARD "11")#设置语言标准要求"C++11"
    
    set(CMAKE_C_STANDARD_REQUIRED "ON")#设置语言标准要求必须满足
    set(CMAKE_CXX_STANDARD_REQUIRED "ON")#设置语言标准要求必须满足
    
    set(CMAKE_C_EXTENSIONS "ON") # 编译器扩展
    set(CMAKE_CXX_EXTENSIONS "ON") # 编译器扩展
    
    set(CMAKE_POSITION_INDEPENDENT_CODE "ON")#生成位置无关代码
    set(CMAKE_ENABLE_EXPORTS "TRUE")
    
    #设置编译配置(VS支持多配置)
    if(NOT CMAKE_CONFIGURATION_TYPES)
      if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Release" CACHE INTERNAL "CMAKE_BUILD_TYPE" FORCE)
      endif()
      set(CMAKE_CONFIGURATION_TYPES "${CMAKE_BUILD_TYPE}" CACHE INTERNAL "CMAKE_CONFIGURATION_TYPES" FORCE)
    endif()
    
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")#MSVC编译器
      #设置编译选项
      #${CMAKE_CXX_FLAGS_INIT}=/DWIN32 /D_WINDOWS /W3 /GR /EHsc
      #${CMAKE_CXX_FLAGS_DEBUG_INIT}=/MDd /Zi /Ob0 /Od /RTC1
      #${CMAKE_CXX_FLAGS_RELEASE_INIT}=/MD /O2 /Ob2 /DNDEBUG
      #${CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT}=/MD /Zi /O2 /Ob1 /DNDEBUG
      
      #将源字符集和执行字符集设置为UTF-8
      add_compile_options(/utf-8)
      #多处理器编译
      add_compile_options(/MP)
      #忽略特定警告
      add_compile_options(/wd4482)#忽略警告[C4482: 使用了非标准扩展: 限定名中使用了枚举]
      add_compile_options(/wd4996)#忽略警告[C4996: 使用了不安全的函数]                              #sprintf等函数不安全,此警告用于提示其安全版本(_s)
      add_compile_options(/wd4251)#忽略警告[C4251: ]
      add_compile_options(/wd4819)#忽略警告[C4819: 该文件包含不能在当前代码页表示的字符,请将其保存为Unicode格式以防止数据丢失]
      add_compile_options(/wd4099)#忽略警告[C4099: 正在链接对象,如同没有调试信息一样]               #开启调试的情况下,没有找到链接库的PDB文件
      #将特定警告视为错误
      add_compile_options(/we4715)#警告视为错误[C4715: 不是所有的控件路径都返回值]                  #有时错误分支返回在优化开启的情况下会出现未知情况
      
      #确定C/C++运行时库版本
      if(NOT DEFINED MSVC_TOOLSET_VERSION)
        if(MSVC_VERSION LESS 1400)
          message(FATAL_ERROR "Unsupported MSVC_VERSION:${MSVC_VERSION}")
        elseif(CMAKE_GENERATOR MATCHES "2005")
          set(MSVC_TOOLSET_VERSION "80" CACHE STRING "MSVC_TOOLSET_VERSION")
        elseif(CMAKE_GENERATOR MATCHES "2008")
          set(MSVC_TOOLSET_VERSION "90" CACHE STRING "MSVC_TOOLSET_VERSION")
        elseif(CMAKE_GENERATOR MATCHES "2010")
          set(MSVC_TOOLSET_VERSION "100" CACHE STRING "MSVC_TOOLSET_VERSION")
        elseif(CMAKE_GENERATOR MATCHES "2012")
          set(MSVC_TOOLSET_VERSION "110" CACHE STRING "MSVC_TOOLSET_VERSION")
        elseif(CMAKE_GENERATOR MATCHES "2013")
          set(MSVC_TOOLSET_VERSION "120" CACHE STRING "MSVC_TOOLSET_VERSION")
        elseif(CMAKE_GENERATOR MATCHES "2015")
          set(MSVC_TOOLSET_VERSION "140" CACHE STRING "MSVC_TOOLSET_VERSION")
        elseif(CMAKE_GENERATOR MATCHES "2017")
          set(MSVC_TOOLSET_VERSION "141" CACHE STRING "MSVC_TOOLSET_VERSION")
        elseif(CMAKE_GENERATOR MATCHES "2019")
          set(MSVC_TOOLSET_VERSION "142" CACHE STRING "MSVC_TOOLSET_VERSION")
        elseif(CMAKE_GENERATOR MATCHES "2022")
          set(MSVC_TOOLSET_VERSION "143" CACHE STRING "MSVC_TOOLSET_VERSION")
        endif()
      endif()
      #高于vc140的默认按vc140兼容
      if(MSVC_TOOLSET_VERSION GREATER 140)
        #set(MSVC_TOOLSET_VERSION "140" CACHE STRING "MSVC_TOOLSET_VERSION")
      endif()
      set(CRT_VERSION_NAME "vc${MSVC_TOOLSET_VERSION}" CACHE STRING "CRT_VERSION_NAME")
      
      #确定处理器架构
      if(CMAKE_CL_64)
        set(PLATFORM "x64" CACHE STRING "PLATFORM")
      else()
        set(PLATFORM "x32" CACHE STRING "PLATFORM")
      endif()
      
      #库文件调试后缀
      set(CMAKE_DEBUG_POSTFIX "_d" CACHE STRING "CMAKE_DEBUG_POSTFIX" FORCE)
      #库文件编译信息
      set(DEFAULT_VERSION_INFORMATION "-${CRT_VERSION_NAME}-${PLATFORM}" CACHE STRING "DEFAULT_VERSION_INFORMATION" FORCE)
    else()#类Unix平台
      #确定C/C++运行时库版本
      set(CRT_VERSION_NAME "${CMAKE_CXX_COMPILER_ID}" CACHE STRING "CRT_VERSION_NAME")
      #确定处理器架构
      set(PLATFORM "${CMAKE_SYSTEM_PROCESSOR}" CACHE STRING "PLATFORM")
      #配置运行时库加载路径
      set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
      #set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
      #set(CMAKE_SKIP_BUILD_RPATH TRUE)
      #set(CMAKE_SKIP_INSTALL_RPATH TRUE)
      #
      if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        if(CMAKE_SYSTEM_PROCESSOR MATCHES "mips64")
          set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic -static-libgcc -mxgot")
        else()
          set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic -static-libgcc -static-libstdc++")
        endif()
        
        list(APPEND CMAKE_INSTALL_RPATH "$ORIGIN;")
      elseif(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
        list(APPEND CMAKE_INSTALL_RPATH "@executable_path;@loader_path;")
      endif()
      list(APPEND CMAKE_INSTALL_RPATH ".;../bin;../lib/${CRT_VERSION_NAME}_${PLATFORM};../lib;../thirdparty/bin;")
    endif()
    
    #可执行程序输出目录
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>" CACHE PATH "CMAKE_RUNTIME_OUTPUT_DIRECTORY" FORCE)
    #动态库输出目录
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>" CACHE PATH "CMAKE_LIBRARY_OUTPUT_DIRECTORY" FORCE)
    #静态库输出目录
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>" CACHE PATH "CMAKE_ARCHIVE_OUTPUT_DIRECTORY" FORCE)
    #程序数据库文件
    set(CMAKE_PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/pdb/$<CONFIG>" CACHE PATH "CMAKE_PDB_OUTPUT_DIRECTORY" FORCE)
    #Java
    set(CMAKE_JAVA_TARGET_OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin" CACHE PATH "CMAKE_JAVA_TARGET_OUTPUT_DIR" FORCE)
    
    #允许使用自定义目录
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    
    #设置CMake预定义文件夹名称
    set(PREDEFINED_TARGETS_FOLDER "_CMakePredefinedTargets")
    set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER ${PREDEFINED_TARGETS_FOLDER})
    
    #
    if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.9)
      set_property(GLOBAL PROPERTY AUTOGEN_SOURCE_GROUP "Moc Files")#
    endif()
    
    #若未设置安装目录,则自定义安装路径
    if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
      #获取工程根目录
      if(DEFINED ENV{INSTALL_DIRECTORY})
        set(CMAKE_INSTALL_PREFIX_DEFAULT $ENV{INSTALL_DIRECTORY} CACHE PATH "CMAKE_INSTALL_PREFIX_DEFAULT" FORCE)
      else()
        get_filename_component(ROOT_DIRECTORY ${CMAKE_SOURCE_DIR} DIRECTORY CACHE)
        get_filename_component(CMAKE_INSTALL_PREFIX_DEFAULT ${ROOT_DIRECTORY} DIRECTORY CACHE)
      endif()
      set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX_DEFAULT} CACHE INTERNAL "CMAKE_INSTALL_PREFIX" FORCE)
    endif()
    
    #检测跨语言扩展支持
    include(CheckLanguage)
    
    #CSharp环境初始化
    if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.8.2)
      check_language("CSharp")
      if(CMAKE_CSharp_COMPILER)
        enable_language("CSharp")
        include(CSharpUtilities)
        
        list(APPEND CMAKE_CSharp_FLAGS " /langversion:default /errorreport:prompt ")
        #set(CMAKE_CSharp_FLAGS "${CMAKE_CSharp_FLAGS}")
        #set(CMAKE_DOTNET_TARGET_FRAMEWORK_VERSION "" CACHE STRING "CMAKE_DOTNET_TARGET_FRAMEWORK_VERSION")
      endif()
    endif()
    
    #Java环境初始化
    find_package(Java QUIET COMPONENTS "Development")
    if(Java_FOUND)
      check_language("Java")
      if(CMAKE_Java_COMPILER)
        enable_language("Java")
        include(UseJava)
        include(FindJNI)
        
        #Java编译指定为utf8编码,防止源码文件编码格式不符导致编译报错
        list(APPEND CMAKE_JAVA_COMPILE_FLAGS "-encoding" "utf8")
      endif()
    endif()
    
    #Python环境初始化
    set(Python_USE_STATIC_LIBS "TRUE")
    find_package(Python QUIET COMPONENTS "Development;Interpreter")
    if(Python_FOUND)
      if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")#MSVC编译器
        set(CMAKE_SHARED_MODULE_PREFIX_PYTHON "_")
        set(CMAKE_SHARED_MODULE_SUFFIX_PYTHON ".pyd")
      else()
        set(CMAKE_SHARED_MODULE_PREFIX_PYTHON "_")
        set(CMAKE_SHARED_MODULE_SUFFIX_PYTHON ".so")
      endif()
    endif()
    
    #gRPC环境初始化
    find_package(gRPC QUIET)
    #Protobuf环境初始化
    find_package(Protobuf QUIET)
    
    #SWIG环境初始化
    if(DEFINED ENV{SWIG_EXECUTABLE})
      set(SWIG_EXECUTABLE $ENV{SWIG_EXECUTABLE} CACHE FILEPATH "SWIG_EXECUTABLE" FORCE)
    endif()
    find_package(SWIG 4.0 QUIET COMPONENTS "csharp;java;python")
    if(SWIG_FOUND)
      include(UseSWIG)
    endif()
    
    #输出编译环境信息
    message("")
    message("************************************************************************************************************************")
    #平台信息
    message(STATUS "CMAKE_GENERATOR:${CMAKE_GENERATOR}")
    message(STATUS "CRT_VERSION_NAME:${CRT_VERSION_NAME}")
    message(STATUS "PLATFORM:${PLATFORM}")
    message("************************************************************************************************************************")
    #环境变量
    message(STATUS "ThirdParty:$ENV{ThirdParty}")
    message(STATUS "BOOST_DIR:$ENV{BOOST_DIR}")
    message(STATUS "QT_DIR:$ENV{QT_DIR}")
    message("************************************************************************************************************************")
    #默认输出目录
    message(STATUS "CMAKE_CONFIGURATION_TYPES:${CMAKE_CONFIGURATION_TYPES}")
    message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    message(STATUS "CMAKE_LIBRARY_OUTPUT_DIRECTORY:${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    message(STATUS "CMAKE_ARCHIVE_OUTPUT_DIRECTORY:${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
    message(STATUS "CMAKE_PDB_OUTPUT_DIRECTORY:${CMAKE_PDB_OUTPUT_DIRECTORY}")
    message("************************************************************************************************************************")
    #默认Java输出目录
    message(STATUS "CMAKE_JAVA_TARGET_OUTPUT_DIR:${CMAKE_JAVA_TARGET_OUTPUT_DIR}")
    message("************************************************************************************************************************")
    #安装目录
    message(STATUS "CMAKE_INSTALL_PREFIX:${CMAKE_INSTALL_PREFIX}")
    message("************************************************************************************************************************")
    message("")
  endif()
else()
  message(FATAL_ERROR "CURRENT CMAKE_VERSION: (${CMAKE_VERSION}) VERSION_REQUIRED: (3.8.2) OR HIGHER")
endif()

#配置Boost库
macro(configureBoostModules)
  if(DEFINED BOOST_MODULE_LIST)
    if(DEFINED ENV{BOOST_DIR})
      #设置Boost模块搜索路径
      set(Boost_NO_WARN_NEW_VERSIONS "ON")
      set(CMAKE_PREFIX_PATH "$ENV{BOOST_DIR}")
      set(BOOST_ROOT "$ENV{BOOST_DIR}")
      set(BOOST_INCLUDEDIR "$ENV{BOOST_DIR}/include")
      if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")#MSVC编译器
        if(EXISTS "$ENV{BOOST_DIR}/lib/${CRT_VERSION_NAME}_${PLATFORM}")
          set(BOOST_LIBRARYDIR "$ENV{BOOST_DIR}/lib/${CRT_VERSION_NAME}_${PLATFORM}")
        elseif(EXISTS "$ENV{BOOST_DIR}/lib/${CRT_VERSION_NAME}/${PLATFORM}")
          set(BOOST_LIBRARYDIR "$ENV{BOOST_DIR}/lib/${CRT_VERSION_NAME}/${PLATFORM}")
        elseif(EXISTS "$ENV{BOOST_DIR}/lib/${CRT_VERSION_NAME}")
          set(BOOST_LIBRARYDIR "$ENV{BOOST_DIR}/lib/${CRT_VERSION_NAME}")
        elseif(EXISTS "$ENV{BOOST_DIR}/lib/${PLATFORM}")
          set(BOOST_LIBRARYDIR "$ENV{BOOST_DIR}/lib/${PLATFORM}")
        elseif(EXISTS "$ENV{BOOST_DIR}/lib")
          set(BOOST_LIBRARYDIR "$ENV{BOOST_DIR}/lib")
        else()
          set(BOOST_LIBRARYDIR "$ENV{BOOST_DIR}")
        endif()
      endif()
      set(Boost_USE_STATIC_LIBS "ON")
      set(Boost_USE_MULTITHREADED "ON")
      #预查找Boost库,确定Boost版本
      find_package(Boost COMPONENTS ${BOOST_MODULE_LIST} QUIET)
      if(Boost_FOUND)
        set(BOOST_MODULE_PREFIX "Boost::")
        foreach(CURRENT_MODULE_NAME ${BOOST_MODULE_LIST})
          if(TARGET "${BOOST_MODULE_PREFIX}${CURRENT_MODULE_NAME}")
            target_link_libraries(${CURRENT_TARGET} PRIVATE "${BOOST_MODULE_PREFIX}${CURRENT_MODULE_NAME}")#导入Boost公共库/模块依赖
          else()
            message(FATAL_ERROR "BoostModule[${CURRENT_MODULE_NAME}] not found")
          endif()
        endforeach()
        target_link_libraries(${CURRENT_TARGET} PRIVATE "Boost::diagnostic_definitions;Boost::disable_autolinking;")#
      else()
        message(FATAL_ERROR "UNKNOWN BOOST_VERSION")
      endif()
    else()
      message(FATAL_ERROR "BOOST_DIR not found for loading BOOST_MODULE_LIST")
    endif()
  endif()
endmacro()

#配置Qt库
macro(configureQtModules)
  if(DEFINED QT_MODULE_LIST)
    if(DEFINED ENV{QT_DIR})
      #设置Qt模块搜索路径
      set(CMAKE_PREFIX_PATH "$ENV{QT_DIR}")
      #设置此行才能成功找到Qt4
      set(QT_BINARY_DIR "$ENV{QT_DIR}/bin" CACHE PATH "QT_BINARY_DIR" FORCE)
      #
      set(QT_MKSPECS_DIR "$ENV{QT_DIR}/mkspecs" CACHE PATH "QT_MKSPECS_DIR" FORCE)
      #设置VS中环境变量
      set_property(TARGET ${CURRENT_TARGET} PROPERTY VS_GLOBAL_QT_DIR "$ENV{QT_DIR}")#$(QT_DIR)="$ENV{QT_DIR}"
      set_property(TARGET ${CURRENT_TARGET} PROPERTY VS_GLOBAL_QT_BINARY_DIR "${QT_BINARY_DIR}")#$(QT_BINARY_DIR)="${QT_BINARY_DIR}"
      set_property(TARGET ${CURRENT_TARGET} PROPERTY VS_GLOBAL_QT_MKSPECS_DIR "${QT_MKSPECS_DIR}")#$(QT_MKSPECS_DIR)="${QT_MKSPECS_DIR}"
      #Qt项目预处理
      set_property(TARGET ${CURRENT_TARGET} PROPERTY AUTOMOC ON)#自动处理自定义Qt类
      set_property(TARGET ${CURRENT_TARGET} PROPERTY AUTOUIC ON)#自动处理自定义Qt界面
      set_property(TARGET ${CURRENT_TARGET} PROPERTY AUTORCC ON)#自动处理自定义Qt资源
      #判断是否存在UI界面
      list(FIND QT_MODULE_LIST "Widgets" INDEX_WIDGETS)
      if(INDEX_WIDGETS GREATER "-1")#包含GUI
        set(USE_GUI ON)
      endif()
      #预查找Qt库,确定Qt版本
      find_package(Qt6 QUIET COMPONENTS "Core" OPTIONAL_COMPONENTS "Gui;Widgets")
      if(NOT Qt6_FOUND)
        find_package(Qt5 QUIET COMPONENTS "Core" OPTIONAL_COMPONENTS "Gui;Widgets")
        if(NOT Qt5_FOUND)
          find_package(Qt4 QUIET)
        endif()
      endif()
      if(Qt6_FOUND)#使用Qt6
        find_package(Qt6 QUIET REQUIRED COMPONENTS ${QT_MODULE_LIST})
        set(QT_MODULE_PREFIX "Qt6::")
      elseif(Qt5_FOUND)#使用Qt5
        list(REMOVE_ITEM QT_MODULE_LIST "Core5Compat")#这些模块在Qt5中没有独立存在
        find_package(Qt5 QUIET REQUIRED COMPONENTS ${QT_MODULE_LIST})
        set(QT_MODULE_PREFIX "Qt5::")
      elseif(Qt4_FOUND OR QT4_FOUND)#使用Qt4
        list(REMOVE_ITEM QT_MODULE_LIST "Widgets" "PrintSupport" "Concurrent" "Core5Compat")#这些模块在Qt4中没有独立存在
        set(QT_MODULE_PREFIX "Qt4::Qt")
      endif()
      if(DEFINED QT_MODULE_PREFIX)#成功找到版本合适的Qt库
        message("\tQT_MODULE_LIST:${QT_MODULE_LIST}")#输出实际导入的Qt模块列表
        foreach(CURRENT_MODULE_NAME ${QT_MODULE_LIST})
          if(TARGET "${QT_MODULE_PREFIX}${CURRENT_MODULE_NAME}")
            target_link_libraries(${CURRENT_TARGET} PRIVATE "${QT_MODULE_PREFIX}${CURRENT_MODULE_NAME}") #导入Qt公共库/模块依赖
            if(TARGET "${QT_MODULE_PREFIX}${CURRENT_MODULE_NAME}Private")
              target_link_libraries(${CURRENT_TARGET} PRIVATE "${QT_MODULE_PREFIX}${CURRENT_MODULE_NAME}Private")#导入Qt私有库/模块依赖
            endif()
          else()
            message(FATAL_ERROR "QtModule[${CURRENT_MODULE_NAME}] not found")
          endif()
        endforeach()
      else()
        message(FATAL_ERROR "UNKNOWN QT_VERSION")
      endif()
    else()
      message(FATAL_ERROR "QT_DIR not found for loading QT_MODULE_LIST")
    endif()
  endif()
endmacro()

#配置三方库
macro(configureThirdPartyList)
  if(DEFINED THIRD_LIBRARY_LIST)
    if(DEFINED ENV{ThirdParty})
      set_property(TARGET ${CURRENT_TARGET} PROPERTY VS_GLOBAL_ThirdParty "$ENV{ThirdParty}")#设置VS中环境变量:$(ThirdParty)=$ENV{ThirdParty}
      message("\tTHIRD_LIBRARY_LIST:${THIRD_LIBRARY_LIST}")#输出三方库列表
      foreach(CURRENT_LIBRARY_NAME ${THIRD_LIBRARY_LIST})
        find_package(${CURRENT_LIBRARY_NAME} QUIET)
        if(${CURRENT_LIBRARY_NAME}_FOUND)
          if(EXISTS "${${CURRENT_LIBRARY_NAME}_INCLUDE_DIRS}")
            target_include_directories(${CURRENT_TARGET} PRIVATE "${${CURRENT_LIBRARY_NAME}_INCLUDE_DIRS}")
          elseif(EXISTS "${${CURRENT_LIBRARY_NAME}_INCLUDE_DIR}")
            target_include_directories(${CURRENT_TARGET} PRIVATE "${${CURRENT_LIBRARY_NAME}_INCLUDE_DIR}")
          endif()
          if(DEFINED ${CURRENT_LIBRARY_NAME}_LIBRARIES AND NOT "${${CURRENT_LIBRARY_NAME}_LIBRARIES}" STREQUAL "")
            #target_Link_libraries(${CURRENT_TARGET} PRIVATE "${${CURRENT_LIBRARY_NAME}_LIBRARIES}")
          endif()
        else()
          #当前三方库根目录
          set(CURRENT_LIBRARY_ROOT "$ENV{ThirdParty}/${CURRENT_LIBRARY_NAME}")
          #添加头文件和静态库搜索路径
          set(CURRENT_LIBRARY_INCLUDE_DIRECTORY "${CURRENT_LIBRARY_ROOT}/include")
          if(EXISTS "${CURRENT_LIBRARY_ROOT}/lib/${CRT_VERSION_NAME}_${PLATFORM}")
            set(CURRENT_LIBRARY_LINK_DIRECTORY "${CURRENT_LIBRARY_ROOT}/lib/${CRT_VERSION_NAME}_${PLATFORM}")
          elseif(EXISTS "${CURRENT_LIBRARY_ROOT}/lib/${CRT_VERSION_NAME}/${PLATFORM}")
            set(CURRENT_LIBRARY_LINK_DIRECTORY "${CURRENT_LIBRARY_ROOT}/lib/${CRT_VERSION_NAME}/${PLATFORM}")
          elseif(EXISTS "${CURRENT_LIBRARY_ROOT}/lib/${CRT_VERSION_NAME}")
            set(CURRENT_LIBRARY_LINK_DIRECTORY "${CURRENT_LIBRARY_ROOT}/lib/${CRT_VERSION_NAME}")
          elseif(EXISTS "${CURRENT_LIBRARY_ROOT}/lib/${PLATFORM}")
            set(CURRENT_LIBRARY_LINK_DIRECTORY "${CURRENT_LIBRARY_ROOT}/lib/${PLATFORM}")
          elseif(EXISTS "${CURRENT_LIBRARY_ROOT}/lib")
            set(CURRENT_LIBRARY_LINK_DIRECTORY "${CURRENT_LIBRARY_ROOT}/lib")
          endif()
          if(EXISTS "${CURRENT_LIBRARY_INCLUDE_DIRECTORY}")
            target_include_directories(${CURRENT_TARGET} PRIVATE "${CURRENT_LIBRARY_INCLUDE_DIRECTORY}")
          endif()
          if(EXISTS "${CURRENT_LIBRARY_LINK_DIRECTORY}")
            target_link_directories(${CURRENT_TARGET} PRIVATE "${CURRENT_LIBRARY_LINK_DIRECTORY}")
            target_link_directories(${CURRENT_TARGET} PRIVATE "${CURRENT_LIBRARY_LINK_DIRECTORY}/$<IF:$<CONFIG:Debug>,Debug,Release>")
          endif()
        endif()
      endforeach()
    else()
      message(FATAL_ERROR "ThirdParty not found for loading THIRD_LIBRARY_LIST")
    endif()
  endif()
endmacro()

#配置授权限制
macro(configureCompanyLicense)
  set(LICENSE_MESSAGE)
  if(NOT DEFINED LICENSE_PRODUCT_ID)
    if(DEFINED ENV{BUILD_XXXX_PRODUCT})#
      if(CMAKE_SYSTEM_NAME MATCHES "Linux")
        set(LICENSE_PRODUCT_ID "1001")
      elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
        set(LICENSE_PRODUCT_ID "1000")
      endif()
      list(APPEND LICENSE_MESSAGE "BUILD_XXXX_PRODUCT:LICENSE_PRODUCT_ID=${LICENSE_PRODUCT_ID}\t")
    endif()
  else()
    list(APPEND LICENSE_MESSAGE "LICENSE_PRODUCT_ID=${LICENSE_PRODUCT_ID}\t")
  endif()
  if(DEFINED ENV{WITHOUT_LICENSE})
    target_compile_definitions(${CURRENT_TARGET} PRIVATE "WITHOUT_LICENSE")
    message("\t${LICENSE_MESSAGE}WITHOUT_LICENSE")
  else()
    target_compile_definitions(${CURRENT_TARGET} PRIVATE "LICENSE_PRODUCT_ID=${LICENSE_PRODUCT_ID}")
    message("\t${LICENSE_MESSAGE}LICENSE_REQUIRED")
  endif()
endmacro()

#从$ENV{SecondParty}导入公司内部其他项目的动态库(二方库)      用于依赖指定版本的SDK进行编译
macro(importTarget IMPORTED_TARGET_NAME)
  if(NOT TARGET "${IMPORTED_TARGET_NAME}")
    if(DEFINED ENV{SecondParty})
      if(EXISTS "$ENV{SecondParty}/include/${IMPORTED_TARGET_NAME}")#依赖已存在的指定版本的库
        message(STATUS "TARGET:${IMPORTED_TARGET_NAME}\t IMPORTED")
        add_library(${IMPORTED_TARGET_NAME} SHARED IMPORTED)
        set_property(TARGET ${IMPORTED_TARGET_NAME} PROPERTY IMPORTED_CONFIGURATIONS "${CMAKE_CONFIGURATION_TYPES}")
        set_property(TARGET ${IMPORTED_TARGET_NAME} PROPERTY INTERFACE_INCLUDE_DIRECTORIES "$ENV{SecondParty}/include")
        foreach(CONFIG_TYPE ${CMAKE_CONFIGURATION_TYPES})
          string(TOUPPER ${CONFIG_TYPE} CONFIG_TYPE_UPPER_CASE)
          set(IMPORTED_TARGET_BASE_NAME "${IMPORTED_TARGET_NAME}${DEFAULT_VERSION_INFORMATION}${CMAKE_${CONFIG_TYPE_UPPER_CASE}_POSTFIX}")
          #查找静态库
          if(MSVC)
            set(IMPORTED_TARGET_IMPLIB "${IMPORTED_TARGET_NAME}_IMPLIB_${CONFIG_TYPE_UPPER_CASE}")#静态库路径
            set(${IMPORTED_TARGET_IMPLIB} "${IMPORTED_TARGET_BASE_NAME}-NOTFOUND" CACHE STRING "${IMPORTED_TARGET_IMPLIB}" FORCE)#清除之前找到的二方库路径缓存
            find_library(${IMPORTED_TARGET_IMPLIB} "${CMAKE_FIND_LIBRARY_PREFIXES}${IMPORTED_TARGET_BASE_NAME}${CMAKE_FIND_LIBRARY_SUFFIX}"
                HINTS "$ENV{SecondParty}/lib"
                PATH_SUFFIXES "${CRT_VERSION_NAME}_${PLATFORM}" "${PLATFORM}" "${CRT_VERSION_NAME}/${PLATFORM}" "${CRT_VERSION_NAME}_${PLATFORM}/static" "${PLATFORM}/static" "${CRT_VERSION_NAME}/${PLATFORM}/static"
                NO_DEFAULT_PATH)
            if(NOT ${${IMPORTED_TARGET_IMPLIB}} STREQUAL "${IMPORTED_TARGET_IMPLIB}-NOTFOUND")
              set_property(TARGET ${IMPORTED_TARGET_NAME} PROPERTY IMPORTED_IMPLIB_${CONFIG_TYPE_UPPER_CASE} "${${IMPORTED_TARGET_IMPLIB}}")
              install(FILES "$<TARGET_LINKER_FILE:${IMPORTED_TARGET_NAME}>" DESTINATION "lib/${CRT_VERSION_NAME}_${PLATFORM}" CONFIGURATIONS "${CONFIG_TYPE}")#
              message("\tLINK_FOR_${CONFIG_TYPE_UPPER_CASE}:${${IMPORTED_TARGET_IMPLIB}}")
            else()
              message("\tLINK_FOR_${CONFIG_TYPE_UPPER_CASE}:NOTFOUND")
            endif()
          endif()
          #查找动态库
          set(IMPORTED_TARGET_LOCATION "${IMPORTED_TARGET_NAME}_LOCATION_${CONFIG_TYPE_UPPER_CASE}")#动态库路径
          set(${IMPORTED_TARGET_LOCATION} "${IMPORTED_TARGET_BASE_NAME}-NOTFOUND" CACHE STRING "${IMPORTED_TARGET_LOCATION}" FORCE)#清除之前找到的二方库路径缓存
          find_file(${IMPORTED_TARGET_LOCATION} "${CMAKE_FIND_LIBRARY_PREFIXES}${IMPORTED_TARGET_BASE_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}"
              HINTS "$ENV{SecondParty}"
              PATH_SUFFIXES "bin" "lib" "lib/${CRT_VERSION_NAME}_${PLATFORM}" "lib/${PLATFORM}"
              NO_DEFAULT_PATH)
          if(NOT ${${IMPORTED_TARGET_LOCATION}} STREQUAL "${IMPORTED_TARGET_LOCATION}-NOTFOUND")
            set_property(TARGET ${IMPORTED_TARGET_NAME} PROPERTY IMPORTED_LOCATION_${CONFIG_TYPE_UPPER_CASE} "${${IMPORTED_TARGET_LOCATION}}")
            install(FILES "$<TARGET_FILE:${IMPORTED_TARGET_NAME}>" DESTINATION "bin" CONFIGURATIONS "${CONFIG_TYPE_UPPER_CASE}")#
          endif()
        endforeach()
        message("")
      else()
        message(WARNING "${IMPORTED_TARGET_NAME} not imported,libraries cannot be found")
      endif()
    else()
      message(FATAL_ERROR "ENV{SecondParty} not defined to import target:${IMPORTED_TARGET_NAME}")
    endif()
  endif()
endmacro()

#导入
macro(addBasicGroup)
  #importTarget("")#
endmacro()

#导入
macro(addUIGroup)
  addBasicGroup()
  
  #importTarget("")#
endmacro()

#预处理-获取必须的信息
macro(collectInformation)
  get_filename_component(CURRENT_TARGET ${CMAKE_CURRENT_LIST_DIR} NAME_WE)#获取当前目标名称
  get_filename_component(CURRENT_SOURCE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)#获取当前源码文件夹名称
  get_property(PARENT_DIRECTORY DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY PARENT_DIRECTORY)#获取父目录
endmacro()

#准备CXX源文件
macro(prepareForCXXTarget)
  #############################################################################################################################
  file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cc" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx")#归集源文件
  file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.inc")#归集头文件
  file(GLOB_RECURSE FORM_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")#归集界面文件
  file(GLOB_RECURSE RESOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.rc" "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc")#归集资源文件
  file(GLOB_RECURSE TS_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.ts")#归集翻译文件
  if(MSVC AND EXISTS "${PROJECT_SOURCE_DIR}/VersionInfo.rc.in")
    set(CURRENT_TARGET_VERSIONINFO_RC "${CMAKE_CURRENT_BINARY_DIR}/VersionInfo.rc")
    string(TIMESTAMP CURRENT_YEAR "%Y")
    configure_file("${PROJECT_SOURCE_DIR}/VersionInfo.rc.in" "${CURRENT_TARGET_VERSIONINFO_RC}")#将版本&版权等信息写入生成的二进制文件
    list(APPEND RESOURCE_FILES "${CURRENT_TARGET_VERSIONINFO_RC}")
  endif()
  #############################################################################################################################
  #公共部分代码目录
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include")
    set(PUBLIC_HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
  else()
    set(PUBLIC_HEADER_DIR "${PARENT_DIRECTORY}")
  endif()
  #############################################################################################################################
  #私有部分代码目录
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src")
    set(PRIVATE_HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
  else()
    set(PRIVATE_HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
  endif()
  #############################################################################################################################
  if(NOT "${PRIVATE_HEADER_DIR}" STREQUAL "${PUBLIC_HEADER_DIR}/${CURRENT_SOURCE_FOLDER}")#经过设计的源码目录,具有较复杂的目录结构
    foreach(CURRENT_SOURCE_CODE_FILE_PATH ${HEADER_FILES} ${SOURCE_FILES} ${FORM_FILES} ${TS_FILES})
      get_filename_component(CURRENT_SOURCE_CODE_DIRECTORY ${CURRENT_SOURCE_CODE_FILE_PATH} DIRECTORY)#获取当前文件目录
      string(REPLACE "${PRIVATE_HEADER_DIR}" "_Src" CURRENT_SOURCE_CODE_FILE_GROUP "${CURRENT_SOURCE_CODE_DIRECTORY}")
      string(REPLACE "${PUBLIC_HEADER_DIR}" "_Include" CURRENT_SOURCE_CODE_FILE_GROUP "${CURRENT_SOURCE_CODE_FILE_GROUP}")
      file(TO_NATIVE_PATH "${CURRENT_SOURCE_CODE_FILE_GROUP}" "CURRENT_SOURCE_CODE_FILE_GROUP")
      source_group("${CURRENT_SOURCE_CODE_FILE_GROUP}" FILES "${CURRENT_SOURCE_CODE_FILE_PATH}")
    endforeach()
  else()#简单目录结构
    source_group("_Header Files" FILES ${HEADER_FILES})
    source_group("_Source Files" FILES ${SOURCE_FILES})
    source_group("Ui Files" FILES ${FORM_FILES})
    source_group("Translation Files" FILES ${TS_FILES})
  endif()
  source_group("Resource" FILES ${RESOURCE_FILES})
  #############################################################################################################################
endmacro()

#准备Protobuf文件
macro(prepareForProtobufTarget)
  #############################################################################################################################
  file(GLOB_RECURSE PROTO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")#归集Proto文件
  #############################################################################################################################
endmacro()

#准备CSharp源文件
macro(prepareForCSharpTarget)
  #############################################################################################################################
  file(GLOB_RECURSE CSHARP_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cs")#归集CSharp源文件
  #############################################################################################################################
endmacro()

#准备Java源文件
macro(prepareForJavaTarget)
  #############################################################################################################################
  file(GLOB_RECURSE JAVA_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.java")#归集Java源文件
  #############################################################################################################################
endmacro()

#准备Python源文件
macro(prepareForPythonTarget)
  #############################################################################################################################
  file(GLOB_RECURSE PYTHON_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.py")#归集Python源文件
  #############################################################################################################################
  foreach(CURRENT_SOURCE_CODE_FILE_PATH ${PYTHON_SOURCE_FILES}) #Python代码保持原始目录结构
    get_filename_component(CURRENT_SOURCE_CODE_DIRECTORY ${CURRENT_SOURCE_CODE_FILE_PATH} DIRECTORY)#获取当前文件目录
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" CURRENT_SOURCE_CODE_FILE_GROUP "${CURRENT_SOURCE_CODE_DIRECTORY}")
    file(TO_NATIVE_PATH "${CURRENT_SOURCE_CODE_FILE_GROUP}" "CURRENT_SOURCE_CODE_FILE_GROUP")
    source_group("${CURRENT_SOURCE_CODE_FILE_GROUP}" FILES "${CURRENT_SOURCE_CODE_FILE_PATH}")
  endforeach()
  #############################################################################################################################
endmacro()

#准备SWIG目标
macro(prepareForSWIGTarget)
  #############################################################################################################################
  prepareForCXXTarget()
  #############################################################################################################################
  file(GLOB_RECURSE SWIG_MODULE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/**/${CURRENT_SOURCE_FOLDER}.i")#归集SWIG接口定义模版文件
  file(GLOB_RECURSE CSHARP_SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/*.cs")#归集CSharp源文件
  file(GLOB_RECURSE JAVA_SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/*.java")#归集Java源文件
  file(GLOB_RECURSE PYTHON_SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/*.py")#归集Python源文件
  #############################################################################################################################
  if(SWIG_MODULE_FILE)
    #配置模块名称
    set_property(SOURCE ${SWIG_MODULE_FILE} PROPERTY SWIG_MODULE_NAME "${CURRENT_TARGET}")
    #指定按C++生成
    set_property(SOURCE ${SWIG_MODULE_FILE} PROPERTY CPLUSPLUS ON)
    if(${SWIG_LANGUAGE} MATCHES "CSharp")
      set_property(SOURCE ${SWIG_MODULE_FILE} APPEND_STRING PROPERTY COMPILE_OPTIONS -namespace ${CURRENT_TARGET})
    elseif(${SWIG_LANGUAGE} MATCHES "Java")
      set_property(SOURCE ${SWIG_MODULE_FILE} APPEND_STRING PROPERTY COMPILE_OPTIONS "-package;${CURRENT_TARGET}")
      string(REPLACE "." "/" SWIG_TARGET_SOURCE_STRUCTURE ${CURRENT_TARGET})
    elseif(${SWIG_LANGUAGE} MATCHES "Python")
    endif()
    if(NOT SWIG_TARGET_SOURCE_OUTPUT_DIR)
      set(SWIG_TARGET_SOURCE_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/source")
    endif()
    set_property(SOURCE ${SWIG_MODULE_FILE} PROPERTY OUTPUT_DIR "${SWIG_TARGET_SOURCE_OUTPUT_DIR}")
    set_property(SOURCE ${SWIG_MODULE_FILE} PROPERTY OUTFILE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated_source")#本地接口实现文件生成位置
  endif()
  #############################################################################################################################
endmacro()

#配置项目目录结构
macro(configureTargetForStructure)
  #############################################################################################################################
  get_property(CURRENT_TARGET_TYPE TARGET ${CURRENT_TARGET} PROPERTY TYPE)#获取目标类型
  message(STATUS "TARGET:${CURRENT_TARGET}\tTYPE:${CURRENT_TARGET_TYPE}")#输出当前目标名称
  string(REPLACE "${PROJECT_SOURCE_DIR}" "${CMAKE_PROJECT_NAME}" FOLDER_PATH ${PARENT_DIRECTORY})#获取相对路径
  set_property(TARGET ${CURRENT_TARGET} PROPERTY FOLDER "${FOLDER_PATH}")#保持项目目录结构
  #############################################################################################################################
endmacro()

#配置默认安装策略
macro(configureTargetForInstall)
  #############################################################################################################################
  if(NOT ${CURRENT_TARGET_TYPE} STREQUAL "UTILITY")#静态库
    if(${CURRENT_TARGET_TYPE} STREQUAL "STATIC_LIBRARY")#静态库
      if(${CMAKE_CURRENT_SOURCE_DIR} MATCHES "${PROJECT_SOURCE_DIR}/Libraries")
        if(NOT ${PUBLIC_HEADER_DIR} STREQUAL "${PARENT_DIRECTORY}")
          install(DIRECTORY "${PUBLIC_HEADER_DIR}/${CURRENT_SOURCE_FOLDER}" DESTINATION "include" OPTIONAL)
          install(TARGETS ${CURRENT_TARGET} ARCHIVE DESTINATION "lib/${CRT_VERSION_NAME}_${PLATFORM}/static")#静态库安装目录
        endif()
      endif()
    else()
      if(${CURRENT_TARGET_TYPE} STREQUAL "MODULE_LIBRARY")#插件库
        if(${CMAKE_CURRENT_SOURCE_DIR} MATCHES "${PROJECT_SOURCE_DIR}/Plugins")
          string(REGEX REPLACE "${PROJECT_SOURCE_DIR}/Plugins" "plugins" PLUGIN_INSTALL_PATH ${PARENT_DIRECTORY})
          install(TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION "${PLUGIN_INSTALL_PATH}" LIBRARY DESTINATION "${PLUGIN_INSTALL_PATH}")#插件库安装目录
        endif()
      else()
        if(${CURRENT_TARGET_TYPE} STREQUAL "EXECUTABLE")#可执行程序
          set_property(TARGET ${CURRENT_TARGET} PROPERTY DEBUG_POSTFIX "d")#设置可执行程序(调试版本)后缀
          if(${CMAKE_CURRENT_SOURCE_DIR} MATCHES "${PROJECT_SOURCE_DIR}/Applications")
            install(TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION "bin")#可执行程序安装目录
          elseif(${CMAKE_CURRENT_SOURCE_DIR} MATCHES "${PROJECT_SOURCE_DIR}/Tools")
            install(TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION "tools")#可执行程序(工具)安装目录
          endif()
        elseif(${CURRENT_TARGET_TYPE} STREQUAL "SHARED_LIBRARY")#动态库
          if(${CMAKE_CURRENT_SOURCE_DIR} MATCHES "${PROJECT_SOURCE_DIR}/Libraries")
            if(NOT ${PUBLIC_HEADER_DIR} STREQUAL "${PARENT_DIRECTORY}")#二次开发库(公开)
              install(DIRECTORY "${PUBLIC_HEADER_DIR}/${CURRENT_SOURCE_FOLDER}" DESTINATION "include" OPTIONAL)
            endif()
            install(TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION "bin" LIBRARY DESTINATION "bin" ARCHIVE DESTINATION "lib/${CRT_VERSION_NAME}_${PLATFORM}")#普通动态库(非插件&&仅运行)安装目录
          endif()
        endif()
      endif()
      if(MSVC)
        install(FILES $<TARGET_PDB_FILE:${CURRENT_TARGET}> DESTINATION "pdb" OPTIONAL)#将pdb文件放入安装目录用于调试
      endif()
    endif()
  endif()
  #############################################################################################################################
  message("")#
  #############################################################################################################################
endmacro()

#配置CXX项目
macro(configureAsCXXTarget)
  if(TARGET "${CURRENT_TARGET}")
    #############################################################################################################################
    configureTargetForStructure()
    #############################################################################################################################
    target_sources(${CURRENT_TARGET} PRIVATE ${SOURCE_FILES} ${HEADER_FILES} ${FORM_FILES} ${RESOURCE_FILES})
    #############################################################################################################################
    #预编译头处理
    set(PCH_NAME "stdafx.h")
    if(EXISTS "${PRIVATE_HEADER_DIR}/${PCH_NAME}")
      set(PCH_HEADER_FILE "${PRIVATE_HEADER_DIR}/stdafx.h")
      set(PCH_SOURCE_FILE "${PRIVATE_HEADER_DIR}/stdafx.cpp")
    endif()
    if(PCH_HEADER_FILE)
      if(MSVC)
        if(MSVC_IDE)
          set(PCH_DIR "${CMAKE_CURRENT_BINARY_DIR}/pch")
          file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/pch")
          target_compile_options(${CURRENT_TARGET} PRIVATE "/Yu${PCH_NAME};/Fp${PCH_DIR}/${PCH_NAME}.pch")
          set_property(SOURCE ${PCH_SOURCE_FILE} APPEND PROPERTY COMPILE_FLAGS "/Yc${PCH_NAME}")
          if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.15)
            set_property(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} APPEND_STRING PROPERTY ADDITIONAL_CLEAN_FILES "${PCH_DIR}/${PCH_NAME}.pch;")
          else()
            set_property(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} APPEND_STRING PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${PCH_DIR}/${PCH_NAME}.pch;")
          endif()
        endif()
        target_compile_options(${CURRENT_TARGET} PRIVATE "/FI${PCH_NAME};")
      else()
        target_compile_options(${CURRENT_TARGET} PRIVATE "-include${PCH_NAME}")#强制包含预编译头文件
      endif()
    endif()
    #############################################################################################################################
    if(${CURRENT_TARGET_TYPE} STREQUAL "STATIC_LIBRARY")#静态库
      target_compile_definitions(${CURRENT_TARGET} PUBLIC "USE_${CURRENT_SOURCE_FOLDER}_STATIC;")
    elseif(${CURRENT_TARGET_TYPE} STREQUAL "MODULE_LIBRARY" OR ${CURRENT_TARGET_TYPE} STREQUAL "SHARED_LIBRARY")#插件库|动态库
      target_compile_definitions(${CURRENT_TARGET} PRIVATE "${CURRENT_SOURCE_FOLDER}_EXPORTS;")
    endif()
    #############################################################################################################################
    if(EXISTS "${PUBLIC_HEADER_DIR}/${CURRENT_SOURCE_FOLDER}")
      target_include_directories(${CURRENT_TARGET} PRIVATE "${PUBLIC_HEADER_DIR}/${CURRENT_SOURCE_FOLDER}")
    endif()
    target_include_directories(${CURRENT_TARGET} PUBLIC "${PUBLIC_HEADER_DIR}")
    if(NOT ${PRIVATE_HEADER_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
      target_include_directories(${CURRENT_TARGET} PRIVATE "${PRIVATE_HEADER_DIR}")
    endif()
    target_include_directories(${CURRENT_TARGET} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")#包含当前源目录
    target_include_directories(${CURRENT_TARGET} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")#包含当前构建目录
    #############################################################################################################################
    configureBoostModules()#处理Boost依赖
    configureQtModules()#处理Qt依赖
    configureThirdPartyList()#处理三方库依赖
    configureCompanyLicense()#配置授权信息
    #############################################################################################################################
    set_property(TARGET ${CURRENT_TARGET} PROPERTY VS_GLOBAL_${CMAKE_PROJECT_NAME} "${CMAKE_INSTALL_PREFIX}")#
    if(${CURRENT_TARGET_TYPE} STREQUAL "EXECUTABLE")#可执行程序
      set_property(TARGET ${CURRENT_TARGET} PROPERTY DEBUG_POSTFIX "d")#设置可执行程序(调试版本)后缀
      #GUI程序设置程序入口、获取UAC权限
      if(MSVC AND DEFINED USE_GUI)
        set_property(TARGET ${CURRENT_TARGET} APPEND_STRING PROPERTY LINK_FLAGS " /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup /level='requireAdministrator'")#GUI程序配置
      endif()
    else()
      set_property(TARGET ${CURRENT_TARGET} PROPERTY OUTPUT_NAME "${CURRENT_TARGET}${DEFAULT_VERSION_INFORMATION}")
    endif()
    #############################################################################################################################
    configureTargetForInstall()
  endif()
endmacro()

#配置Protobuf项目
macro(configureAsProtobufTarget)
  if(TARGET "${CURRENT_TARGET}")
    #############################################################################################################################
    configureTargetForStructure()
    #############################################################################################################################
    protobuf_generate(TARGET "${CURRENT_TARGET}"
        #OUT_VAR PROTO_SOURCE_FILES
        #PROTOC_OUT_DIR "${PROTO_BINARY_DIR}"
        #LANGUAGE "cpp"
        #IMPORT_DIRS "proto"
        #GENERATE_EXTENSIONS ".pb.h;.pb.cc"
    )
    
    target_include_directories("${CURRENT_TARGET}" PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>")
    target_include_directories("${CURRENT_TARGET}" PRIVATE "${Protobuf_INCLUDE_DIRS}")
    target_link_libraries("${CURRENT_TARGET}" PRIVATE "${Protobuf_LIBRARIES}")
    #############################################################################################################################
    if(gRPC_FOUND)
      if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.21.0)
        protobuf_generate(TARGET "${CURRENT_TARGET}"
            #OUT_VAR PROTO_SOURCE_FILES
            PROTOC_OUT_DIR "${PROTO_BINARY_DIR}"
            LANGUAGE "grpc"
            PLUGIN "protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
            #PLUGIN_OPTIONS generate_mock_code=true
            #IMPORT_DIRS "proto"
            GENERATE_EXTENSIONS ".grpc.pb.h;.grpc.pb.cc"
        )
        
        target_link_libraries("${CURRENT_TARGET}" PRIVATE "gRPC::grpc++")
      else()
        message(WARNING "CURRENT CMAKE_VERSION: (${CMAKE_VERSION}) VERSION_REQUIRED: (3.21.0) OR HIGHER FOR GRPC PROJECT")
      endif()
    else()
      message(WARNING "UNKNOWN GRPC_VERSION")
    endif()
    #############################################################################################################################
    configureTargetForInstall()
    #############################################################################################################################
  endif()
endmacro()

#配置CSharp项目
macro(configureAsCSharpTarget)
  if(TARGET "${CURRENT_TARGET}")
    #set_property(TARGET ${CURRENT_TARGET} PROPERTY VS_DOTNET_REFERENCES_COPY_LOCAL "OFF")
    #############################################################################################################################
    configureTargetForStructure()
    #############################################################################################################################
    target_sources(${CURRENT_TARGET} PRIVATE "${CSHARP_SOURCE_FILES}")
    #############################################################################################################################
    configureTargetForInstall()
    #############################################################################################################################
  endif()
endmacro()

#配置Java项目
macro(configureAsJavaTarget)
  if(TARGET "${CURRENT_TARGET}")
    #############################################################################################################################
    configureTargetForStructure()
    #############################################################################################################################
    configureTargetForInstall()
    #############################################################################################################################
  endif()
endmacro()

#配置Python项目
macro(configureAsPythonTarget)
  if(TARGET "${CURRENT_TARGET}")
    #############################################################################################################################
    configureTargetForStructure()
    #############################################################################################################################
    configureTargetForInstall()
    #############################################################################################################################
  endif()
endmacro()

#配置SWIG项目
macro(configureAsSWIGTarget)
  if(TARGET "${CURRENT_TARGET}")
    #############################################################################################################################
    configureAsCXXTarget()
    #############################################################################################################################
    configureTargetForStructure()
    #############################################################################################################################
    set_property(TARGET ${CURRENT_TARGET} PROPERTY SWIG_USE_TARGET_INCLUDE_DIRECTORIES "TRUE")
    #############################################################################################################################
    #这里使SWIG项目永远需要重新生成,保证对应目标的源文件最新
    add_custom_command(TARGET "${CURRENT_TARGET}"
        POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E touch_nocreate "${SWIG_MODULE_FILE}"
    )
    #############################################################################################################################
    configureTargetForInstall()
    #############################################################################################################################
  endif()
endmacro()

#指定生成C/C++可执行程序
macro(generateExecutableProgram)
  collectInformation()
  prepareForCXXTarget()#文件归集
  if(SOURCE_FILES)
    add_executable(${CURRENT_TARGET})#生成C/C++可执行程序
    configureAsCXXTarget()#配置目标项目
  else()
    message(WARNING "SOURCE_FILES not found")
  endif()
endmacro()

#指定生成常规动态链接库
macro(generateDynamicLibrary)
  collectInformation()
  prepareForCXXTarget()#文件归集
  if(SOURCE_FILES)
    add_library(${CURRENT_TARGET} SHARED)#生成动态库
    configureAsCXXTarget()#配置目标项目
  else()
    message(WARNING "SOURCE_FILES not found")
  endif()
endmacro()

#指定生成静态链接库
macro(generateStaticLibrary)
  collectInformation()
  prepareForCXXTarget()#文件归集
  if(SOURCE_FILES)
    add_library(${CURRENT_TARGET} STATIC)#生成静态库
    configureAsCXXTarget()#配置目标项目
  else()
    message(WARNING "SOURCE_FILES not found")
  endif()
endmacro()

#指定生成插件动态链接库
macro(generatePluginLibrary)
  collectInformation()
  prepareForCXXTarget()#文件归集
  if(SOURCE_FILES)
    add_library(${CURRENT_TARGET} MODULE)#生成插件库
    configureAsCXXTarget()#配置目标项目
  else()
    message(WARNING "SOURCE_FILES not found")
  endif()
endmacro()

#生成Protobuf动态库
macro(generateProtobufLibrary)
  collectInformation()
  if(Protobuf_FOUND)
    prepareForProtobufTarget()#文件归集
    if(PROTO_FILES)
      add_library(${CURRENT_TARGET} OBJECT ${PROTO_FILES})#生成Proto动态库
      configureAsProtobufTarget()#配置目标项目
    else()
      message(WARNING "PROTO_FILES(*.proto) not found")
    endif()
  endif()
endmacro()

#指定生成CSharp可执行程序
macro(generateCSharpProgram)
  collectInformation()
  if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.8.2)
    if(CMAKE_CSharp_COMPILER)
      prepareForCSharpTarget()#文件归集
      if(CSHARP_SOURCE_FILES)
        add_executable(${CURRENT_TARGET})#生成CSharp可执行程序
        configureAsCSharpTarget()#配置目标项目
      else()
        message(WARNING "CSHARP_SOURCE_FILES(*.cs) not found")
      endif()
    else()
      message(WARNING "CMAKE_CSharp_COMPILER not found")
    endif()
  else()
    message(FATAL_ERROR "CURRENT CMAKE_VERSION: (${CMAKE_VERSION}) VERSION_REQUIRED: (3.8.2) OR HIGHER FOR CSHARP PROJECT")
  endif()
endmacro()

#指定生成CSharp库
macro(generateCSharpLibrary)
  collectInformation()
  if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.8.2)
    if(CMAKE_CSharp_COMPILER)
      prepareForCSharpTarget()#文件归集
      if(CSHARP_SOURCE_FILES)
        add_library(${CURRENT_TARGET} SHARED)#生成CSharp动态库
        configureAsCSharpTarget()#配置目标项目
      else()
        message(WARNING "CSHARP_SOURCE_FILES(*.cs) not found")
      endif()
    else()
      message(WARNING "CMAKE_CSharp_COMPILER not found")
    endif()
  else()
    message(FATAL_ERROR "CURRENT CMAKE_VERSION: (${CMAKE_VERSION}) VERSION_REQUIRED: (3.8.2) OR HIGHER FOR CSHARP PROJECT")
  endif()
endmacro()

#指定生成Java
macro(generateJavaPackage)
  collectInformation()
  if(Java_FOUND)
    prepareForJavaTarget()#文件归集
    if(JAVA_SOURCE_FILES)
      if(EXISTS "${PROJECT_SOURCE_DIR}/Manifest.txt.in")
        set(CURRENT_TARGET_MANIFEST_TXT "${CMAKE_CURRENT_BINARY_DIR}/Manifest.txt")
        configure_file("${PROJECT_SOURCE_DIR}/Manifest.txt.in" "${CURRENT_TARGET_MANIFEST_TXT}")
      endif()
      add_jar(${CURRENT_TARGET} SOURCES "${JAVA_SOURCE_FILES}" INCLUDE_JARS ${CURRENT_JAVA_INCLUDE_PATHS} ENTRY_POINT "${CURRENT_JAVA_ENTRY_POINT}" MANIFEST "${CURRENT_TARGET_MANIFEST_TXT}")#生成Jar包
      configureAsJavaTarget()#配置目标项目
    else()
      message(WARNING "JAVA_SOURCE_FILES(*.java) not found")
    endif()
  else()
    message(FATAL_ERROR "Module[\"Java\"] not found")
  endif()
endmacro()

#指定生成Python可执行程序
macro(generatePythonProgram)
  collectInformation()
  prepareForPythonTarget()#文件归集
  add_custom_target(${CURRENT_TARGET} SOURCES "${PYTHON_SOURCE_FILES}")#组织Python源代码
  configureAsPythonTarget()#配置目标项目
endmacro()

#指定生成常规Python动态链接库
macro(generatePythonLibrary)
  collectInformation()
  generateDynamicLibrary()
  if(TARGET "${CURRENT_TARGET}")
    set_property(TARGET ${CURRENT_TARGET} PROPERTY RUNTIME_OUTPUT_NAME "${CURRENT_TARGET}")#
    set_property(TARGET ${CURRENT_TARGET} PROPERTY SUFFIX ".pyd")#
  endif()
endmacro()

#指定生成CSharp包装库
macro(generateSWIGLibraryForCSharp)
  collectInformation()
  if(SWIG_FOUND)
    set(SWIG_LANGUAGE "CSharp")
    prepareForSWIGTarget()
    if(SWIG_MODULE_FILE)
      swig_add_library(${CURRENT_TARGET} TYPE "SHARED" LANGUAGE "csharp" SOURCES "${SWIG_MODULE_FILE}")
      configureAsSWIGTarget()
      add_custom_command(TARGET "${CURRENT_TARGET}"
          POST_BUILD
          COMMAND "${CMAKE_CSharp_COMPILER}" -target:library -out:${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CURRENT_TARGET}${CMAKE_SHARED_MODULE_SUFFIX} -recurse:"${SWIG_TARGET_SOURCE_OUTPUT_DIR}/*.cs" "${CSHARP_SOURCE_FILES}"
          COMMENT "Generated ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CURRENT_TARGET}${CMAKE_SHARED_MODULE_SUFFIX}"
          #
          COMMAND "${CMAKE_COMMAND}" -E rm -rf "${CMAKE_CURRENT_BINARY_DIR}/source"
          #删除生成的C/C++文件
          COMMAND "${CMAKE_COMMAND}" -E rm -rf "${CMAKE_CURRENT_BINARY_DIR}/generated_source"
      )
    else()
      message(WARNING "SWIG_MODULE_FILE(*.i) not found")
    endif()
  endif()
endmacro()

#指定生成Java包装库
macro(generateSWIGLibraryForJava)
  collectInformation()
  if(SWIG_FOUND)
    set(SWIG_LANGUAGE "Java")
    if(Java_FOUND)
      prepareForSWIGTarget()
      if(SWIG_MODULE_FILE)
        swig_add_library(${CURRENT_TARGET} TYPE "SHARED" LANGUAGE "java" SOURCES "${SWIG_MODULE_FILE}")
        if(TARGET "${CURRENT_TARGET}")
          set_property(TARGET ${CURRENT_TARGET} PROPERTY RUNTIME_OUTPUT_NAME "${CURRENT_TARGET}")#
        endif()
        configureAsSWIGTarget()
        add_custom_command(TARGET "${CURRENT_TARGET}"
            POST_BUILD
            #
            COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/java"
            #编译java
            COMMAND "${Java_JAVAC_EXECUTABLE}" ${CMAKE_JAVA_COMPILE_FLAGS} -d "${CMAKE_CURRENT_BINARY_DIR}/java" -sourcepath "${SWIG_TARGET_SOURCE_OUTPUT_DIR}" "${SWIG_TARGET_SOURCE_OUTPUT_DIR}/*.java" ${JAVA_SOURCE_FILES}
            #生成jar包
            COMMAND "${Java_JAR_EXECUTABLE}" cf "${CMAKE_JAVA_TARGET_OUTPUT_DIR}/${CURRENT_TARGET}.jar" -C "${CMAKE_CURRENT_BINARY_DIR}/java" ${SWIG_TARGET_SOURCE_STRUCTURE}
            COMMENT "Generated ${CMAKE_JAVA_TARGET_OUTPUT_DIR}/${CURRENT_TARGET}.jar"
            #删除Java编译生成的中间文件
            COMMAND "${CMAKE_COMMAND}" -E rm -rf "${CMAKE_CURRENT_BINARY_DIR}/java"
            #删除生成的java源码,防止无关代码残留,若需要查看包装代码请注释此行
            COMMAND "${CMAKE_COMMAND}" -E rm -rf "${CMAKE_CURRENT_BINARY_DIR}/source"
            #删除生成的C/C++文件
            COMMAND "${CMAKE_COMMAND}" -E rm -rf "${CMAKE_CURRENT_BINARY_DIR}/generated_source"
        )
      else()
        message(WARNING "SWIG_MODULE_FILE(*.i) not found")
      endif()
    else()
      message(FATAL_ERROR "Module[\"Java\"] not found")
    endif()
  endif()
endmacro()

#指定生成Python包装库
macro(generateSWIGLibraryForPython)
  collectInformation()
  if(SWIG_FOUND)
    set(SWIG_LANGUAGE "Python")
    prepareForSWIGTarget()
    if(SWIG_MODULE_FILE)
      swig_add_library(${CURRENT_TARGET} TYPE "SHARED" LANGUAGE "python" SOURCES "${SWIG_MODULE_FILE}")
      if(TARGET "${CURRENT_TARGET}")
        set_property(TARGET ${CURRENT_TARGET} PROPERTY PREFIX "${CMAKE_SHARED_MODULE_PREFIX_PYTHON}")#
        set_property(TARGET ${CURRENT_TARGET} PROPERTY RUNTIME_OUTPUT_NAME "${CURRENT_TARGET}")#
        set_property(TARGET ${CURRENT_TARGET} PROPERTY SUFFIX "${CMAKE_SHARED_MODULE_SUFFIX_PYTHON}")#
      endif()
      configureAsSWIGTarget()
      add_custom_command(TARGET "${CURRENT_TARGET}"
          POST_BUILD
          #删除生成的C/C++文件
          COMMAND "${CMAKE_COMMAND}" -E rm -rf "${CMAKE_CURRENT_BINARY_DIR}/generated_source"
      )
    else()
      message(WARNING "SWIG_MODULE_FILE(*.i) not found")
    endif()
  endif()
endmacro()
