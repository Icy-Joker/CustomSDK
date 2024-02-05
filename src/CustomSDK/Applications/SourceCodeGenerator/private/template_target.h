#pragma once

#ifndef __TEMPLATE_TARGET_H__
# define __TEMPLATE_TARGET_H__

const char* TEMPLATE_PRECOMPILED_HEADER =
"#pragma once\n"
"\n"
"#ifndef __STDAFX_H__\n"
"# define __STDAFX_H__\n"
"\n"
"##BLOCK_TARGET_API_MACRO_IMPORT##\n"
"\n"
"#endif // !__STDAFX_H__\n"
"";

const char* TEMPLATE_PRECOMPILED_SOURCE =
"#include \"stdafx.h\"\n"
"";

const char* TEMPLATE_TARGET_EXPORT =
"#pragma once\n"
"\n"
"#ifndef __##BLOCK_TARGET_NAME_UPPER_CASE##_EXPORT_H__\n"
"# define __##BLOCK_TARGET_NAME_UPPER_CASE##_EXPORT_H__\n"
"\n"
"# ifdef _MSC_VER\n"
"#  ifdef ##BLOCK_TARGET_NAME##_EXPORTS\n"
"#   define ##BLOCK_TARGET_NAME##_API _declspec(dllexport)\n"
"#  elif defined USE_##BLOCK_TARGET_NAME##_STATIC\n"
"#   define ##BLOCK_TARGET_NAME##_API\n"
"#  else\n"
"#   define ##BLOCK_TARGET_NAME##_API _declspec(dllimport)\n"
"#  endif // ##BLOCK_TARGET_NAME##_EXPORTS\n"
"# else\n"
"#  define ##BLOCK_TARGET_NAME##_API\n"
"# endif //_MSC_VER\n"
"\n"
"#endif // !__##BLOCK_TARGET_NAME_UPPER_CASE##_EXPORT_H__\n"
"";

const char* TEMPLATE_TARGET_HEADER =
"#pragma once\n"
"\n"
"#ifndef __##BLOCK_TARGET_NAME_UPPER_CASE##_H__\n"
"# define __##BLOCK_TARGET_NAME_UPPER_CASE##_H__\n"
"\n"
"extern \"C\"\n"
"{\n"
"  ##BLOCK_TARGET_NAME##_API void Initialize##BLOCK_TARGET_NAME##();\n"
"}\n"
"\n"
"#endif // !__##BLOCK_TARGET_NAME_UPPER_CASE##_H__\n"
"";

const char* TEMPLATE_TARGET_SOURCE =
"#include \"stdafx.h\"\n"
"\n"
"#include \"##BLOCK_TARGET_NAME##.h\"\n"
"\n"
"##BLOCK_TARGET_NAME##_API void Initialize##BLOCK_TARGET_NAME##()\n"
"{\n"
"}\n"
"";

const char* TEMPLATE_CLASS_PRIVATE_HEADER =
"#pragma once\n"
"\n"
"#ifndef __##BLOCK_CLASS_NAME_UPPER_CASE##PRIVATE_H__\n"
"# define __##BLOCK_CLASS_NAME_UPPER_CASE##PRIVATE_H__\n"
"\n"
"struct ##BLOCK_CLASS_NAME##Private\n"
"{\n"
"};\n"
"\n"
"#endif // !__##BLOCK_CLASS_NAME_UPPER_CASE##PRIVATE_H__\n"
"";

const char* TEMPLATE_CLASS_PRIVATE_SOURCE =
"#include \"stdafx.h\"\n"
"\n"
"#include \"##BLOCK_CLASS_NAME##Private.h\"\n"
"";

const char* TEMPLATE_CLASS_HEADER =
"#pragma once\n"
"\n"
"#ifndef __##BLOCK_CLASS_NAME_UPPER_CASE##_H__\n"
"# define __##BLOCK_CLASS_NAME_UPPER_CASE##_H__\n"
"\n"
"struct ##BLOCK_CLASS_NAME##Private;\n"
"\n"
"class ##BLOCK_TARGET_API_MACRO## ##BLOCK_CLASS_NAME##\n"
"{\n"
"public:\n"
"  ##BLOCK_CLASS_NAME##();\n"
"  ~##BLOCK_CLASS_NAME##();\n"
"public:\n"
"protected:\n"
"private:\n"
"  ##BLOCK_CLASS_NAME##Private* _p;\n"
"};\n"
"\n"
"#endif // !__##BLOCK_CLASS_NAME_UPPER_CASE##_H__\n"
"";

const char* TEMPLATE_CLASS_SOURCE =
"#include \"stdafx.h\"\n"
"\n"
"#include \"##BLOCK_CLASS_NAME##.h\"\n"
"#include \"##BLOCK_CLASS_NAME##Private.h\"\n"
"\n"
"##BLOCK_CLASS_NAME##::##BLOCK_CLASS_NAME##():\n"
"  _p(new ##BLOCK_CLASS_NAME##Private())\n"
"{\n"
"}\n"
"\n"
"##BLOCK_CLASS_NAME##::~##BLOCK_CLASS_NAME##()\n"
"{\n"
"  if(_p)\n"
"  {\n"
"    delete _p;\n"
"    _p = nullptr;\n"
"  }\n"
"}\n"
"";

const char* TEMPLATE_ENTRY_METHOD = 
"#include \"stdafx.h\"\n"
"\n"
"int main(int argc, char* argv[])\n"
"{\n"
"  int result = 0;\n"
"\n"
"  return result;\n"
"}\n"
"";

const char* TEMPLATE_CMAKE_CONFIGURATION =
"#\n"
"#set(QT_MODULE_LIST \"Core;Gui;Widgets;\")#配置Qt模块\n"
"#\n"
"#set(THIRD_LIBRARY_LIST \"boost;\")#配置其他三方库\n"
"#\n"
"##BLOCK_TARGET_GENERATE_COMMAND##\n"
"#\n"
"#target_compiler_definitions(\"${CURRENT_TARGET}\" PRIVATE \"\")#添加预处理宏\n"
"#\n"
"#target_link_libraries(\"${CURRENT_TARGET}\" PRIVATE \"\")#添加依赖库\n"
"";

#endif // !__TEMPLATE_TARGET_H__
