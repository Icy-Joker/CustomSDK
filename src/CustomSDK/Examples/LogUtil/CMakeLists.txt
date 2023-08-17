#set(QT_MODULE_LIST Core Gui Widgets)
set(THIRD_LIBRARY_LIST boost)

generateExecutableProgram()

target_link_libraries(${CURRENT_TARGET} PUBLIC BasicUIFramework)
target_link_libraries(${CURRENT_TARGET} PUBLIC BasicFramework)
target_link_libraries(${CURRENT_TARGET} PUBLIC BasicSupport)

if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  target_link_libraries(${CURRENT_TARGET} PUBLIC "pthread")
endif()
