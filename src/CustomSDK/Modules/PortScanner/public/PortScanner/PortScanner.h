#pragma once

#include <QWidget>

namespace Ui
{
	class PortScanner;
}

class PortScanner : public QWidget
{
	Q_OBJECT
public:
	explicit PortScanner(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
	~PortScanner();
private slots:
  void on_pushButton_DoScanning_clicked();
private:
	Ui::PortScanner* ui;
};
