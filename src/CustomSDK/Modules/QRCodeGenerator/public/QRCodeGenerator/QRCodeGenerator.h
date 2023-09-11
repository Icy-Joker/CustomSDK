#pragma once

#ifndef __QRCODEGENERATOR_H__
# define __QRCODEGENERATOR_H__

#include <QWidget>

namespace Ui
{
  class QRCodeGenerator;
}

class QRCodeGenerator_API QRCodeGenerator : public QWidget
{
  Q_OBJECT
public:
  explicit QRCodeGenerator(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
  ~QRCodeGenerator();
private slots:
  void on_pushButton_clicked();
private:
  Ui::QRCodeGenerator* ui;
};

#endif //!__QRCODEGENERATOR_H__
