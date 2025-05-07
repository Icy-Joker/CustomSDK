cmake_minimum_required(VERSION "3.19.0")

project("Examples" DESCRIPTION "Examples" LANGUAGES "CXX" VERSION "0.0.0.0")
#
include(CPack)
#
#set(CPACK_PACKAGE_NAME "${CMAKE_PROJECT_NAME}")
#set(CPACK_PACKAGE_VENDOR "CommonSoftware")
#set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${CMAKE_PROJECT_DESCRIPTION}")
#set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
#set(CPACK_GENERATOR "TGZ;ZIP") # 生成 tar.gz 和 zip
#
include("${PROJECT_SOURCE_DIR}/module.cmake")

#add_subdirectory("")#
