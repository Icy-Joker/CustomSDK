set(QT_MODULE_LIST Core Gui Widgets)
set(THIRD_LIBRARY_LIST boost)

generateStaticLibrary()

target_link_libraries(${CURRENT_TARGET} PRIVATE "BasicSupport")
target_link_libraries(${CURRENT_TARGET} PRIVATE "BasicFramework")
target_link_libraries(${CURRENT_TARGET} PRIVATE "BasicUIFramework")

if(MSVC_IDE)
 #忽略因正则匹配字符串导致的未知定义转义字符串警告
 target_compile_options(${CURRENT_TARGET} PRIVATE "/wd4129")
endif()
