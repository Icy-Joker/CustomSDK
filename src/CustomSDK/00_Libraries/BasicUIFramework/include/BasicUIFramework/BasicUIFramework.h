#pragma once

#ifndef BASICUIFRAMEWORK_H
# define BASICUIFRAMEWORK_H

namespace BasicUIFramework
{
  extern "C"
  {
    BasicUIFramework_API bool initialize(int argc,char* argv[]);
    BasicUIFramework_API int exec();
  }
}

#endif//!__BASICUIFRAMEWORK_H__
