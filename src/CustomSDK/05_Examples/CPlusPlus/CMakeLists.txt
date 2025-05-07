#add_subdirectory("")#
add_subdirectory("src/Examples")#

install(DIRECTORY "src/Examples" DESTINATION "examples/CPlusPlus/src" USE_SOURCE_PERMISSIONS PATTERN "src/Examples/CMakeLists.txt" EXCLUDE)#
install(FILES "resource/template/CMakeLists.txt" DESTINATION "examples/CPlusPlus/src/Examples")#
install(FILES "${CMAKE_SOURCE_DIR}/module.cmake" DESTINATION "examples/CPlusPlus/src/Examples")
install(FILES "${CMAKE_SOURCE_DIR}/CMakePresets.json" DESTINATION "examples/CPlusPlus/src/Examples")
install(FILES "${CMAKE_SOURCE_DIR}/CMakeUserPresets.json" DESTINATION "examples/CPlusPlus/src/Examples")
install(FILES "${CMAKE_SOURCE_DIR}/Manifest.txt.in" DESTINATION "examples/CPlusPlus/src/Examples")
install(FILES "${CMAKE_SOURCE_DIR}/VersionInfo.rc.in" DESTINATION "examples/CPlusPlus/src/Examples")
