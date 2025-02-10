#pragma once

#ifndef __SIMPLEGRPCSERVER_H__
# define __SIMPLEGRPCSERVER_H__

class SimpleGRPCServerPrivate;

class SimpleGRPCServer
{
public:
  explicit SimpleGRPCServer();
  ~SimpleGRPCServer();
public:
  bool initializeWithConfig(const char* config_file_path);
public:
  void run();
  void stop();
private:
  class SimpleGRPCServerPrivate* private_ptr;
};

#endif // !__SIMPLEGRPCSERVER_H__
