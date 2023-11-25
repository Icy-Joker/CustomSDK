#include "stdafx.h"

#include "CustomControls/CustomWindowTitleBar.h"
#include "ui_CustomWindowTitleBar.h"

#include <QStyle>
#include <QMouseEvent>

CustomWindowTitleBar::CustomWindowTitleBar(QWidget * parent, Qt::WindowFlags flags) :
	QWidget(parent,flags),
	ui(new Ui::CustomWindowTitleBar())
{
  ui->setupUi(this);

	if (parent)
	{
    this->setAttribute(Qt::WidgetAttribute::WA_StyledBackground);

    if (parent->isTopLevel())
    {
      QIcon window_icon = parent->windowIcon();
      QString window_title = parent->windowTitle();

      ui->label_window_title->setText(window_title);

      //ui->label_window_icon->setIcon(window_icon);

      if(Qt::WindowFlags flags = parent->windowFlags())
      {
#ifdef __APPLE__
        //parent->setWindowFlags(Qt::WindowFlags(Qt::WindowType::FramelessWindowHint));
#else
        parent->setWindowFlags(Qt::WindowFlags((flags & Qt::WindowType::WindowType_Mask) | Qt::WindowType::FramelessWindowHint));
#endif
        ui->toolButton_Minimize->setVisible(Qt::WindowType::WindowMinimizeButtonHint == (flags & Qt::WindowType::WindowMinimizeButtonHint));
        ui->toolButton_Resize->setVisible(Qt::WindowType::WindowFullscreenButtonHint == (flags & Qt::WindowType::WindowFullscreenButtonHint));
        ui->toolButton_Close->setVisible(Qt::WindowType::WindowCloseButtonHint == (flags & Qt::WindowType::WindowCloseButtonHint));

        if(Qt::WindowType::MSWindowsFixedSizeDialogHint == (flags & Qt::WindowType::MSWindowsFixedSizeDialogHint))
        {
          ui->toolButton_Resize->setHidden(true);
        }

        this->setVisible(Qt::WindowType::FramelessWindowHint == (flags & Qt::WindowType::FramelessWindowHint));
      }
    }
    parent->installEventFilter(this);
  }
}

CustomWindowTitleBar::~CustomWindowTitleBar()
{
  if(QWidget* parent = this->parentWidget())
  {
    //removeEventFilter(this);
  }

  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

bool CustomWindowTitleBar::eventFilter(QObject * watched, QEvent * event)
{
	bool result = QObject::eventFilter(watched, event);

  if(QWidget* parent = this->parentWidget())
  {
    if(parent == watched && parent->isTopLevel())
    {
      switch (event->type())
      {
        case QEvent::Resize:
        {
          if (QWidget* widget = dynamic_cast<QWidget*>(watched))
          {
            ui->toolButton_Resize->style()->unpolish(ui->toolButton_Resize);
            ui->toolButton_Resize->style()->polish(ui->toolButton_Resize);
          }
          break;
        }
        case QEvent::WindowTitleChange:
        {
          break;
        }
        default:
        {
          break;
        }
      }
    }
  }
	
	return result;
}

void CustomWindowTitleBar::mouseMoveEvent(QMouseEvent * mouse_move_event)
{
  if(mouse_move_event)
  {
    QPoint point_previous = this->property("point_previous").value<QPoint>();
    Qt::MouseButtons mouse_buttons = mouse_move_event->buttons();

    if(Qt::MouseButton::LeftButton == (mouse_buttons & Qt::MouseButton::LeftButton))
    {
      QPoint point_current = mouse_move_event->globalPos();

      if(!point_previous.isNull() && point_previous != QPoint(0,0))
      {
        if(QWidget* parent = this->parentWidget())
        {
          parent->move(parent->geometry().topLeft() + (point_current - point_previous));
        }
      }
      point_previous = point_current;
    }
    else
    {
      point_previous = QPoint(0,0);
    }
    this->setProperty("point_previous",point_previous);
  }
  return QWidget::mouseMoveEvent(mouse_move_event);
}

void CustomWindowTitleBar::mouseDoubleClickEvent(QMouseEvent * mouse_double_click_event)
{   
  if(mouse_double_click_event)
  {
    if (QWidget* parent = this->parentWidget())
    {
      on_toolButton_Resize_clicked();
    }
  }

  return QWidget::mouseDoubleClickEvent(mouse_double_click_event);
}

void CustomWindowTitleBar::on_toolButton_Minimize_clicked()
{
	if (QWidget* parent = this->parentWidget())
	{
		parent->showMinimized();
	}
}

void CustomWindowTitleBar::on_toolButton_Resize_clicked()
{
	if (QWidget* parent = this->parentWidget())
	{
    if(ui->toolButton_Resize->isVisibleTo(parent) && ui->toolButton_Resize->isEnabledTo(parent))
    {
      if(parent->isFullScreen())
      {
        parent->showNormal();
      }
      else
      {
        parent->showFullScreen();
      }

    }
  }
}

void CustomWindowTitleBar::on_toolButton_Close_clicked()
{
	if (QWidget* parent = this->parentWidget())
	{
		parent->close();
	}
}
