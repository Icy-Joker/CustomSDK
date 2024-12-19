#include "stdafx.h"

#include "SerialPortDebugger/SerialPortDebugger.h"

#include <iostream>

#include "ui_SerialPortDebugger.h"

#include <boost/asio/io_context.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/serial_port.hpp>

#include <boost/filesystem.hpp>
#include <boost/make_shared.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/regex.hpp>

class SerialPortDebuggerPrivate
{
private:
  SerialPortDebuggerPrivate():
    executor_work_guard(boost::asio::make_work_guard(io_context)),
    serial_port(io_context)
  {
    boost::thread([&]
    {
      io_context.run();
      std::cout << "stopped ..." << std::endl;
    });
  }

  ~SerialPortDebuggerPrivate()
  {
    io_context.stop();
  }
private:
  boost::asio::io_context io_context;
  boost::asio::serial_port serial_port;
  boost::asio::executor_work_guard<boost::asio::io_context::executor_type> executor_work_guard;

  friend class SerialPortDebugger;
};

const std::vector<std::string> getAvailablePortName()
{
  std::vector<std::string> result;
#ifdef WIN32
  for (std::size_t i = 0; i <= UINT16_MAX; i++)
  {
    const std::string com_name = "COM" + std::to_string((long)i);
    HANDLE handle_com = CreateFileA(com_name.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
    if (INVALID_HANDLE_VALUE != handle_com)
    {
      result.push_back(com_name);

      CloseHandle(handle_com);
    }
  }
#else
  boost::filesystem::path device_directory("/dev");;
  for(const auto& entry : boost::filesystem::directory_iterator(device_directory))
  {
    if(entry.is_other() && boost::regex_match(entry.path().filename().string(),boost::regex("^tty(S|USB|ACM)[0-9]+$",boost::regex_constants::icase)))
    {
      result.push_back(entry.path().string());
    }
  }
#endif
  return result;
}

SerialPortDebugger::SerialPortDebugger(QWidget* parent /*= nullptr*/,Qt::WindowFlags flags /*= Qt::WindowFlags()*/) :
  QMainWindow(parent,flags),
  ui(new Ui::SerialPortDebugger()),
  private_ptr(new SerialPortDebuggerPrivate())
{
  ui->setupUi(this);

  const std::vector<std::string> abailable_port_names = getAvailablePortName();
  std::for_each(abailable_port_names.begin(),abailable_port_names.end(),[&](const std::string& port_name)
  {
    ui->comboBox_SerialPortName->addItem(QString::fromStdString(port_name));
  });
}

SerialPortDebugger::~SerialPortDebugger()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
  if(private_ptr)
  {
    delete private_ptr;
  }
}

void SerialPortDebugger::doOpenSerialPort()
{
  //获取串行端口参数
  std::string port_name = ui->comboBox_SerialPortName->currentText().toStdString();
  unsigned int baud_rate = ui->comboBox_BaudRate->currentText().toUInt();
  unsigned int character_size = ui->comboBox_CharacterSize->currentText().toUInt();
  unsigned int stop_bits = ui->comboBox_StopBits->currentText().toUInt();
  unsigned int parity = ui->comboBox_Parity->currentText().toUInt();
  unsigned int flow_control = ui->comboBox_FlowControl->currentText().toUInt();
  //打开并配置串口
  try
  {
    private_ptr->serial_port.open(port_name.c_str());
    if(private_ptr->serial_port.is_open())
    {
      private_ptr->serial_port.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
      private_ptr->serial_port.set_option(boost::asio::serial_port_base::character_size(character_size));
      private_ptr->serial_port.set_option(boost::asio::serial_port_base::stop_bits((boost::asio::serial_port_base::stop_bits::type)stop_bits));
      private_ptr->serial_port.set_option(boost::asio::serial_port_base::parity((boost::asio::serial_port_base::parity::type)parity));
      private_ptr->serial_port.set_option(boost::asio::serial_port_base::flow_control((boost::asio::serial_port_base::flow_control::type)flow_control));

      ui->pushButton_SerialPortControl->setText(QString::fromUtf8("关闭串口"));
    }
  }
  catch(const boost::system::system_error& error)
  {
    const int error_code = error.code().value();
    switch(error_code)
    {
      case boost::asio::error::eof:
      {
        ui->textBrowser->append(QString::fromUtf8("系统找不到指定的文件(%1)").arg(QString::fromStdString(port_name)));
        break;
      }
      default:
      {
        ui->textBrowser->append(QString("error_code:%1\terror_message:%2").arg(QString::number(error_code)).arg(QString::fromUtf8(error.what())));
        break;
      }
    }
  }
}

void SerialPortDebugger::doSendMessage(const std::string& message_content)
{
  if(private_ptr->serial_port.is_open())
  {
    private_ptr->serial_port.async_write_some(boost::asio::buffer(message_content),[&](const boost::system::error_code& error_code,std::size_t bytes_transferred)
    {
      if(!error_code)
      {
        ui->textBrowser->append(QString("async_send[bytes received:%1 message:%2]").arg(QString::number(bytes_transferred)).arg(message_content.data()));
      }
      else
      {
        ui->textBrowser->append(QString("error_code:%1\terror_message:%2").arg(QString::number(error_code.value()).arg(QString::fromUtf8(error_code.what()))));
      }
    });
  }
}

void SerialPortDebugger::doHandleMessage(const QByteArray& byte_array)
{
  doSendMessage(byte_array.data());
}

void SerialPortDebugger::doReceiveMessage()
{
  if(private_ptr->serial_port.is_open())
  {
    std::array<char,1024> read_buffer = {0};
    private_ptr->serial_port.async_read_some(boost::asio::buffer(read_buffer),[&](const boost::system::error_code& error_code,std::size_t bytes_transferred)
    {
      if(!error_code)
      {
        read_buffer[bytes_transferred] = '\0';

        doHandleMessage(read_buffer.data());

        doReceiveMessage();
      }
      else
      {
        ui->textBrowser->append(QString("error_code:%1\terror_message:%2").arg(QString::number(error_code.value()).arg(QString::fromUtf8(error_code.what()))));
      }
    });
  }
}

void SerialPortDebugger::doCloseSerialPort()
{
  try
  {
    private_ptr->serial_port.close();

    if(!private_ptr->serial_port.is_open())
    {
      ui->pushButton_SerialPortControl->setText(QString::fromUtf8("打开串口"));
    }
  }
  catch(const boost::system::system_error& error)
  {
    const int error_code = error.code().value();
    ui->textBrowser->append(QString("error_code:%1\terror_message:%2").arg(QString::number(error_code).arg(QString::fromUtf8(error.what()))));
  }
}

void SerialPortDebugger::on_pushButton_SerialPortControl_clicked()
{
  qDebug("on_pushButton_SerialPortControl_clicked");

  if(ui->pushButton_SerialPortControl->text() == QString::fromUtf8("打开串口"))
  {
    doOpenSerialPort();
  }
  else if(ui->pushButton_SerialPortControl->text() == QString::fromUtf8("关闭串口"))
  {
    doCloseSerialPort();
  }
}

void SerialPortDebugger::on_pushButton_SendMessage_clicked()
{
  qDebug("on_pushButton_SendMessage_clicked");

  if(private_ptr->serial_port.is_open())
  {
    std::string message_content = ui->lineEdit_UserMessage->text().toStdString();

    doSendMessage(message_content);
  }
}
