#pragma once

#include <QMainWindow>

class BasicUIFramework_API CustomMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit CustomMainWindow(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
	~CustomMainWindow();
};
