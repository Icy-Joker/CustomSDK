cmake_minimum_required(VERSION "3.19.0")

project("CustomSDK" DESCRIPTION "CustomSDK" VERSION "0.0.0.0")

include("${PROJECT_SOURCE_DIR}/module.cmake")

#add_subdirectory("")#
add_subdirectory("00_Libraries")#二次开发库目录
