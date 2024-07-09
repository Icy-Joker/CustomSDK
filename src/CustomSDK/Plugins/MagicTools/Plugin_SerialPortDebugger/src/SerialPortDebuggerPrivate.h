#pragma once

#ifndef __SERIALPORTDEBUGGERPRIVATE_H__
# define __SERIALPORTDEBUGGERPRIVATE_H__

#include <boost/asio.hpp>

class SerialPortDebuggerPrivate
{
private:
  explicit SerialPortDebuggerPrivate();
  ~SerialPortDebuggerPrivate();
private:
  boost::asio::io_context io_context;
  boost::asio::serial_port serial_port;
  boost::asio::executor_work_guard<boost::asio::io_context::executor_type> executor_work_guard;

  friend class SerialPortDebugger;
};

#endif // !__SERIALPORTDEBUGGERPRIVATE_H__
