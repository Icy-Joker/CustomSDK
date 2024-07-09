#include "stdafx.h"

#include "SerialPortDebugger/SerialPortDebugger.h"
#include "SerialPortHandler.h"

#include <iostream>

#include "ui_SerialPortDebugger.h"

#include <boost/filesystem.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/regex.hpp>
#include <boost/asio.hpp>
#include <boost/asio/streambuf.hpp>

const std::vector<std::string> getAvailablePortName()
{
  std::vector<std::string> result;
#ifdef WIN32
  for(std::size_t i = 0;i <= UINT16_MAX;i++)
  {
    const std::string com_name = "COM" + std::to_string((long)i);
    HANDLE handle_com = CreateFileA(com_name.c_str(), GENERIC_READ | GENERIC_WRITE,0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED,0);
    if(INVALID_HANDLE_VALUE != handle_com)
    {
      result.push_back(com_name);

      CloseHandle(handle_com);
    }
  }
#else
  boost::filesystem::path device_directory("/dev");;
  for(const auto& entry : boost::filesystem::directory_iterator(device_directory))
  {
#ifdef BOOST_OS_MACOS
    if(entry.is_other() && boost::regex_match(entry.path().filename().string(),boost::regex("^tty\\.USB\\S*",boost::regex_constants::icase)))
#elif defined BOOST_OS_LINUX
      if(entry.is_other() && boost::regex_match(entry.path().filename().string(),boost::regex("^tty(S|USB|ACM)[0-9]+$",boost::regex_constants::icase)))
#endif
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
  serial_port_handler(new SerialPortHandler())
{
  ui->setupUi(this);

  const std::vector<std::string> abailable_port_names = getAvailablePortName();
  std::for_each(abailable_port_names.begin(),abailable_port_names.end(),[&](const std::string& port_name)
  {
    ui->comboBox_SerialPortName->addItem(QString::fromStdString(port_name));
  });

  connect(this,SIGNAL(signal_SendMessage()),this,SLOT(on_pushButton_SendMessage_clicked()));
}

SerialPortDebugger::~SerialPortDebugger()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
  if(serial_port_handler)
  {
    delete serial_port_handler;
    serial_port_handler = nullptr;
  }
}

void SerialPortDebugger::on_pushButton_SerialPortControl_clicked()
{
  if(ui->pushButton_SerialPortControl->text() == QString::fromUtf8("打开串口"))
  {
    //获取串行端口参数
    const std::string serial_port_name = ui->comboBox_SerialPortName->currentText().toStdString();
    unsigned int baud_rate = ui->comboBox_BaudRate->currentText().toUInt();
    unsigned int character_size = ui->comboBox_CharacterSize->currentText().toUInt();
    unsigned int stop_bits = ui->comboBox_StopBits->currentIndex();
    unsigned int parity = ui->comboBox_Parity->currentText().toUInt();
    unsigned int flow_control = ui->comboBox_FlowControl->currentText().toUInt();
    //打开并配置串口
    try
    {
      if(this->serial_port_handler->open(serial_port_name))
      {
        this->serial_port_handler->setBaudRate(baud_rate);
        this->serial_port_handler->setDataBits(character_size);
        this->serial_port_handler->setStopBits(stop_bits);
        this->serial_port_handler->setParity(parity);
        this->serial_port_handler->setFlowControl(flow_control);

        this->serial_port_handler->setAsyncReadCallback([&](const std::string& message_content)
        {
          ui->textBrowser->append(QString::fromUtf8("数据接收:[大小:%1 内容:%2]").arg(QString::number(message_content.length()),QString::fromStdString(message_content)));
        });

        ui->pushButton_SerialPortControl->setText(QString::fromUtf8("关闭串口"));
        ui->pushButton_SendMessage->setEnabled(true);
      }
    }
    catch(const std::runtime_error& error)
    {
      ui->textBrowser->append(QString::fromUtf8("串口打开失败:%1").arg(QString::fromStdString(error.what())));
    }
  }
  else if(ui->pushButton_SerialPortControl->text() == QString::fromUtf8("关闭串口"))
  {
    if(this->serial_port_handler->close())
    {
      ui->pushButton_SerialPortControl->setText(QString::fromUtf8("打开串口"));
      ui->pushButton_SendMessage->setEnabled(false);
    }
  }
}

void SerialPortDebugger::on_checkBox_EnableAutoSend_stateChanged(int check_state)
{
  if(check_state == Qt::CheckState::Checked)
  {
    ui->spinBox->setEnabled(false);
    ui->pushButton_SendMessage->setEnabled(false);

    boost::thread([this]()
    {
      while(ui->checkBox_EnableAutoSend->isChecked())
      {
        emit signal_SendMessage();
        boost::this_thread::sleep_for(boost::chrono::milliseconds(ui->spinBox->value()));
      }
    });
  }
  else if(check_state == Qt::CheckState::Unchecked)
  {
    ui->spinBox->setEnabled(true);
    ui->pushButton_SendMessage->setEnabled(true);
  }
}

void SerialPortDebugger::on_pushButton_SendMessage_clicked()
{
  std::string message_content = ui->lineEdit_UserMessage->text().toStdString();

  if(serial_port_handler)
  {
    this->serial_port_handler->doAsyncWrite(message_content);
  }
}
