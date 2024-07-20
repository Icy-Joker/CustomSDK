#
set(BOOST_MODULE_LIST "thread;system;filesystem;date_time;program_options;regex;atomic;chrono;")#配置Boost模块
#
#set(QT_MODULE_LIST "Core;Gui;Widgets;")#配置Qt模块
#
set(THIRD_LIBRARY_LIST "icu4c;")#配置其他三方库
#
generateExecutableProgram()#
if(TARGET "${CURRENT_TARGET}")
  #target_compile_definitions("${CURRENT_TARGET}" PRIVATE "")#添加预处理宏
  #
  #target_include_directories("${CURRENT_TARGET}" PRIVATE "")#添加头文件搜索路径
  #
  #target_link_directories("${CURRENT_TARGET}" PRIVATE "")#添加链接库搜索路径
  #
  #target_link_libraries("${CURRENT_TARGET}" PRIVATE "")#添加依赖库
  target_link_libraries("${CURRENT_TARGET}" PRIVATE "BasicFramework")#
  target_link_libraries("${CURRENT_TARGET}" PRIVATE "CustomFramework")#
  target_link_libraries("${CURRENT_TARGET}" PRIVATE "CustomModule")#
  #
  install(TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION "test/bin" LIBRARY DESTINATION "test/bin")
  if("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
    install(DIRECTORY "resource/scripts" DESTINATION "test" FILES_MATCHING PATTERN "*.bat")
  else()
    install(DIRECTORY "resource/scripts" DESTINATION "test" FILES_MATCHING PATTERN "*.sh" PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)
  endif()
endif()
