set(QT_MODULE_LIST Core Gui Widgets)
set(THIRD_LIBRARY_LIST boost)

generateDynamicLibrary()

target_link_libraries(${CURRENT_TARGET} PUBLIC BasicSupport)
