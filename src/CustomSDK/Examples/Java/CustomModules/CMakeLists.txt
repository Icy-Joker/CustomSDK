#add_subdirectory("")#
add_subdirectory("CustomModule4Java")#
add_dependencies("CustomModule4Java" "CustomFramework4Java")
add_subdirectory("CustomModuleExecutable4Java")#
add_dependencies("CustomModuleExecutable4Java" "CustomModule4Java")#
