#pragma once

#ifndef __SERIALPORTDEBUGGERPRIVATE_H__
# define __SERIALPORTDEBUGGERPRIVATE_H__

#include <boost/asio.hpp>
#include <boost/atomic/atomic.hpp>

class SerialPortDebuggerPrivate
{
private:
  explicit SerialPortDebuggerPrivate();
  ~SerialPortDebuggerPrivate();
public:
  void doSendMessage(const std::string& message_content);
  void doReceiveMessage();
private:
  bool open(const std::string& serial_port_name);
  void setBaudRate(unsigned int baud_rate);
  void setDataBits(unsigned int character_size);
  void setStopBits(unsigned int stop_bits);
  void setParity(unsigned int parity);
  void setFlowControl(unsigned int flow_control);
  bool close();
private:
  boost::asio::io_context io_context;
  boost::asio::serial_port serial_port;
  boost::asio::executor_work_guard<boost::asio::io_context::executor_type> executor_work_guard;

  boost::atomic_bool auto_send_enabled;

  friend class SerialPortDebugger;
};

#endif // !__SERIALPORTDEBUGGERPRIVATE_H__
