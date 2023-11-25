#pragma once

#include <QMessageBox>
//BasicUIFramework_API
class  CustomMessageBox : public QMessageBox
{
	Q_OBJECT
public:
	explicit CustomMessageBox(QWidget* parent = nullptr);
  CustomMessageBox(Icon icon, const QString& title, const QString& text, StandardButtons buttons = NoButton, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
	~CustomMessageBox();
public:
	static StandardButton information(QWidget *parent, const QString &title,const QString &text, StandardButtons buttons = Ok, StandardButton defaultButton = NoButton);
	static StandardButton question(QWidget *parent, const QString &title, const QString &text, StandardButtons buttons = StandardButtons(Yes | No), StandardButton defaultButton = NoButton);
	static StandardButton warning(QWidget *parent, const QString &title, const QString &text, StandardButtons buttons = Ok, StandardButton defaultButton = NoButton);
	static StandardButton critical(QWidget *parent, const QString &title, const QString &text, StandardButtons buttons = Ok, StandardButton defaultButton = NoButton);
};
