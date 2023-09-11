#include "stdafx.h"
#include "QRCodeGenerator.h"
#include "ui_QRCodeGenerator.h"

#include <qrencode/qrencode.h>

#include <sstream>

#include <QImage>

QRCodeGenerator::QRCodeGenerator(QWidget* parent,Qt::WindowFlags flags):
  QWidget(parent,flags),
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

void QRCodeGenerator::on_pushButton_clicked()
{
  const std::string& message_context = ui->lineEdit->text().toStdString();
  if(!message_context.empty())
  {
    if(QRcode* qrcode = QRcode_encodeString(message_context.c_str(), 7, QR_ECLEVEL_L, QR_MODE_8, 1))
    {
      QImage img_bmp(qrcode->width,qrcode->width,QImage::Format_RGB32);
      // 打印 QR 码数据
      for(int y = 0; y < qrcode->width; y++)
      {
        for(int x = 0; x < qrcode->width; x++) 
        {
          img_bmp.setPixel(x,y,qrcode->data[ y * qrcode->width + x] & 0x01 ? qRgb(255,255,255) : qRgb(0,0,0));
        }
      }
      
      ui->label->setScaledContents(true);
      ui->label->setPixmap(QPixmap::fromImage(img_bmp));
      //ui->label->setPixmap(QPixmap::fromImage(img_bmp).scaled(ui->label->size(),Qt::AspectRatioMode::KeepAspectRatio, Qt::SmoothTransformation));

      QRcode_free(qrcode);
    }
  }
}
