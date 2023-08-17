#include "CustomWindow.h"

#include "CustomControls/CustomWindowTitleBar.h"

#include <QVBoxLayout>
#include <QIcon>
#include <QEvent>

CustomWindow::CustomWindow(QWidget* parent /* = nullptr */, Qt::WindowFlags flags /* = Qt::Widget */) :
	QWidget(parent, flags),
	title_bar(new CustomWindowTitleBar(this)),
	widget_center(new QWidget(this))
{
	initializeUI();
	initializeFunction();
	connectSignals();
}

CustomWindow::~CustomWindow()
{
	if (QLayout* layout = this->layout())
	{
		if (widget_center)
		{
			widget_center->removeEventFilter(this);
			layout->removeWidget(widget_center);
			widget_center = nullptr;
		}
	}
}

void CustomWindow::setCentralWidget(QWidget * widget)
{
	if (QLayout* layout = this->layout())
	{
		if (widget_center)
		{
			layout->removeWidget(widget_center);
			widget_center = nullptr;
		}
		if (widget_center = widget)
		{
			widget_center->installEventFilter(this);

			layout->addWidget(widget_center);

			this->setWindowIcon(widget_center->windowIcon());
			this->setWindowTitle(widget_center->windowTitle());
			//this->adjustSize();
		}
	}
}

QWidget * CustomWindow::centralWidget()
{
	return widget_center;
}

bool CustomWindow::eventFilter(QObject * watched, QEvent * event)
{
	bool result = QObject::eventFilter(watched, event);
	switch (event->type())
	{
		case QEvent::WindowIconChange:
		{
			if (title_bar)
			{
				if (QWidget* widget = dynamic_cast<QWidget*>(watched))
				{
					if (widget == this || widget == widget_center)
					{
						title_bar->setWindowIcon(widget->windowIcon());
					}
				}
			}
			break;
		}
		case QEvent::WindowTitleChange:
		{
			if (title_bar)
			{
				if (QWidget* widget = dynamic_cast<QWidget*>(watched))
				{
					if (widget == this || widget == widget_center)
					{
						title_bar->setWindowTitle(widget->windowTitle());
					}
				}
			}
			break;
		}
		default:
			break;
	}
	return result;
}

void CustomWindow::initializeUI()
{
	if (QVBoxLayout* vLayout = new QVBoxLayout(this))
	{
		this->setLayout(vLayout);

		vLayout->setContentsMargins(0, 0, 0, 0);
		vLayout->setSpacing(0);

		if (QWidget* widget_top_levle= this->topLevelWidget())
		{
			if (QWidget* parent=this->parentWidget())
			{
				if (parent== widget_top_levle|| widget_top_levle ==this)
				{
					vLayout->addWidget(title_bar);
          #ifdef __APPLE__
          title_bar->setVisible(false);
          #endif
				}
			}
		}
		vLayout->addWidget(widget_center);
	}
}

void CustomWindow::initializeFunction()
{
	this->installEventFilter(this);
}

void CustomWindow::connectSignals()
{
}
