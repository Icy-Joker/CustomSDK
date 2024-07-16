#pragma once

#ifndef __BASE64CONVERTER_H__
# define __BASE64CONVERTER_H__

#include <QMainWindow>

namespace Ui
{
  class Base64Converter;
}

class Base64Converter : public QMainWindow
{
  Q_OBJECT
public:
  explicit Base64Converter(QWidget *parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
  ~Base64Converter() override;
private:
  const QByteArray doGenerateBase64(const QByteArray& byte_array);
  const QByteArray doParseBase64(const QByteArray& byte_array);
private:
  void doGenerateBase64();
  void doParseBase64();
private slots:
  void on_pushButton_ConvertToBase64_clicked();
  void on_pushButton_ConvertFromBase64_clicked();
private:
  Ui::Base64Converter *ui;
};

#endif // !__BASE64CONVERTER_H__
