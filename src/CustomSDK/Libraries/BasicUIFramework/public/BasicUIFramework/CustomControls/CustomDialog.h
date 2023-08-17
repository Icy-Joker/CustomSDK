#pragma once

#include <QDialog>

class BasicUIFramework_API CustomDialog : public QDialog
{
	Q_OBJECT
public:
	explicit CustomDialog(QWidget* parent = nullptr, Qt::WindowFlags flags= Qt::WindowFlags());
	~CustomDialog();
};
