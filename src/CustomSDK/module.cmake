if(${CMAKE_VERSION} VERSION_GREATER 3.8.2 OR ${CMAKE_VERSION} VERSION_EQUAL 3.8.2)#此模块要求CMake版本至少3.8.2
  if(${CMAKE_VERSION} VERSION_GREATER 3.9 OR ${CMAKE_VERSION} VERSION_EQUAL 3.9)#
    cmake_policy(SET CMP0068 NEW)
  endif()
  if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})#编译环境与目标配置初始化
    set(CMAKE_WARN_VS10 OFF CACHE BOOL "CMAKE_WARN_VS10")#忽略将不支持VS2010的警告

    set(CMAKE_C_STANDARD "11")#设置语言标准要求"C11"
    set(CMAKE_CXX_STANDARD "11")#设置语言标准要求"C++11"

    set(CMAKE_C_STANDARD_REQUIRED "ON")#设置语言标准要求必须满足
    set(CMAKE_CXX_STANDARD_REQUIRED "ON")#设置语言标准要求必须满足

    set(CMAKE_POSITION_INDEPENDENT_CODE "TRUE")#生成位置无关代码
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
        set(MSVC_TOOLSET_VERSION "140" CACHE STRING "MSVC_TOOLSET_VERSION")
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

      set(SYMBOL_SEARCH_LIBRARY " /LIBPATH:")
    else()#类Unix平台
      #确定C/C++运行时库版本
      set(CRT_VERSION_NAME "${CMAKE_CXX_COMPILER_ID}" CACHE STRING "CRT_VERSION_NAME")
      #确定处理器架构
      set(PLATFORM "${CMAKE_SYSTEM_PROCESSOR}" CACHE STRING "PLATFORM")
      #配置运行时库加载路径
      set(CMAKE_BUILD_WITH_INSTALL_RPATH "TRUE")
      #set(CMAKE_INSTALL_RPATH_USE_LINK_PATH "TRUE")
      #set(CMAKE_SKIP_BUILD_RPATH TRUE)
      #set(CMAKE_SKIP_INSTALL_RPATH TRUE)
      set(CMAKE_INSTALL_RPATH ".;../bin;../lib/${CRT_VERSION_NAME}_${PLATFORM};../lib;../thirdparty/bin;")
      #
      if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        if(CMAKE_SYSTEM_PROCESSOR MATCHES "mips64")
          set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic -static-libgcc -mxgot")
        else()
          set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic -static-libgcc -static-libstdc++")
        endif()
      elseif(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
      endif()

      set(SYMBOL_SEARCH_LIBRARY " -L")
    endif()

    #可执行程序输出目录
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" CACHE PATH "CMAKE_RUNTIME_OUTPUT_DIRECTORY")
    #动态库输出目录
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" CACHE PATH "CMAKE_LIBRARY_OUTPUT_DIRECTORY")
    #静态库输出目录
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE PATH "CMAKE_ARCHIVE_OUTPUT_DIRECTORY")
    #程序数据库文件
    set(CMAKE_PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/pdb" CACHE PATH "CMAKE_PDB_OUTPUT_DIRECTORY")
    #Java
    set(CMAKE_JAVA_TARGET_OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin" CACHE PATH "CMAKE_JAVA_TARGET_OUTPUT_DIR")

    #允许使用自定义目录
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    #设置CMake预定义文件夹名称
    set(PREDEFINED_TARGETS_FOLDER "_CMakePredefinedTargets")
    set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER ${PREDEFINED_TARGETS_FOLDER})

    #
    if(${CMAKE_VERSION} VERSION_GREATER 3.9 OR ${CMAKE_VERSION} VERSION_EQUAL 3.9)
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

    include(CheckLanguage)

    #Java环境初始化
    find_package(Java)
    if(Java_FOUND)
      #Java编译指定为utf8编码,防止源码文件编码格式不符导致编译报错
      list(APPEND CMAKE_JAVA_COMPILE_FLAGS "-encoding" "utf8")
      include(UseJava)
    endif()

    #CSharp环境初始化
    if(${CMAKE_VERSION} VERSION_GREATER 3.8.2 OR ${CMAKE_VERSION} VERSION_EQUAL 3.8.2)
      check_language("CSharp")
      if(CMAKE_CSharp_COMPILER)
        enable_language("CSharp")
        include(CSharpUtilities)

        set(CMAKE_CSharp_FLAGS "/langversion:default /errorreport:prompt")
        set(CMAKE_DOTNET_TARGET_FRAMEWORK_VERSION "v4.0" CACHE STRING "CMAKE_DOTNET_TARGET_FRAMEWORK_VERSION")
      endif()
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
      set(CMAKE_PREFIX_PATH "$ENV{BOOST_DIR}")
      set(BOOST_ROOT "$ENV{BOOST_DIR}")
      set(BOOST_INCLUDEDIR "$ENV{BOOST_DIR}/include")
      if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")#MSVC编译器
        set(BOOST_LIBRARYDIR "$ENV{BOOST_DIR}/lib/${CRT_VERSION_NAME}/${PLATFORM}")
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
  if(DEFINED THIRD_LIBRARY_LIST )
    if(DEFINED ENV{ThirdParty})
      set_property(TARGET ${CURRENT_TARGET} PROPERTY VS_GLOBAL_ThirdParty "$ENV{ThirdParty}")#设置VS中环境变量:$(ThirdParty)=$ENV{ThirdParty}
      message("\tTHIRD_LIBRARY_LIST:${THIRD_LIBRARY_LIST}")#输出三方库列表
      foreach(CURRENT_LIBRARY_NAME ${THIRD_LIBRARY_LIST})
        #添加三方库搜索路径
        set(CURRENT_LIBRARY_ROOT "")
        if(CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
          #设置当前库的根路径
          if(${CURRENT_LIBRARY_NAME} STREQUAL "soci")
            set(CURRENT_LIBRARY_ROOT "$ENV{ThirdParty}/soci")
          else()
            set(CURRENT_LIBRARY_ROOT "$ENV{ThirdParty}/${CURRENT_LIBRARY_NAME}")
          endif()
          #添加头文件和静态库搜索路径
          target_include_directories(${CURRENT_TARGET} SYSTEM PRIVATE "${CURRENT_LIBRARY_ROOT}/include")
          set_property(TARGET ${CURRENT_TARGET} APPEND_STRING PROPERTY LINK_FLAGS "${SYMBOL_SEARCH_LIBRARY}${CURRENT_LIBRARY_ROOT}/lib")
          #链接静态库
          if(${CURRENT_LIBRARY_NAME} MATCHES "Qtnribbon")
            target_link_libraries(${CURRENT_TARGET} PRIVATE "qtnribbon")
          elseif(${CURRENT_LIBRARY_NAME} MATCHES "tbb")
             target_link_libraries(${CURRENT_TARGET} PRIVATE "tbb;tbbmalloc;tbbmalloc_proxy;")
          elseif(${CURRENT_LIBRARY_NAME} MATCHES "soci")
            target_link_libraries(${CURRENT_TARGET} PRIVATE "soci_core")
          elseif(${CURRENT_LIBRARY_NAME} MATCHES "iconv")
            target_link_libraries(${CURRENT_TARGET} PRIVATE "iconv")
          elseif(${CURRENT_LIBRARY_NAME} MATCHES "sqlite3")
            target_link_libraries(${CURRENT_TARGET} PRIVATE "sqlite3")
          elseif(${CURRENT_LIBRARY_NAME} MATCHES "pcap")
            target_link_libraries(${CURRENT_TARGET} PRIVATE "pcap")
          elseif(${CURRENT_LIBRARY_NAME} MATCHES "gtest")
            target_link_libraries(${CURRENT_TARGET} PRIVATE "gtest")
          endif()
        elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
          #设置当前库的根路径
          if(${CURRENT_LIBRARY_NAME} STREQUAL "qwt" AND ${CRT_VERSION_NAME} MATCHES "vc100")
            set(CURRENT_LIBRARY_ROOT "$ENV{ThirdParty}/qwt-6.0.1")
          elseif(${CURRENT_LIBRARY_NAME} STREQUAL "soci")
            set(CURRENT_LIBRARY_ROOT "$ENV{ThirdParty}/soci")
          else()
           set(CURRENT_LIBRARY_ROOT "$ENV{ThirdParty}/${CURRENT_LIBRARY_NAME}")
          endif()
          #添加头文件和静态库搜索路径
          target_include_directories(${CURRENT_TARGET} SYSTEM PRIVATE ${CURRENT_LIBRARY_ROOT}/include)
          if(EXISTS "${CURRENT_LIBRARY_ROOT}/lib/${CRT_VERSION_NAME}/${PLATFORM}")
            set_property(TARGET ${CURRENT_TARGET} APPEND_STRING PROPERTY LINK_FLAGS "${SYMBOL_SEARCH_LIBRARY}${CURRENT_LIBRARY_ROOT}/lib/${CRT_VERSION_NAME}/${PLATFORM}")
            set_property(TARGET ${CURRENT_TARGET} APPEND_STRING PROPERTY LINK_FLAGS "${SYMBOL_SEARCH_LIBRARY}${CURRENT_LIBRARY_ROOT}/lib/${CRT_VERSION_NAME}/${PLATFORM}/${CMAKE_CFG_INTDIR}")
            set_property(TARGET ${CURRENT_TARGET} APPEND_STRING PROPERTY LINK_FLAGS_RELWITHDEBINFO "${SYMBOL_SEARCH_LIBRARY}${CURRENT_LIBRARY_ROOT}/lib/${CRT_VERSION_NAME}/${PLATFORM}/Release")
          elseif(EXISTS "${CURRENT_LIBRARY_ROOT}/lib")
            set_property(TARGET ${CURRENT_TARGET} APPEND_STRING PROPERTY LINK_FLAGS "${SYMBOL_SEARCH_LIBRARY}${CURRENT_LIBRARY_ROOT}/lib")
            set_property(TARGET ${CURRENT_TARGET} APPEND_STRING PROPERTY LINK_FLAGS "${SYMBOL_SEARCH_LIBRARY}${CURRENT_LIBRARY_ROOT}/lib/${CMAKE_CFG_INTDIR}")
            set_property(TARGET ${CURRENT_TARGET} APPEND_STRING PROPERTY LINK_FLAGS_RELWITHDEBINFO "${SYMBOL_SEARCH_LIBRARY}${CURRENT_LIBRARY_ROOT}/lib/Release")
          endif()
          #链接静态库
          if(${CURRENT_LIBRARY_NAME} MATCHES "Qtnribbon")
            target_link_libraries(${CURRENT_TARGET} PRIVATE debug "qtnribbond3" optimized "qtnribbon3")
          elseif(${CURRENT_LIBRARY_NAME} MATCHES "qwt")
            target_link_libraries(${CURRENT_TARGET} PRIVATE debug "qwtd" optimized "qwt")
          elseif(${CURRENT_LIBRARY_NAME} MATCHES "gtest" AND ${CRT_VERSION_NAME} MATCHES "vc140")
            target_link_libraries(${CURRENT_TARGET} PRIVATE debug "gtestd" optimized "gtest")
          elseif(${CURRENT_LIBRARY_NAME} MATCHES "lua53" AND ${CRT_VERSION_NAME} MATCHES "vc140")
            target_link_libraries(${CURRENT_TARGET} PRIVATE "lua53")
          elseif(${CURRENT_LIBRARY_NAME} MATCHES "sqlite3")
            #target_link_libraries(${CURRENT_TARGET} PRIVATE "sqlite3")
          elseif(${CURRENT_LIBRARY_NAME} MATCHES "soci")
            target_link_libraries(${CURRENT_TARGET} PRIVATE debug "soci_core_3_2d;soci_sqlite3_3_2d" optimized "soci_core_3_2;soci_sqlite3_3_2")
          elseif(${CURRENT_LIBRARY_NAME} MATCHES "libcef")
            target_link_libraries(${CURRENT_TARGET} PRIVATE "libcef;libcef_dll_wrapper")
          elseif(${CURRENT_LIBRARY_NAME} MATCHES "pcap")
            target_link_libraries(${CURRENT_TARGET} PRIVATE "wpcap")
          elseif(${CURRENT_LIBRARY_NAME} MATCHES "tbb")
            target_link_libraries(${CURRENT_TARGET} PRIVATE debug "tbb_debug;tbbmalloc_debug;tbbmalloc_proxy_debug" optimized "tbb;tbbmalloc;tbbmalloc_proxy")
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
    if(DEFINED ENV{BUILD_XSIM_PRODUCT})#XSimStudio
      if(CMAKE_SYSTEM_NAME MATCHES "Linux")
        set(LICENSE_PRODUCT_ID "2003")
      elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
        set(LICENSE_PRODUCT_ID "2002")
      endif()
      list(APPEND LICENSE_MESSAGE "BUILD_XSIM_PRODUCT:LICENSE_PRODUCT_ID=${LICENSE_PRODUCT_ID}\t")
    elseif(DEFINED ENV{BUILD_LINK_PRODUCT})#XSimLink
      if(CMAKE_SYSTEM_NAME MATCHES "Linux")
        set(LICENSE_PRODUCT_ID "1001")
      elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
        set(LICENSE_PRODUCT_ID "1000")
      endif()
      list(APPEND LICENSE_MESSAGE "BUILD_LINK_PRODUCT:LICENSE_PRODUCT_ID=${LICENSE_PRODUCT_ID}\t")
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
        set_property(TARGET "${IMPORTED_TARGET_NAME}" PROPERTY IMPORTED_CONFIGURATIONS "${CMAKE_CONFIGURATION_TYPES}")
        set_property(TARGET "${IMPORTED_TARGET_NAME}" PROPERTY INTERFACE_INCLUDE_DIRECTORIES "$ENV{SecondParty}/include")
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
              set_property(TARGET "${IMPORTED_TARGET_NAME}" PROPERTY IMPORTED_IMPLIB_${CONFIG_TYPE_UPPER_CASE} "${${IMPORTED_TARGET_IMPLIB}}")
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
              set_property(TARGET "${IMPORTED_TARGET_NAME}" PROPERTY IMPORTED_LOCATION_${CONFIG_TYPE_UPPER_CASE} "${${IMPORTED_TARGET_LOCATION}}")
              install(FILES "$<TARGET_FILE:${IMPORTED_TARGET_NAME}>" DESTINATION "bin" CONFIGURATIONS "${CONFIG_TYPE_UPPER_CASE}")#
            endif()
        endforeach()
        message("")
      else()
        message(FATAL_ERROR "${IMPORTED_TARGET_NAME} not imported,libraries cannot be found")
      endif()
    else()
      message(FATAL_ERROR "ENV{SecondParty} not defined to import target:${IMPORTED_TARGET_NAME}")
    endif()
  endif()
endmacro()

#导入BasicFramework
macro(addBasicGroup)
  importTarget("TopSimRuntime")
  importTarget("TopSimDataInterface")
  importTarget("TopSimIDL")
endmacro()

#导入LinkStudioFramework
macro(addLinkGroup)
  addBasicGroup()

  importTarget("TopSimRPC")
  importTarget("TopSimDataInterfaceCWarp")
  importTarget("TopSimDataInterfacePydWarp")
endmacro()

#导入BasicUIFramework
macro(addUIGroup)
  addBasicGroup()

  importTarget("HRUtil")
  importTarget("HRComModules")
  importTarget("HRControls")
  importTarget("HRUICommon")
endmacro()

#文件分类归集
macro(prepareTarget)
  get_filename_component(CURRENT_TARGET ${CMAKE_CURRENT_LIST_DIR} NAME_WE)#获取当前目标名称
  get_filename_component(CURRENT_SOURCE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)#获取当前源码文件夹名称
  get_property(PARENT_DIRECTORY DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY PARENT_DIRECTORY)#获取父目录
#############################################################################################################################
  #C/C++
  file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx")#归集源文件
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
  #Java
  file(GLOB_RECURSE JAVA_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.java")#归集Java源文件
#############################################################################################################################
  #CSharp
  file(GLOB_RECURSE CSHARP_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cs")#归集CSharp源文件
#############################################################################################################################
  #Python
  file(GLOB_RECURSE PYTHON_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.py")#归集Python源文件
#############################################################################################################################
endmacro()

#配置目标项目
macro(configureTarget)
#############################################################################################################################
  get_property(CURRENT_TARGET_TYPE TARGET ${CURRENT_TARGET} PROPERTY TYPE)#获取目标类型
  message(STATUS "TARGET:${CURRENT_TARGET}\tTYPE:${CURRENT_TARGET_TYPE}")#输出当前目标名称
  string(REPLACE "${PROJECT_SOURCE_DIR}" "${CMAKE_PROJECT_NAME}" FOLDER_PATH ${PARENT_DIRECTORY})#获取相对路径
  set_property(TARGET ${CURRENT_TARGET} PROPERTY FOLDER "${FOLDER_PATH}")#保持项目目录结构
#############################################################################################################################
  if(NOT CURRENT_TARGET_TYPE STREQUAL "UTILITY")#非Java/Python代码
#############################################################################################################################
    #公共部分代码目录
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/public/include/${CURRENT_SOURCE_FOLDER}")
      set(PUBLIC_HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/public/include")
    elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/public/${CURRENT_SOURCE_FOLDER}")
      set(PUBLIC_HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/public")
    else()
      set(PUBLIC_HEADER_DIR "${PARENT_DIRECTORY}")
    endif()
#############################################################################################################################
    #私有部分代码目录
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/private/src/${CURRENT_SOURCE_FOLDER}")
      set(PRIVATE_HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/private/src/${CURRENT_SOURCE_FOLDER}")
    elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/private/src")
      set(PRIVATE_HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/private/src")
    elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/private")
      set(PRIVATE_HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/private")
    else()
      set(PRIVATE_HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
    endif()
    if(NOT CSHARP_SOURCE_FILES)#C/C++
#############################################################################################################################
      target_sources(${CURRENT_TARGET} PRIVATE ${SOURCE_FILES} ${HEADER_FILES} ${FORM_FILES} ${RESOURCE_FILES})
#############################################################################################################################
      if(NOT "${PRIVATE_HEADER_DIR}" STREQUAL "${PUBLIC_HEADER_DIR}/${CURRENT_SOURCE_FOLDER}")#经过设计的源码目录(public|private),具有较复杂的目录结构
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
      set(PCH_NAME "stdafx.h")
      if(EXISTS "${PRIVATE_HEADER_DIR}/${PCH_NAME}")
        set(PCH_HEADER_FILE "${PRIVATE_HEADER_DIR}/stdafx.h")
        set(PCH_SOURCE_FILE "${PRIVATE_HEADER_DIR}/stdafx.cpp")
      endif()
      if(MSVC)
        #预编译头处理
        if(PCH_HEADER_FILE)
          set(PCH_DIR "${CMAKE_CURRENT_BINARY_DIR}/pch/${CMAKE_CFG_INTDIR}")
          file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/pch")
          target_compile_options(${CURRENT_TARGET} PRIVATE "/Yu${PCH_NAME};/FI${PCH_NAME};/Fp${PCH_DIR}/${PCH_NAME}.pch")
          set_property(SOURCE "${PCH_SOURCE_FILE}" PROPERTY COMPILE_FLAGS "/Yc${PCH_NAME}")
          if(${CMAKE_VERSION} VERSION_GREATER 3.15 OR ${CMAKE_VERSION} VERSION_EQUAL 3.15)
            set_directory_properties(PROPERTIES ADDITIONAL_CLEAN_FILES "${PCH_DIR}/${PCH_NAME}.pch")
          else()
            set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${PCH_DIR}/${PCH_NAME}.pch")
          endif()
        endif()
      else()
        #预编译头处理
        if(PCH_HEADER_FILE)
          target_compile_options(${CURRENT_TARGET} PRIVATE "-include${PCH_NAME}")#强制包含预编译头文件
        endif()
      endif()
#############################################################################################################################
      target_include_directories(${CURRENT_TARGET} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")#包含当前源目录
      target_include_directories(${CURRENT_TARGET} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")#包含当前构建目录
#############################################################################################################################
      set_property(TARGET ${CURRENT_TARGET} PROPERTY VS_GLOBAL_${CMAKE_PROJECT_NAME} "${CMAKE_INSTALL_PREFIX}")#
#############################################################################################################################
      if(EXISTS "${PUBLIC_HEADER_DIR}/${CURRENT_SOURCE_FOLDER}")
        target_include_directories(${CURRENT_TARGET} PRIVATE "${PUBLIC_HEADER_DIR}/${CURRENT_SOURCE_FOLDER}")
      endif()
      target_include_directories(${CURRENT_TARGET} PUBLIC "${PUBLIC_HEADER_DIR}")
      if(NOT ${PRIVATE_HEADER_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
        target_include_directories(${CURRENT_TARGET} PRIVATE "${PRIVATE_HEADER_DIR}")
      endif()
#############################################################################################################################
      configureBoostModules()#处理Boost依赖
      configureQtModules()#处理Qt依赖
      configureThirdPartyList()#处理三方库依赖
      configureCompanyLicense()#配置授权信息
#############################################################################################################################
    elseif(CSHARP_SOURCE_FILES)#CSharp
      target_sources(${CURRENT_TARGET} PRIVATE "${CSHARP_SOURCE_FILES}")
    endif()
#############################################################################################################################
    if(${CURRENT_TARGET_TYPE} STREQUAL "STATIC_LIBRARY")#静态库
      target_compile_definitions(${CURRENT_TARGET} PUBLIC "USE_${CURRENT_SOURCE_FOLDER}_STATIC;")
      if(${CMAKE_CURRENT_SOURCE_DIR} MATCHES "${PROJECT_SOURCE_DIR}/Libraries")
        if(NOT ${PUBLIC_HEADER_DIR} STREQUAL "${PARENT_DIRECTORY}")
          install(DIRECTORY "${PUBLIC_HEADER_DIR}/${CURRENT_SOURCE_FOLDER}" DESTINATION "include")
          install(TARGETS ${CURRENT_TARGET} ARCHIVE DESTINATION "lib/${CRT_VERSION_NAME}_${PLATFORM}/static")#静态库安装目录
        endif()
      endif()
    else()
      if(${CURRENT_TARGET_TYPE} STREQUAL "MODULE_LIBRARY")#插件库
        target_compile_definitions(${CURRENT_TARGET} PRIVATE "${CURRENT_SOURCE_FOLDER}_EXPORTS;")
        if(${CMAKE_CURRENT_SOURCE_DIR} MATCHES "${PROJECT_SOURCE_DIR}/Plugins")
          string(REGEX REPLACE "${PROJECT_SOURCE_DIR}/Plugins" "plugins" PLUGIN_INSTALL_PATH ${PARENT_DIRECTORY})
          install(TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION "${PLUGIN_INSTALL_PATH}" LIBRARY DESTINATION "${PLUGIN_INSTALL_PATH}")#插件库安装目录
        endif()
      else()
        if(${CURRENT_TARGET_TYPE} STREQUAL "EXECUTABLE")#可执行程序
          #记录程序基础名称
          target_compile_definitions(${CURRENT_TARGET} PRIVATE "PROGRAM_BASE_NAME=\"${CURRENT_TARGET}\"")
          set_property(TARGET ${CURRENT_TARGET} PROPERTY DEBUG_POSTFIX "d")#设置可执行程序(调试版本)后缀
          #GUI程序设置程序入口、获取UAC权限
          if(MSVC AND DEFINED USE_GUI)
            set_property(TARGET ${CURRENT_TARGET} APPEND_STRING PROPERTY LINK_FLAGS " /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup /level='requireAdministrator'")#GUI程序配置
          endif()
          if(${CMAKE_CURRENT_SOURCE_DIR} MATCHES "${PROJECT_SOURCE_DIR}/Applications")
            if(NOT ${PUBLIC_HEADER_DIR} STREQUAL "${PARENT_DIRECTORY}")#插件化的工具,直接暴露接口定义
              target_include_directories(${CURRENT_TARGET} SYSTEM INTERFACE "${PUBLIC_HEADER_DIR}")
              install(DIRECTORY "${PUBLIC_HEADER_DIR}/${CURRENT_SOURCE_FOLDER}" DESTINATION "include")
            endif()
            install(TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION "bin")#可执行程序安装目录
          elseif(${CMAKE_CURRENT_SOURCE_DIR} MATCHES "${PROJECT_SOURCE_DIR}/Tools")
            install(TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION "tools")#可执行程序(工具)安装目录
          endif()
          if(MSVC)
            #在VS中重定调试相关变量
            if(${CMAKE_VERSION} VERSION_GREATER 3.8 OR ${CMAKE_VERSION} VERSION_EQUAL 3.8)
                #set_property(TARGET ${CURRENT_TARGET} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$(${CMAKE_PROJECT_NAME})/bin")#设置VS调试工作目录
                if(${CMAKE_VERSION} VERSION_GREATER 3.13 OR ${CMAKE_VERSION} VERSION_EQUAL 3.13)
                    set_property(TARGET ${CURRENT_TARGET} PROPERTY VS_GLOBAL_PATH "${QT_BINARY_DIR};$(${CMAKE_PROJECT_NAME})/bin;$ENV{PATH};")#设置VS中$(PATH)的值
                    set_property(TARGET ${CURRENT_TARGET} PROPERTY VS_DEBUGGER_ENVIRONMENT "PATH=$(PATH)")#设置VS调试环境为$(PATH)
                endif()
            endif()
          endif()
        elseif(${CURRENT_TARGET_TYPE} STREQUAL "SHARED_LIBRARY")#动态库
          target_compile_definitions(${CURRENT_TARGET} PRIVATE "${CURRENT_SOURCE_FOLDER}_EXPORTS;")
          if(${CMAKE_CURRENT_SOURCE_DIR} MATCHES "${PROJECT_SOURCE_DIR}/Libraries")
            if(NOT ${PUBLIC_HEADER_DIR} STREQUAL "${PARENT_DIRECTORY}")#二次开发库(公开)
              install(DIRECTORY "${PUBLIC_HEADER_DIR}/${CURRENT_SOURCE_FOLDER}" DESTINATION "include")
            endif()
            install(TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION "bin" LIBRARY DESTINATION "bin" ARCHIVE DESTINATION "lib/${CRT_VERSION_NAME}_${PLATFORM}")#普通动态库(非插件&&仅运行)安装目录
          endif()
        endif()
      endif()
      if(MSVC)
        #install(FILES $<TARGET_PDB_FILE:${CURRENT_TARGET}> DESTINATION "pdb" OPTIONAL)#将pdb文件放入安装目录用于调试
      endif()
    endif()
    #为C/C++库添加编译版本信息
    set_property(TARGET ${CURRENT_TARGET} PROPERTY OUTPUT_NAME "${CURRENT_TARGET}$<$<AND:$<OR:$<STREQUAL:\"$<TARGET_PROPERTY:${CURRENT_TARGET},LINKER_LANGUAGE>\",\"C\">,$<STREQUAL:\"$<TARGET_PROPERTY:${CURRENT_TARGET},LINKER_LANGUAGE>\",\"CXX\">>,$<NOT:$<STREQUAL:\"${CURRENT_TARGET_TYPE}\",\"EXECUTABLE\">>>:${DEFAULT_VERSION_INFORMATION}>")
#############################################################################################################################
  elseif(PYTHON_SOURCE_FILES)#
    #Python代码保持原始目录结构
    foreach(CURRENT_SOURCE_CODE_FILE_PATH ${PYTHON_SOURCE_FILES})
      get_filename_component(CURRENT_SOURCE_CODE_DIRECTORY ${CURRENT_SOURCE_CODE_FILE_PATH} DIRECTORY)#获取当前文件目录
      string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" CURRENT_SOURCE_CODE_FILE_GROUP "${CURRENT_SOURCE_CODE_DIRECTORY}")
      file(TO_NATIVE_PATH "${CURRENT_SOURCE_CODE_FILE_GROUP}" "CURRENT_SOURCE_CODE_FILE_GROUP")
      source_group("${CURRENT_SOURCE_CODE_FILE_GROUP}" FILES "${CURRENT_SOURCE_CODE_FILE_PATH}")
    endforeach()
  endif()
  message("")
endmacro()

#指定生成C/C++可执行程序
macro(generateExecutableProgram)
  prepareTarget()#文件归集
  add_executable(${CURRENT_TARGET})#生成C/C++可执行程序
  configureTarget()#配置目标项目
endmacro()

#指定生成常规动态链接库
macro(generateDynamicLibrary)
  prepareTarget()#文件归集
  add_library(${CURRENT_TARGET} SHARED)#生成动态库
  configureTarget()#配置目标项目
endmacro()

#指定生成静态链接库
macro(generateStaticLibrary)
  prepareTarget()#文件归集
  add_library(${CURRENT_TARGET} STATIC)#生成静态库
  configureTarget()#配置目标项目
endmacro()

#指定生成插件动态链接库
macro(generatePluginLibrary)
  prepareTarget()#文件归集
  add_library(${CURRENT_TARGET} MODULE)#生成插件库
  configureTarget()#配置目标项目
endmacro()

#指定生成Java
macro(generateJavaPackage)
 if(Java_FOUND)
    prepareTarget()#文件归集
    add_jar(${CURRENT_TARGET} SOURCES "${JAVA_SOURCE_FILES}" ENTRY_POINT "${JAVA_ENTRY_POINT}")#生成Jar包
    configureTarget()#配置目标项目
  else()
    message(FATAL_ERROR "Module[\"Java\"] not found")
  endif()
endmacro()

#指定生成CSharp可执行程序
macro(generateCSharpProgram)
  if(${CMAKE_VERSION} VERSION_GREATER 3.8.2 OR ${CMAKE_VERSION} VERSION_EQUAL 3.8.2)
    prepareTarget()#文件归集
    add_executable(${CURRENT_TARGET})#生成CSharp可执行程序
    configureTarget()#配置目标项目
  else()
    message(FATAL_ERROR "CURRENT CMAKE_VERSION: (${CMAKE_VERSION}) VERSION_REQUIRED: (3.8.2) OR HIGHER FOR CSHARP PROJECT")
  endif()
endmacro()

#指定生成CSharp库
macro(generateCSharpLibrary)
  if(${CMAKE_VERSION} VERSION_GREATER 3.8.2 OR ${CMAKE_VERSION} VERSION_EQUAL 3.8.2)
    prepareTarget()#文件归集
    add_library(${CURRENT_TARGET} SHARED)#生成CSharp动态库
    configureTarget()#配置目标项目
  else()
    message(FATAL_ERROR "CURRENT CMAKE_VERSION: (${CMAKE_VERSION}) VERSION_REQUIRED: (3.8.2) OR HIGHER FOR CSHARP PROJECT")
  endif()
endmacro()

#指定生成Python可执行程序
macro(generatePythonProgram)
  prepareTarget()#文件归集
  add_custom_target(${CURRENT_TARGET} SOURCES "${PYTHON_SOURCE_FILES}")#组织Python源代码
  configureTarget()#配置目标项目
endmacro()

#指定生成常规Python动态链接库
macro(generatePythonLibrary)
  generateDynamicLibrary()
  set_property(TARGET ${CURRENT_TARGET} PROPERTY RUNTIME_OUTPUT_NAME "${CURRENT_TARGET}")#
  set_property(TARGET ${CURRENT_TARGET} PROPERTY SUFFIX ".pyd")#
endmacro()
