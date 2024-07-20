#
set(BOOST_MODULE_LIST "thread;system;filesystem;date_time;program_options;regex;atomic;chrono;")#配置Boost模块
#
#set(QT_MODULE_LIST "Core;Gui;Widgets;Core5Compat;")#配置Qt模块
#
set(THIRD_LIBRARY_LIST "icu4c;pugixml;fmt;spdlog;")#配置其他三方库
#
#set(SWIG_TARGET_SOURCE_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/Extends/CustomFramework4CSharp/src")
if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.8.2)
  if(CMAKE_CSharp_COMPILER)
    generateSWIGLibraryForCSharp()
    #
    if(TARGET "${CURRENT_TARGET}")
      #
      #target_compile_definitions("${CURRENT_TARGET}" PRIVATE "")#添加预处理宏
      #
      #target_include_directories("${CURRENT_TARGET}" PRIVATE "")#添加头文件搜索路径
      #
      #target_link_directories("${CURRENT_TARGET}" PRIVATE "")#添加链接库搜索路径
      #
      #target_link_libraries("${CURRENT_TARGET}" PRIVATE "")#添加依赖库
      target_link_libraries(${CURRENT_TARGET} PRIVATE "BasicSupport")
      target_link_libraries(${CURRENT_TARGET} PRIVATE "CommonFramework")
      target_link_libraries("${CURRENT_TARGET}" PRIVATE "fmt::fmt-header-only")#
      target_link_libraries("${CURRENT_TARGET}" PRIVATE "spdlog::spdlog_header_only")#
      #
      if(CMAKE_SYSTEM_NAME MATCHES "Windows")
        install(FILES "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CURRENT_TARGET}${CMAKE_SHARED_MODULE_SUFFIX}" DESTINATION "bin")#安装CSharp封装库
      else()
        install(FILES "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CURRENT_TARGET}${CMAKE_SHARED_MODULE_SUFFIX}" DESTINATION "lib")#安装CSharp封装库
      endif()
      install(DIRECTORY "resource/config" DESTINATION "." FILES_MATCHING PATTERN "*.xml")
    endif()
  else()
    message(WARNING "CMAKE_CSharp_COMPILER not found")
  endif()
else()
  message(FATAL_ERROR "CURRENT CMAKE_VERSION: (${CMAKE_VERSION}) VERSION_REQUIRED: (3.8.2) OR HIGHER FOR CSHARP PROJECT")
endif()
