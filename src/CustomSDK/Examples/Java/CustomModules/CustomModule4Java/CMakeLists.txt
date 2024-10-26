#
set(CURRENT_JAVA_INCLUDE_PATHS "")#添加Java编译依赖
list(APPEND CURRENT_JAVA_INCLUDE_PATHS "${CMAKE_JAVA_TARGET_OUTPUT_DIR}/CustomFramework4Java.jar")#
#
set(CURRENT_JAVA_CLASS_PATHS "")#添加Java运行依赖
#
set(CURRENT_JAVA_ENTRY_POINT "")#配置主类
#
generateJavaPackage()
#
if(TARGET "${CURRENT_TARGET}")
  install_jar(${CURRENT_TARGET} DESTINATION "test/bin")
  install(DIRECTORY "resource/config" DESTINATION "test" FILES_MATCHING PATTERN "*.xml")
endif()
