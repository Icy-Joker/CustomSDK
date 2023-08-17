cmake_minimum_required(VERSION 3.1)

project(CustomSDK LANGUAGES CXX VERSION 3.1.0.0)

include(${CMAKE_SOURCE_DIR}/module.cmake)

add_subdirectory(Applications)#运行工具
add_subdirectory(Examples)#SDK使用示例,附带源码
add_subdirectory(Libraries)#二次开发库
add_subdirectory(Models)#附加库
add_subdirectory(Modules)#自带模块,仅运行用,不用于二次开发
add_subdirectory(Plugins)#自带插件库
add_subdirectory(Tools)#自带插件库
add_subdirectory(Demos)#
