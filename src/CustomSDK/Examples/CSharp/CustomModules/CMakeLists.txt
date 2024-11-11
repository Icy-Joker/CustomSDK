#add_subdirectory("")#
add_subdirectory("CustomModule4CSharp")#
add_subdirectory("CustomModuleExecutable4CSharp")#

add_dependencies("CustomModule4CSharp" "CustomFramework4CSharp")#
add_dependencies("CustomModuleExecutable4CSharp" "CustomModule4CSharp")#
