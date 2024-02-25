#pragma once

#ifndef __SERIALPORTDEBUGGERPRIVATE_H__
# define __SERIALPORTDEBUGGERPRIVATE_H__

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/thread.hpp>

struct SerialPortDebuggerPrivate
{
  boost::asio::io_context io_context;
  boost::shared_ptr<boost::asio::serial_port> serial_port_ptr;
  boost::thread thread_io_context_run;
};

#endif // !__SERIALPORTDEBUGGERPRIVATE_H__
