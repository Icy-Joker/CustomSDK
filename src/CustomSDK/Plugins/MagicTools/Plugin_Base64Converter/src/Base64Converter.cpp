#include "stdafx.h"

#include "Base64Converter/Base64Converter.h"
#include "ui_Base64Converter.h"

#include <QFile>
#include <QBuffer>

Base64Converter::Base64Converter(QWidget* parent /*= nullptr*/,Qt::WindowFlags flags /*= Qt::WindowFlags()*/):
  QMainWindow(parent,flags),
  ui(new Ui::Base64Converter())
{
  ui->setupUi(this);

  QString file_path = "slena_color.gif";
  if(QFile::exists(file_path))
  {
    QImage image;
    if(image.load(file_path))
    {
      ui->label->setPixmap(QPixmap::fromImage(image));

      ui->stackedWidget->setCurrentWidget(ui->page_ImageView);
    }
    else
    {
      QFile file(file_path);
      if(file.open(QIODevice::ReadOnly))
      {
        ui->plainTextEdit->setPlainText(file.readAll());
        file.close();

        ui->stackedWidget->setCurrentWidget(ui->page_TextView);
      }
    }
  }
  else
  {
  }
}

Base64Converter::~Base64Converter()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void Base64Converter::on_pushButton_ConvertToBase64_clicked()
{
  if(ui->stackedWidget->currentWidget() == ui->page_TextView)
  {
    QString text_content = ui->plainTextEdit->toPlainText();
    QString base_64_string = text_content.toUtf8().toBase64();

    ui->plainTextEdit_Base64->setPlainText(base_64_string);
  }
  else if(ui->stackedWidget->currentWidget() == ui->page_ImageView)
  {
    QImage image = ui->label->pixmap().toImage();
    QByteArray byte_array;
    QBuffer buffer(&byte_array);
    image.save(&buffer,"PNG");
    QString base_64_string = byte_array.toBase64();

    ui->plainTextEdit_Base64->setPlainText(base_64_string);
  }
}

void Base64Converter::on_pushButton_ConvertFromBase64_clicked()
{
  QString base_64_string = ui->plainTextEdit_Base64->toPlainText();
  QByteArray byte_array = QByteArray::fromBase64(base_64_string.toUtf8());

  if(!byte_array.isNull())
  {
    QImage image;
    if(image.loadFromData(byte_array))
    {
      ui->label->setPixmap(QPixmap::fromImage(image));

      ui->stackedWidget->setCurrentWidget(ui->page_ImageView);
    }
    else
    {
      ui->plainTextEdit->setPlainText(QString::fromUtf8(byte_array));
      ui->stackedWidget->setCurrentWidget(ui->page_TextView);
    }
  }
}
