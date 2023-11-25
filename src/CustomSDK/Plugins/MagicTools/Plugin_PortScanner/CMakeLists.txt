set(QT_MODULE_LIST Core Gui Widgets)
set(THIRD_LIBRARY_LIST boost)

generatePluginLibrary()

target_link_libraries(${CURRENT_TARGET} PRIVATE "BasicSupport")
target_link_libraries(${CURRENT_TARGET} PRIVATE "BasicFramework")
target_link_libraries(${CURRENT_TARGET} PRIVATE "BasicUIFramework")
target_link_libraries(${CURRENT_TARGET} PRIVATE "PortScanner")
#target_link_libraries(${CURRENT_TARGET} PRIVATE "MagicToolBox")
target_include_directories(${CURRENT_TARGET} PRIVATE "$<TARGET_PROPERTY:MagicToolBox,INTERFACE_INCLUDE_DIRECTORIES>")

if(MSVC_IDE)
 #忽略因正则匹配字符串导致的未知定义转义字符串警告
 target_compile_options(${CURRENT_TARGET} PRIVATE "/wd4129")
endif()
