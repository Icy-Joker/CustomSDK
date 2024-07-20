#pragma once

#ifndef __BASICUIFRAMEWORK_H__
# define __BASICUIFRAMEWORK_H__

namespace BasicUIFramework
{
  extern "C"
  {
    BasicUIFramework_API bool initialize(int argc,char* argv[]);
    BasicUIFramework_API int exec();
  }
}

#endif // !__BASICUIFRAMEWORK_H__
