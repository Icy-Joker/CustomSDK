#include "stdafx.h"

#include "TCPServer.h"
#include "TCPServerPrivate.h"
#include "ui_TCPServer.h"

#include <boost/function.hpp>
#include <boost/thread.hpp>

TCPServer::TCPServer(QWidget* parent /*= nullptr*/,Qt::WindowFlags flags /*= Qt::WindowFlags()*/):
  QWidget(parent,flags),
  ui(new Ui::TCPServer()),
  _p(new TCPServerPrivate())
{
  ui->setupUi(this);

  ui->lineEdit_ServerAddress->setValidator(new QRegExpValidator(QRegExp("127.0.0.1"),this));
}

TCPServer::~TCPServer()
{
  if(_p)
  {
    delete _p;
    _p = nullptr;
  }
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void TCPServer::on_pushButton_ServerControl_clicked()
{
  qDebug("on_pushButton_ServerControl_clicked");
  if(ui->pushButton_ServerControl->text() == QString::fromLocal8Bit("¿ªÊ¼¼àÌý"))
  {
    std::string ip_address = ui->lineEdit_ServerAddress->text().toLocal8Bit().constData();
    unsigned short ip_port = ui->spinBox_ServerPort->value();

    _p->endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip_address),ip_port);
    _p->socket = boost::make_shared<boost::asio::ip::tcp::socket>(_p->io_context);
    _p->acceptor = boost::make_shared<boost::asio::ip::tcp::acceptor>(_p->io_context,_p->endpoint);

    std::array<char,1024> receive_buffer = {'\0'};
    boost::function<void(const boost::system::error_code& error_code)> function_async_accept = [&](const boost::system::error_code& error_code)
    {
      if(!error_code)
      {
        qDebug("New Connextion");

        boost::thread thread_async_receive([&]
        {
          static boost::function<void(const boost::system::error_code&,std::size_t)> function_async_receive = [&](const boost::system::error_code& error_code,std::size_t bytes_transferred)
          {
            if(!error_code)
            {
              qDebug("bytes_transferred:%d\t%s",bytes_transferred,receive_buffer.data());
              if(ui->checkBox_EnableAutoEcho->isChecked())
              {
                _p->socket->async_send(boost::asio::buffer(receive_buffer),[&](const boost::system::error_code& error_code,std::size_t bytes_transferred)
                {
                  if(!error_code)
                  {
                    qDebug("bytes_transferred:%d:%s",bytes_transferred,receive_buffer.data());
                  }
                });
              }
              _p->socket->async_receive(boost::asio::buffer(receive_buffer),function_async_receive);
            }
            else
            {
              qDebug("error_code:%d",error_code);
            }
          };

          if(_p->socket->is_open())
          {
            _p->socket->async_receive(boost::asio::buffer(receive_buffer),function_async_receive);
          }
        });
      }
      else
      {
      }
    };
    _p->acceptor->async_accept(*(_p->socket.get()),function_async_accept);

    _p->thread_io_context = boost::thread([&]
    {
      while(true)
      {
        try
        {
          boost::this_thread::interruption_point();

          _p->io_context.run();

          boost::this_thread::sleep_for(boost::chrono::seconds(0));
        }
        catch(const std::exception&)
        {
          break;
        }
      }
    });

    ui->pushButton_ServerControl->setText(QString::fromLocal8Bit("½áÊø¼àÌý"));
  }
  else if(ui->pushButton_ServerControl->text() == QString::fromLocal8Bit("½áÊø¼àÌý"))
  { 
    try
    {
      if(_p->socket)
      {
        _p->socket->cancel();
      }
    }
    catch(const boost::system::system_error& error)
    {
    }

    try
    {
      if(_p->acceptor)
      {
        _p->acceptor->cancel();
      }
    }
    catch(const boost::system::system_error& error)
    {
    }

    _p->thread_io_context.interrupt();
    if(_p->thread_io_context.joinable())
    {
      _p->thread_io_context.join();
    }

    ui->pushButton_ServerControl->setText(QString::fromLocal8Bit("¿ªÊ¼¼àÌý"));
  }
}

void TCPServer::on_checkBox_EnableAutoEcho_stateChanged(int check_status)
{
  ui->pushButton_SendResponseMessage->setEnabled(Qt::CheckState::Checked != (Qt::CheckState) check_status);
}

void TCPServer::on_pushButton_SendResponseMessage_clicked()
{
  qDebug("on_pushButton_SendResponseMessage");
}
