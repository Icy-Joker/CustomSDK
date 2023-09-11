#include "stdafx.h"
#include "CustomControls/CustomMessageBox.h"
#include "CustomControls/CustomWindowTitleBar.h"

#include <QLayout>

CustomMessageBox::CustomMessageBox(QWidget* parent /* = nullptr */) :
  QMessageBox(CustomMessageBox::Icon::NoIcon, QString(), QString(), CustomMessageBox::StandardButtons(), parent, Qt::WindowFlags())
{
}

CustomMessageBox::CustomMessageBox(Icon icon, const QString & title, const QString & text, StandardButtons buttons, QWidget * parent, Qt::WindowFlags flags) :
	QMessageBox(icon, title, text, buttons, parent, flags)
{
  if(this->isTopLevel())
  {
    if(QLayout* default_layout = QMessageBox::layout())
    {
      default_layout->setContentsMargins(0,0,0,0);
      default_layout->setMenuBar(new CustomWindowTitleBar(this));
    }
  }
}

CustomMessageBox::~CustomMessageBox()
{
}

CustomMessageBox::StandardButton CustomMessageBox::information(QWidget * parent, const QString & title, const QString & text, StandardButtons buttons, StandardButton defaultButton)
{
	CustomMessageBox message_box(QMessageBox::Icon::Information, title, text, buttons, parent);
	message_box.setDefaultButton(defaultButton);

	return (CustomMessageBox::StandardButton)message_box.exec();
}

CustomMessageBox::StandardButton CustomMessageBox::question(QWidget * parent, const QString & title, const QString & text, StandardButtons buttons, StandardButton defaultButton)
{
	CustomMessageBox message_box(QMessageBox::Icon::Question, title, text, buttons, parent);
	message_box.setDefaultButton(defaultButton);

	return (CustomMessageBox::StandardButton)message_box.exec();
}

CustomMessageBox::StandardButton CustomMessageBox::warning(QWidget * parent, const QString & title, const QString & text, StandardButtons buttons, StandardButton defaultButton)
{
	CustomMessageBox message_box(QMessageBox::Icon::Warning, title, text, buttons, parent);
	message_box.setDefaultButton(defaultButton);

	return (CustomMessageBox::StandardButton)message_box.exec();
}

CustomMessageBox::StandardButton CustomMessageBox::critical(QWidget * parent, const QString & title, const QString & text, StandardButtons buttons, StandardButton defaultButton)
{
	CustomMessageBox message_box(QMessageBox::Icon::Critical, title, text, buttons, parent);
	message_box.setDefaultButton(defaultButton);

	return (CustomMessageBox::StandardButton)message_box.exec();
}
