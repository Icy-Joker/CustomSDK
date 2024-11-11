#
if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.8.2)
  if(CMAKE_CSharp_COMPILER)
    generateCSharpLibrary()#
    #
    if(TARGET "${CURRENT_TARGET}")
      #
      set_property(TARGET ${CURRENT_TARGET} APPEND_STRING PROPERTY VS_DOTNET_REFERENCES "CustomFramework4CSharp${CMAKE_SHARED_MODULE_SUFFIX}")
      #
      if(CMAKE_SYSTEM_NAME MATCHES "Windows")
        install(TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION "test/plugins/CustomModule")
      else()
        install(TARGETS ${CURRENT_TARGET} LIBRARY DESTINATION "test/plugins/CustomModule")
      endif()
    endif()
  else()
    message(WARNING "CMAKE_CSharp_COMPILER not found")
  endif()
else()
  message(FATAL_ERROR "CURRENT CMAKE_VERSION: (${CMAKE_VERSION}) VERSION_REQUIRED: (3.8.2) OR HIGHER FOR CSHARP PROJECT")
endif()
