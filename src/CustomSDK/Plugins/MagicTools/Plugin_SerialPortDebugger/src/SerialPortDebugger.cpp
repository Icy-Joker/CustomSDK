#include "stdafx.h"

#include "SerialPortDebugger/SerialPortDebugger.h"

#include <iostream>

#include "ui_SerialPortDebugger.h"

#include "SerialPortDebuggerPrivate.h"

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

  connect(this,SIGNAL(signal_SendMessage()),this,SLOT(on_pushButton_SendMessage_clicked()));
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
    private_ptr = nullptr;
  }
}

void SerialPortDebugger::doHandleMessage(const QByteArray& byte_array)
{
  //doSendMessage(byte_array.data());
  ui->textBrowser->append(QString("async_received[bytes received:%1 message:%2]").arg(QString::number(byte_array.length()),byte_array.data()));
}

void SerialPortDebugger::on_pushButton_SerialPortControl_clicked()
{
  if(ui->pushButton_SerialPortControl->text() == QString::fromUtf8("打开串口"))
  {
    //获取串行端口参数
    const std::string serial_port_name = "/dev/tty.usbserial-2130";//ui->comboBox_SerialPortName->currentText().toStdString();
    unsigned int baud_rate = ui->comboBox_BaudRate->currentText().toUInt();
    unsigned int character_size = ui->comboBox_CharacterSize->currentText().toUInt();
    unsigned int stop_bits = ui->comboBox_StopBits->currentIndex();
    unsigned int parity = ui->comboBox_Parity->currentText().toUInt();
    unsigned int flow_control = ui->comboBox_FlowControl->currentText().toUInt();
    //打开并配置串口
    if(private_ptr->open(serial_port_name))
    {
      private_ptr->setBaudRate(baud_rate);
      private_ptr->setDataBits(character_size);
      private_ptr->setStopBits(stop_bits);
      private_ptr->setParity(parity);
      private_ptr->setFlowControl(flow_control);

      private_ptr->doReceiveMessage();

      ui->pushButton_SerialPortControl->setText(QString::fromUtf8("关闭串口"));
    }
  }
  else if(ui->pushButton_SerialPortControl->text() == QString::fromUtf8("关闭串口"))
  {
    if(private_ptr->close())
    {
      ui->pushButton_SerialPortControl->setText(QString::fromUtf8("打开串口"));
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

  if(private_ptr)
  {
    private_ptr->doSendMessage(message_content);
  }
}
