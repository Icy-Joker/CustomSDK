cmake_minimum_required(VERSION "3.13.0")

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL "${CMAKE_SOURCE_DIR}")
  project("Examples" LANGUAGES "CXX")
  
  include("${CMAKE_CURRENT_SOURCE_DIR}/module.cmake")
else()
  file(COPY "${CMAKE_SOURCE_DIR}/module.cmake" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")
  if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" DESTINATION "examples" USE_SOURCE_PERMISSIONS PATTERN "scripts/*.bat" EXCLUDE)
  else()
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" DESTINATION "examples" USE_SOURCE_PERMISSIONS PATTERN "scripts/*.sh" EXCLUDE)
  endif()
endif()

if(CMAKE_CXX_COMPILER)
  #add_subdirectory("")#
endif()
