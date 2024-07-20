#add_subdirectory("")#
add_subdirectory("CustomModule4Python")#
add_subdirectory("CustomModuleExecutable4Python")#

add_dependencies("CustomModule4Python" "CustomFramework4Python")#
add_dependencies("CustomModuleExecutable4Python" "CustomModule4Python")#
