#include "stdafx.h"

#include "BasicUIFramework/SplashScreen.h"

#include <QProgressBar>
#include <QLabel>
#include <QVBoxLayout>

SplashScreen::SplashScreen(const QPixmap& pixmap,Qt::WindowFlags flags):
  QSplashScreen(pixmap,flags),
  progress_bar(new QProgressBar(this)),
  label_info(new QLabel(this))
{
  // 创建一个进度条
  progress_bar = new QProgressBar(this);
  progress_bar->setRange(0,100);
  progress_bar->setAlignment(Qt::AlignCenter);

  // 创建一个标签，用于显示加载信息
  label_info = new QLabel(this);
  label_info->setAlignment(Qt::AlignCenter);
  label_info->setStyleSheet("QLabel { color : white; }");

  // 设置布局
  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addStretch();
  layout->addWidget(label_info);
  layout->addWidget(progress_bar);

  setLayout(layout);
}

SplashScreen::~SplashScreen()
{
  if(progress_bar)
  {
    delete progress_bar;
    progress_bar= nullptr;
  }
  if(label_info)
  {
    delete label_info;
    label_info = nullptr;
  }
}

void SplashScreen::showProgress(int value,const QString& message)
{
  progress_bar->setValue(value);
  showMessage(message,Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignRight,Qt::white);
}
