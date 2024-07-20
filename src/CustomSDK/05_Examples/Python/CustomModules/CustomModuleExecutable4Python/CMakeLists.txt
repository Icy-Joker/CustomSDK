#
generatePythonProgram()#生成可执行程序
#
install(DIRECTORY "src/" DESTINATION "test/bin" FILES_MATCHING PATTERN "*.py")
install(DIRECTORY "resource/config" DESTINATION "test" FILES_MATCHING PATTERN "*.xml")
if("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
  install(DIRECTORY "resource/scripts" DESTINATION "test" FILES_MATCHING PATTERN "*.bat")
else()
  install(DIRECTORY "resource/scripts" DESTINATION "test" FILES_MATCHING PATTERN "*.sh" PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)
endif()
