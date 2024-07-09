#pragma once

#ifndef __MEDIAPLAYER_H__
# define __MEDIAPLAYER_H__

#include <QMainWindow>
#include <QMediaPlayer>

namespace Ui
{
  class MediaPlayer;
}

class MediaPlayer : public QMainWindow
{
  Q_OBJECT
public:
  explicit MediaPlayer(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
  ~MediaPlayer() override;
protected:
  bool eventFilter(QObject* obj,QEvent* event) override;
private slots:
  void on_action_Load_triggered();
private:
  Ui::MediaPlayer* ui;

  QMediaPlayer* media_player;
};

#endif // !__MEDIAPLAYER_H__
