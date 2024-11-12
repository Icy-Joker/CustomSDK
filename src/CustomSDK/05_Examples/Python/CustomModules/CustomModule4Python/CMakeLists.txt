#
set(BOOST_MODULE_LIST "thread;system;filesystem;date_time;program_options;regex;atomic;chrono;")#配置Boost模块
#
#set(QT_MODULE_LIST "Core;Gui;Widgets;Core5Compat;")#配置Qt模块
#
set(THIRD_LIBRARY_LIST "icu4c;")#配置其他三方库
#
if(SWIG_FOUND)
  if(Python_FOUND)
    #
    generateSWIGLibraryForPython("CustomModule4Python")
    #
    if(TARGET "${CURRENT_TARGET}")
      #
      #target_compile_definitions("${CURRENT_TARGET}" PRIVATE "")#添加预处理宏
      target_compile_definitions("${CURRENT_TARGET}" PRIVATE "CustomModule_EXPORTS")#
      #
      #target_include_directories("${CURRENT_TARGET}" PRIVATE "")#添加头文件搜索路径
      target_include_directories(${CURRENT_TARGET} SYSTEM PRIVATE "${Python_INCLUDE_DIRS}")
      #
      #target_link_directories("${CURRENT_TARGET}" PRIVATE "")#添加链接库搜索路径
      target_link_directories(${CURRENT_TARGET} PRIVATE "${Python_LIBRARY_DIRS}")
      #
      #target_link_libraries("${CURRENT_TARGET}" PRIVATE "")#添加依赖库
      target_link_libraries(${CURRENT_TARGET} PRIVATE "BasicSupport")
      target_link_libraries(${CURRENT_TARGET} PRIVATE "CommonFramework")
      target_link_libraries(${CURRENT_TARGET} PRIVATE "CustomFramework4Python")
      target_link_libraries(${CURRENT_TARGET} PRIVATE "${Python_LIBRARIES}")
      #
      if(CMAKE_SYSTEM_NAME MATCHES "Windows")
        install(TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION "test/plugins/CustomModule")
      else()
        install(TARGETS ${CURRENT_TARGET} LIBRARY DESTINATION "test/plugins/CustomModule")
      endif()
      install(DIRECTORY "${SWIG_TARGET_SOURCE_OUTPUT_DIR}/" DESTINATION "test/plugins/CustomModule" OPTIONAL PATTERN "*.py")
    endif()
  endif()
endif()
