#add_subdirectory("")#
add_subdirectory("CustomModule")#
add_dependencies("CustomModule" "CustomFramework")#
add_subdirectory("CustomModuleExecutable")#
add_dependencies("CustomModuleExecutable" "CustomModule")#
