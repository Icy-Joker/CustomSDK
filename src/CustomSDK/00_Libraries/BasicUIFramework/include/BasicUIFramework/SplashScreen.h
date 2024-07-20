#pragma once

#ifndef SPLASHSCREEN_H
# define SPLASHSCREEN_H

#include <QSplashScreen>

class QProgressBar;
class QLabel;

class BasicUIFramework_API SplashScreen : public QSplashScreen
{
  Q_OBJECT
public:
  explicit SplashScreen(const QPixmap& pixmap = QPixmap(),Qt::WindowFlags flags = Qt::WindowFlags());
  ~SplashScreen();
public:
  void showProgress(int value,const QString& message);
private:
  QProgressBar* progress_bar;
  QLabel* label_info;
};

#endif//!SPLASHSCREEN_H
