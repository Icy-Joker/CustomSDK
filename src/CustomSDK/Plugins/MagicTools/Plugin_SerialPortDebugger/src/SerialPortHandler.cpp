#include "stdafx.h"

#include "SerialPortHandler.h"

#include <BasicFramework/LogManager.h>

#include <boost/format.hpp>

SerialPortHandler::SerialPortHandler():
  executor_work_guard(boost::asio::make_work_guard(io_context)),
  serial_port(io_context)
{
  this->thread_io_context = boost::thread([&]()
  {
    io_context.run();
  });
}

SerialPortHandler::~SerialPortHandler()
{
  this->executor_work_guard.reset();
  this->thread_io_context.join();
}

void SerialPortHandler::setBaudRate(unsigned int baud_rate)
{
  if(this->serial_port.is_open())
  {
    this->serial_port.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
  }
}

void SerialPortHandler::setDataBits(unsigned int character_size)
{
  if(this->serial_port.is_open())
  {
    this->serial_port.set_option(boost::asio::serial_port_base::character_size(character_size));
  }
}

void SerialPortHandler::setStopBits(unsigned int stop_bits)
{
  if(this->serial_port.is_open())
  {
    this->serial_port.set_option(boost::asio::serial_port_base::stop_bits((boost::asio::serial_port_base::stop_bits::type)stop_bits));
  }
}

void SerialPortHandler::setParity(unsigned int parity)
{
  if(this->serial_port.is_open())
  {
    this->serial_port.set_option(boost::asio::serial_port_base::parity((boost::asio::serial_port_base::parity::type)parity));
  }
}

void SerialPortHandler::setFlowControl(unsigned int flow_control)
{
  if(this->serial_port.is_open())
  {
    this->serial_port.set_option(boost::asio::serial_port_base::flow_control((boost::asio::serial_port_base::flow_control::type)flow_control));
  }
}

bool SerialPortHandler::open(const std::string& port_name)
{
  bool result = false;

  if(!this->serial_port.is_open())
  {
    try
    {
      this->serial_port.open(port_name);
      result = this->serial_port.is_open();
      if(result)
      {
        LogManager::getInstance()->debug("串口打开成功");
      }
    }
    catch(const boost::system::system_error& error)
    {
      if(const int error_code = error.code().value())
      {
        LogManager::getInstance()->error(error.code().message().c_str());

        throw std::runtime_error(error.code().message().c_str());
      }
    }
  }

  return result;
}

bool SerialPortHandler::close()
{
  bool result = false;

  if(this->serial_port.is_open())
  {
    this->serial_port.close();
  }
  result = !this->serial_port.is_open();

  if(result)
  {
    LogManager::getInstance()->debug("串口关闭成功");
  }

  return result;
}

void SerialPortHandler::setAsyncReadCallback(AsyncReadCallback callback_message)
{
  this->callback_message = std::move(callback_message);
}

void SerialPortHandler::doAsyncWrite(const std::string& message_content)
{
  if(this->serial_port.is_open())
  {
    this->serial_port.async_write_some(boost::asio::buffer(message_content + "\r\n"),[=](const boost::system::error_code& error_code,std::size_t bytes_transferred)
    {
      if(!error_code)
      {
        if(callback_message)
        {
          callback_message(message_content);
        }

        LogManager::getInstance()->debug((boost::format("串口数据发送成功:[大小:%1%,%2%]") % message_content.size() % message_content).str().c_str());
      }
      else
      {
        LogManager::getInstance()->error((boost::format("串口数据发送失败：%1%") % error_code.message()).str().c_str());
      }
    });
  }
}

void SerialPortHandler::startAsyncRead()
{
  if(this->serial_port.is_open())
  {
    static std::array<char,1024> read_buffer = {0};
    static boost::asio::streambuf stream_buf;
    boost::asio::async_read_until(this->serial_port,stream_buf,"\r\n",[&](const boost::system::error_code& error_code,std::size_t bytes_transferred)
    {
      if(!error_code)
      {
        std::istream input_stream(&stream_buf);
        std::string message_content;

#ifdef BOOST_OS_MACOS
        std::getline(input_stream,message_content,'\r');
#else
        std::getline(is,line);
#endif

        if(callback_message)
        {
          callback_message(message_content);
        }

        LogManager::getInstance()->debug((boost::format("串口数据接收成功:[大小:%1%,%2%]") % message_content.size() % message_content).str().c_str());

        // 清除已处理的数据
        stream_buf.consume(bytes_transferred);

        this->startAsyncRead();
      }
      else
      {
        LogManager::getInstance()->error(error_code.message().c_str());
      }
    });
  }
}
