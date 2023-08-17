
#include "CustomControls/CustomMainWindow.h"
#include "CustomControls/CustomWindowTitleBar.h"

CustomMainWindow::CustomMainWindow(QWidget * parent, Qt::WindowFlags flags) :
	QMainWindow(parent, flags)
{	
  QMainWindow::setMenuWidget(new CustomWindowTitleBar(this));

  if(QStatusBar* status_bar = QMainWindow::statusBar())
  {
  }
}

CustomMainWindow::~CustomMainWindow()
{
}
