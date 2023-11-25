set(QT_MODULE_LIST Core Gui Widgets)
set(THIRD_LIBRARY_LIST boost qrencode-4.1.1)

generatePluginLibrary()

target_link_libraries(${CURRENT_TARGET} PRIVATE "BasicSupport")
target_link_libraries(${CURRENT_TARGET} PRIVATE "BasicFramework")
target_link_libraries(${CURRENT_TARGET} PRIVATE "BasicUIFramework")
target_link_libraries(${CURRENT_TARGET} PRIVATE "QRCodeGenerator")
#target_link_libraries(${CURRENT_TARGET} PRIVATE "MagicToolBox")
target_include_directories(${CURRENT_TARGET} PRIVATE "$<TARGET_PROPERTY:MagicToolBox,INTERFACE_INCLUDE_DIRECTORIES>")
target_link_libraries(${CURRENT_TARGET} PRIVATE "qrencode")
