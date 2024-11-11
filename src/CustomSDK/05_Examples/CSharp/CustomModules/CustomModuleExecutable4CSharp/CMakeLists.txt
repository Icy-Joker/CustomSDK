#
if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.8.2)
  if(CMAKE_CSharp_COMPILER)
    generateCSharpProgram()#
    #
    if(TARGET "${CURRENT_TARGET}")
      #
      set_property(TARGET ${CURRENT_TARGET} APPEND_STRING PROPERTY VS_DOTNET_REFERENCES "CustomFramework4CSharp${CMAKE_SHARED_MODULE_SUFFIX};")
      #
      install(TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION "test/bin")
      install(FILES "$<TARGET_FILE_DIR:${CURRENT_TARGET}>/CustomFramework4CSharp${CMAKE_SHARED_MODULE_SUFFIX}" DESTINATION "test/bin")#将添加的CSharp引用库同步放入安装目录
      install(DIRECTORY "resource/config" DESTINATION "test" FILES_MATCHING PATTERN "*.xml")
      if("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
        install(DIRECTORY "resource/scripts" DESTINATION "test" FILES_MATCHING PATTERN "*.bat")
      else()
        install(DIRECTORY "resource/scripts" DESTINATION "test" FILES_MATCHING PATTERN "*.sh" PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)
      endif()
    endif()
  else()
    message(WARNING "CMAKE_CSharp_COMPILER not found")
  endif()
else()
  message(FATAL_ERROR "CURRENT CMAKE_VERSION: (${CMAKE_VERSION}) VERSION_REQUIRED: (3.8.2) OR HIGHER FOR CSHARP PROJECT")
endif()
