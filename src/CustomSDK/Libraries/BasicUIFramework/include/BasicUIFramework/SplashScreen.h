#pragma once

#ifndef __SPLASHSCREEN_H__
# define __SPLASHSCREEN_H__

#include <QSplashScreen>

class QProgressBar;
class QLabel;

class BasicUIFramework_API SplashScreen : public QSplashScreen
{
  Q_OBJECT
public:
  explicit SplashScreen(const QPixmap &pixmap = QPixmap(), Qt::WindowFlags flags = Qt::WindowFlags());
  ~SplashScreen();
public:
  void showProgress(int value,const QString& message);
private:
  QProgressBar *progress_bar;
  QLabel* label_info;
};

#endif // !__SPLASHSCREEN_H__
