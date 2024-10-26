#
set(BOOST_MODULE_LIST "thread;system;filesystem;date_time;program_options;regex;atomic;chrono;")#配置Boost模块
#
#set(QT_MODULE_LIST "Core;Gui;Widgets;Core5Compat;")#配置Qt模块
#
set(THIRD_LIBRARY_LIST "icu4c;pugixml;fmt;spdlog;")#配置其他三方库
#
#set(SWIG_TARGET_SOURCE_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/Modules/CustomFramework4Python/src")
if(SWIG_FOUND)
  if(Python_FOUND)
    generateSWIGLibraryForPython()
    if(TARGET "${CURRENT_TARGET}")
      #target_compile_definitions("${CURRENT_TARGET}" PRIVATE "")#添加预处理宏
      target_compile_definitions("${CURRENT_TARGET}" PRIVATE "CustomFramework_EXPORTS")#
      #
      #target_include_directories("${CURRENT_TARGET}" PRIVATE "")#添加头文件搜索路径
      target_include_directories(${CURRENT_TARGET} SYSTEM PRIVATE "${Python_INCLUDE_DIRS}")
      #
      #target_link_directories("${CURRENT_TARGET}" PRIVATE "")#添加链接库搜索路径
      target_link_directories(${CURRENT_TARGET} PRIVATE "${Python_LIBRARY_DIRS}")
      #
      #target_link_libraries("${CURRENT_TARGET}" PRIVATE "")#添加依赖库
      target_link_libraries(${CURRENT_TARGET} PRIVATE "BasicSupport")
      target_link_libraries(${CURRENT_TARGET} PRIVATE "BasicFramework")
      target_link_libraries(${CURRENT_TARGET} PRIVATE "${Python_LIBRARIES}")
      #
      install(DIRECTORY "${SWIG_TARGET_SOURCE_OUTPUT_DIR}/" DESTINATION "bin" OPTIONAL PATTERN "*.py")
    endif()
  endif()
endif()
