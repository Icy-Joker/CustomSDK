#pragma once

#ifndef __SOURCECODEGENERATOR_H__
# define __SOURCECODEGENERATOR_H__

struct SourceCodeGeneratorPrivate;

class SourceCodeGenerator
{
public:
  SourceCodeGenerator();
  ~SourceCodeGenerator();
public:
protected:
private:
  SourceCodeGeneratorPrivate* _p;
};

#endif // !__SOURCECODEGENERATOR_H__
