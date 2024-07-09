#pragma once

#ifndef __QRCODEGENERATOR_H__
# define __QRCODEGENERATOR_H__

#include <QMainWindow>

namespace Ui
{
  class QRCodeGenerator;
}

class QRCodeGenerator : public QMainWindow
{
  Q_OBJECT
public:
  explicit QRCodeGenerator(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
  ~QRCodeGenerator() override;
private slots:
  void on_pushButton_GenerateQRCode_clicked();
private:
  Ui::QRCodeGenerator* ui;
};

#endif // !__QRCODEGENERATOR_H__
