#
set(BOOST_MODULE_LIST "thread;system;filesystem;date_time;program_options;regex;atomic;chrono;")#配置Boost模块
#
#set(QT_MODULE_LIST "Core;Gui;Widgets;")#配置Qt模块
#
set(THIRD_LIBRARY_LIST "icu4c")#配置其他三方库
#
generateExecutableProgram()#生成可执行程序
#
#target_compiler_definitions("${CURRENT_TARGET}" PRIVATE "")#添加预处理宏
#
#target_link_libraries("${CURRENT_TARGET}" PRIVATE "")#添加依赖库
