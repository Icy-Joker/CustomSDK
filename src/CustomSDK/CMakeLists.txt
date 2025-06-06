cmake_minimum_required(VERSION "3.19.0")

project("CustomSDK" DESCRIPTION "CustomSDK" VERSION "0.0.0.0")

include("${PROJECT_SOURCE_DIR}/module.cmake")

#add_subdirectory("")#
add_subdirectory("Libraries")#
add_subdirectory("Modules")#
add_subdirectory("Plugins")#
add_subdirectory("Applications")#
add_subdirectory("Tools")#
add_subdirectory("Examples")#
add_subdirectory("Tests")#
