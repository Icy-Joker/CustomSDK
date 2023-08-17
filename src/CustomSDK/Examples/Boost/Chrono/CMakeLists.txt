set(THIRD_LIBRARY_LIST boost)

generateExecutableProgram()
#
target_compile_definitions(${CURRENT_TARGET} PRIVATE "BOOST_THREAD_USES_CHRONO")
#
target_link_libraries(${CURRENT_TARGET} PRIVATE "pthread;")
