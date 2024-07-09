#pragma once

#ifndef SERIALPORTHANDLER_H
# define SERIALPORTHANDLER_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include <string>
#include <functional>

class SerialPortHandler
{
public:
  explicit SerialPortHandler();
  ~SerialPortHandler();
public:
  void setBaudRate(unsigned int baud_rate);
  void setDataBits(unsigned int character_size);
  void setStopBits(unsigned int stop_bits);
  void setParity(unsigned int parity);
  void setFlowControl(unsigned int flow_control);

  bool open(const std::string& port_name);
  bool close();

  using AsyncReadCallback = std::function<void(const std::string&)>;
  void setAsyncReadCallback(AsyncReadCallback callback_message);
  void doAsyncWrite(const std::string& message_content);
private:
  void startAsyncRead();
private:
  boost::asio::io_context io_context;
  boost::asio::executor_work_guard<boost::asio::io_context::executor_type> executor_work_guard;
  boost::asio::serial_port serial_port;

  boost::thread thread_io_context;

  AsyncReadCallback callback_message;
};

#endif // !SERIALPORTHANDLER_H
