#pragma once

#ifndef SINGLETON_H
# define SINGLETON_H

template<typename TYPE>
class Singleton
{
public:
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
protected:
  Singleton() = default;
  virtual ~Singleton() = default;
public:
  static TYPE* instance()
  {
    static TYPE unique_instance;

    return &unique_instance;
  }
};

#endif//!SINGLETON_H
