#include "stdafx.h"

#include "SerialPortDebuggerPrivate.h"

#include <iostream>
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
  executor_work_guard.reset();
  io_context.stop();
}

void SerialPortDebuggerPrivate::doSendMessage(const std::string& message_content)
{
  if(this->serial_port.is_open())
  {
    this->serial_port.async_write_some(boost::asio::buffer(message_content + "\r\n"),[&](const boost::system::error_code& error_code,std::size_t bytes_transferred)
    {
      if(!error_code)
      {
        //ui->textBrowser->append(QString("async_send[bytes send:%1 message:%2]").arg(QString::number(bytes_transferred)).arg(message_content.data()));
      }
      else
      {
        std::cout << "Error sending message" << std::endl;
        //ui->textBrowser->append(QString("error_code:%1\terror_message:%2").arg(QString::number(error_code.value()).arg(QString::fromUtf8(error_code.what()))));
      }
    });
  }
}

void SerialPortDebuggerPrivate::doReceiveMessage()
{
  if(this->serial_port.is_open())
  {
    static std::array<char,1024> read_buffer = {0};
    static boost::asio::streambuf stream_buf;
    boost::asio::async_read_until(this->serial_port,stream_buf,"\r\n",[&](const boost::system::error_code& error_code,std::size_t bytes_transferred)
    {
      if(!error_code)
      {
        std::istream is(&stream_buf);
        std::string line;
        //std::replace(line.begin(),line.end(),'\r','\n');
        std::getline(is,line);// 提取数据，去除 '\n'

        std::cout << line << std::endl;

        // 清除已处理的数据
        stream_buf.consume(bytes_transferred);

        this->doReceiveMessage();
      }
      else
      {
        //ui->textBrowser->append(QString("error_code:%1\terror_message:%2").arg(QString::number(error_code.value()).arg(QString::fromUtf8(error_code.what()))));
      }
    });
  }
}

bool SerialPortDebuggerPrivate::open(const std::string& serial_port_name)
{
  bool result = false;

  if(!this->serial_port.is_open())
  {
    try
    {
      this->serial_port.open(serial_port_name);
      result = this->serial_port.is_open();
    }
    catch(const boost::system::system_error& error)
    {
      if(const int error_code = error.code().value())
      {
        if(error_code == boost::asio::error::eof)
        {
          //ui->textBrowser->append(QString::fromUtf8("系统找不到指定的文件(%1)").arg(QString::fromStdString(serial_port_name)));
        }
      }
    }
  }

  return result;
}

void SerialPortDebuggerPrivate::setBaudRate(unsigned int baud_rate)
{
  if(this->serial_port.is_open())
  {
    this->serial_port.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
  }
}

void SerialPortDebuggerPrivate::setDataBits(unsigned int character_size)
{
  if(this->serial_port.is_open())
  {
    this->serial_port.set_option(boost::asio::serial_port_base::character_size(character_size));
  }
}

void SerialPortDebuggerPrivate::setStopBits(unsigned int stop_bits)
{
  if(this->serial_port.is_open())
  {
    this->serial_port.set_option(boost::asio::serial_port_base::stop_bits((boost::asio::serial_port_base::stop_bits::type)stop_bits));
  }
}

void SerialPortDebuggerPrivate::setParity(unsigned int parity)
{
  if(this->serial_port.is_open())
  {
    this->serial_port.set_option(boost::asio::serial_port_base::parity((boost::asio::serial_port_base::parity::type)parity));
  }
}

void SerialPortDebuggerPrivate::setFlowControl(unsigned int flow_control)
{
  if(this->serial_port.is_open())
  {
    this->serial_port.set_option(boost::asio::serial_port_base::flow_control((boost::asio::serial_port_base::flow_control::type)flow_control));
  }
}

bool SerialPortDebuggerPrivate::close()
{
  bool result = false;

  if(this->serial_port.is_open())
  {
    try
    {
      this->serial_port.close();

      result = !this->serial_port.is_open();
    }
    catch(const boost::system::system_error& error)
    {
      const int error_code = error.code().value();
      //ui->textBrowser->append(QString("error_code:%1\terror_message:%2").arg(QString::number(error_code).arg(QString::fromUtf8(error.what()))));
    }
  }

  return result;
}
