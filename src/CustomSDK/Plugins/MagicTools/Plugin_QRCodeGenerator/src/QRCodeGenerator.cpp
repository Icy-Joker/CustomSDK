#include "stdafx.h"

#include "QRCodeGenerator/QRCodeGenerator.h"
#include "ui_QRCodeGenerator.h"

#include <qrencode.h>

QRCodeGenerator::QRCodeGenerator(QWidget* parent /*= nullptr*/,Qt::WindowFlags flags /*= Qt::WindowFlags()*/):
  QMainWindow(parent,flags),
  ui(new Ui::QRCodeGenerator())
{
  ui->setupUi(this);
}

QRCodeGenerator::~QRCodeGenerator()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void QRCodeGenerator::on_pushButton_GenerateQRCode_clicked()
{
  const std::string message_content = ui->lineEdit_MessageContent->text().toStdString();
  if(!message_content.empty())
  {
    if(QRcode* qr_code = QRcode_encodeString(message_content.c_str(),0,QRecLevel::QR_ECLEVEL_L,QR_MODE_8,1))
    {
      int qr_code_width = qr_code->width;
      QImage image_qr_code(qr_code_width,qr_code_width,QImage::Format::Format_Grayscale8);
      for(std::size_t i = 0;i < qr_code_width;++i)
      {
        for(std::size_t j = 0;j < qr_code_width;++j)
        {
          image_qr_code.setPixel(i,j,(qr_code->data[i * qr_code_width + j] & 0x01) ? 0x000000 : 0xffffff);
        }
      }
      ui->label_QRCode->setPixmap(QPixmap::fromImage(image_qr_code.scaled(ui->label_QRCode->width(),ui->label_QRCode->height())));
    }
  }
}
