#
set(BOOST_MODULE_LIST "thread;system;filesystem;date_time;program_options;regex;atomic;chrono;")#配置Boost模块
#
#set(QT_MODULE_LIST "Core;Gui;Widgets;Core5Compat;")#配置Qt模块
#
set(THIRD_LIBRARY_LIST "icu4c;pugixml;fmt;spdlog;")#配置其他三方库
#
generateDynamicLibrary()#
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
  target_link_libraries("${CURRENT_TARGET}" PRIVATE "BasicSupport")#
  target_link_libraries("${CURRENT_TARGET}" PRIVATE "BasicFramework")#
  target_link_libraries("${CURRENT_TARGET}" PRIVATE "pugixml")#
  target_link_libraries("${CURRENT_TARGET}" PRIVATE "fmt::fmt;spdlog::spdlog")#
  #
  install(DIRECTORY "resource/config" DESTINATION "." FILES_MATCHING PATTERN "*.xml")
endif()
