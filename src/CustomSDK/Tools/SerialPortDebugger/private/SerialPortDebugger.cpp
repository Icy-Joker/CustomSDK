#include "stdafx.h"

#include "SerialPortDebugger.h"
#include "SerialPortDebuggerPrivate.h"
#include "ui_SerialPortDebugger.h"

#include <boost/make_shared.hpp>

SerialPortDebugger::SerialPortDebugger(QWidget* parent /*= nullptr*/,Qt::WindowFlags flags /*= Qt::WindowFlags()*/) :
  QMainWindow(parent,flags),
  _p(new SerialPortDebuggerPrivate()),
  ui(new Ui::SerialPortDebugger())
{
  ui->setupUi(this);

  _p->thread_io_context_run = boost::thread([&]
  {
    while(!boost::this_thread::interruption_requested())
    {
      _p->io_context.run();

      boost::this_thread::sleep_for(boost::chrono::milliseconds(0));
    }
  });
}

SerialPortDebugger::~SerialPortDebugger()
{
  if(_p)
  {
    if(_p->thread_io_context_run.joinable())
    {
      _p->thread_io_context_run.interrupt();
      _p->thread_io_context_run.join();
    }

    delete _p;
    _p = nullptr;
  }
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void SerialPortDebugger::on_pushButton_SerialPortControl_clicked()
{
  qDebug("on_pushButton_SerialPortControl_clicked");

  if(ui->pushButton_SerialPortControl->text() == QString::fromLocal8Bit("打开串口"))
  {
    //获取串行端口参数
    std::string port_name = ui->comboBox_SerialPortName->currentText().toStdString();
    unsigned int baud_rate = ui->comboBox_BaudRate->currentText().toUInt();
    unsigned int character_size = ui->comboBox_CharacterSize->currentText().toUInt();
    unsigned int stop_bits = ui->comboBox_StopBits->currentText().toUInt();
    unsigned int parity = ui->comboBox_Parity->currentText().toUInt();
    unsigned int flow_control = ui->comboBox_FlowControl->currentText().toUInt();
    //打开并配置串口
    if(_p->serial_port_ptr = boost::make_shared<boost::asio::serial_port>(_p->io_context))
    {
      try
      {
        _p->serial_port_ptr->open(port_name.c_str());
        if(_p->serial_port_ptr->is_open())
        {
          ui->pushButton_SerialPortControl->setText(QString::fromLocal8Bit("关闭串口"));

          _p->serial_port_ptr->set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
          _p->serial_port_ptr->set_option(boost::asio::serial_port_base::character_size(character_size));
          _p->serial_port_ptr->set_option(boost::asio::serial_port_base::stop_bits((boost::asio::serial_port_base::stop_bits::type) stop_bits));
          _p->serial_port_ptr->set_option(boost::asio::serial_port_base::parity((boost::asio::serial_port_base::parity::type) parity));
          _p->serial_port_ptr->set_option(boost::asio::serial_port_base::flow_control((boost::asio::serial_port_base::flow_control::type) flow_control));

          std::array<char,1024> read_buffer;
          static std::function<void(const boost::system::error_code&,std::size_t)> function_async_receive_message = [&](const boost::system::error_code& error_code,std::size_t bytes_transferred)
          {
            if(error_code.value() == 0)
            {
              //read_buffer[bytes_transferred] = '\0';
              ui->textBrowser->append(QString("bytes received:%1 message:%2").arg(QString::number(bytes_transferred)).arg(read_buffer.data()));
              if(_p->serial_port_ptr && _p->serial_port_ptr->is_open())
              {
                _p->serial_port_ptr->async_read_some(boost::asio::buffer(read_buffer),function_async_receive_message);
              }
            }
          };
          _p->serial_port_ptr->async_read_some(boost::asio::buffer(read_buffer),function_async_receive_message);
        }
      }
      catch(const boost::system::system_error& error)
      {
        const int error_code = error.code().value();
        switch(error_code)
        {
          case boost::asio::error::eof:
          {
            ui->textBrowser->append(QString::fromLocal8Bit("系统找不到指定的文件(%1)").arg(QString::fromStdString(port_name)));
            break;
          }
          default:
          {
            ui->textBrowser->append(QString("error_code:%1\terror_message:%2").arg(QString::number(error_code)).arg(QString::fromLocal8Bit(error.what())));
            break;
          }
        }
      }
    }
  }
  else if(ui->pushButton_SerialPortControl->text() == QString::fromLocal8Bit("关闭串口"))
  {
    ui->pushButton_SerialPortControl->setText(QString::fromLocal8Bit("打开串口"));

    if(_p->serial_port_ptr)
    {
      if(_p->serial_port_ptr->is_open())
      {
        _p->serial_port_ptr->close();
      }
      _p->serial_port_ptr.reset();
    }
  }
}

void SerialPortDebugger::on_pushButton_SendMessage_clicked()
{
  qDebug("on_pushButton_SendMessage_clicked");

  if(_p->serial_port_ptr && _p->serial_port_ptr->is_open())
  {
    std::string user_message = ui->lineEdit_UserMessage->text().toStdString();
    _p->serial_port_ptr->async_write_some(boost::asio::buffer(user_message.data(),user_message.length()+1),[&](const boost::system::error_code& error_code,std::size_t bytes_transferred)
    {
      if(error_code.value() == 0)
      {
        ui->textBrowser->append(QString("bytes_transferred:%1 message:%2").arg(QString::number(bytes_transferred)).arg(QString::fromLocal8Bit(user_message.c_str())));
      }
    });
  }
}