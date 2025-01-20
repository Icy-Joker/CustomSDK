#add_subdirectory("")#
add_subdirectory("src/Examples")#

install(DIRECTORY "src/Examples" DESTINATION "examples/CSharp/src" USE_SOURCE_PERMISSIONS PATTERN "src/Examples/CMakeLists.txt" EXCLUDE)#
install(FILES "resource/template/CMakeLists.txt" DESTINATION "examples/CSharp/src/Examples")#
install(FILES "${CMAKE_SOURCE_DIR}/module.cmake" DESTINATION "examples/CSharp/src/Examples")
install(FILES "${CMAKE_SOURCE_DIR}/CMakePresets.json" DESTINATION "examples/CSharp/src/Examples")
install(FILES "${CMAKE_SOURCE_DIR}/CMakeUserPresets.json" DESTINATION "examples/CSharp/src/Examples")
install(FILES "${CMAKE_SOURCE_DIR}/Manifest.txt.in" DESTINATION "examples/CSharp/src/Examples")
install(FILES "${CMAKE_SOURCE_DIR}/VersionInfo.rc.in" DESTINATION "examples/CSharp/src/Examples")
