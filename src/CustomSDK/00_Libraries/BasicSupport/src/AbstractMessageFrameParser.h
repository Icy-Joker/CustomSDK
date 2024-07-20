#pragma once

#ifndef ABSTRACTMESSAGEFRAMEPARSER_H
# define ABSTRACTMESSAGEFRAMEPARSER_H

#include <string>

class AbstractMessageFrameParser
{
public:
  virtual ~AbstractMessageFrameParser() = default;
public:
  virtual bool parse(std::string& buffer,std::string& frame) = 0;
};

#endif//!ABSTRACTMESSAGEFRAMEPARSER_H
