#set(QT_MODULE_LIST Core Gui Widgets)
set(THIRD_LIBRARY_LIST boost)

generateExecutableProgram()
#
target_include_directories(${CURRENT_TARGET} PRIVATE "$ENV{ThirdParty}/qrencode-4.1.1/include")
target_link_directories(${CURRENT_TARGET} PRIVATE "$ENV{ThirdParty}/qrencode-4.1.1/lib")
#
#target_link_libraries(${CURRENT_TARGET} PRIVATE BasicUIFramework)
#target_link_libraries(${CURRENT_TARGET} PRIVATE BasicFramework)
#target_link_libraries(${CURRENT_TARGET} PRIVATE BasicSupport)
#
target_link_libraries(${CURRENT_TARGET} PRIVATE "qrencode")
#
if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  target_link_libraries(${CURRENT_TARGET} PRIVATE "pthread")
endif()
#
install(TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION "tools")
