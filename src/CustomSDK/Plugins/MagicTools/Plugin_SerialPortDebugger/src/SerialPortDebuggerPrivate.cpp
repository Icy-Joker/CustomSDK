#include "stdafx.h"

#include "SerialPortDebuggerPrivate.h"

#include <boost/thread.hpp>

SerialPortDebuggerPrivate::SerialPortDebuggerPrivate():
  executor_work_guard(boost::asio::make_work_guard(io_context)),
  serial_port(io_context)
{
  boost::thread([&]
  {
    try
    {
      io_context.run();
    }
    catch(const boost::system::system_error& error)
    {
    }
  });
}

SerialPortDebuggerPrivate::~SerialPortDebuggerPrivate()
{
  //io_context.stop();
  executor_work_guard.reset();
}
