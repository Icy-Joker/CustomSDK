set(QT_MODULE_LIST Core Gui Widgets)
set(THIRD_LIBRARY_LIST boost)

generateExecutableProgram()

target_link_libraries(${CURRENT_TARGET} PRIVATE "BasicSupport")
target_link_libraries(${CURRENT_TARGET} PRIVATE "BasicFramework")
target_link_libraries(${CURRENT_TARGET} PRIVATE "BasicUIFramework")
