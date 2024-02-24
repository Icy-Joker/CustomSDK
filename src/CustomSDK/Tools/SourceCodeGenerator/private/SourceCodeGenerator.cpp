#include "stdafx.h"

#include "SourceCodeGenerator.h"
#include "SourceCodeGeneratorPrivate.h"

SourceCodeGenerator::SourceCodeGenerator():
  _p(new SourceCodeGeneratorPrivate())
{
}

SourceCodeGenerator::~SourceCodeGenerator()
{
  if(_p)
  {
    delete _p;
    _p = nullptr;
  }
}
