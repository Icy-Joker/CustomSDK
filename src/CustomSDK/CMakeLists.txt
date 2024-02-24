cmake_minimum_required(VERSION "3.8.2")

project("CustomSDK" DESCRIPTION "CustomSDK" VERSION "0.0.0.0")

include("${PROJECT_SOURCE_DIR}/module.cmake")

#add_subdirectory("")#
add_subdirectory("Applications")#
add_subdirectory("Examples")#
add_subdirectory("Libraries")#
add_subdirectory("Modules")#
add_subdirectory("Tools")#
