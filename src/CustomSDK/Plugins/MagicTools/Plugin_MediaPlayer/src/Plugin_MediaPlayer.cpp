#include "stdafx.h"

#include "Plugin_MediaPlayer.h"

#include <MediaPlayer/MediaPlayer.h>

Plugin_MediaPlayer::Plugin_MediaPlayer():
  MagicTool()
{
  setName("MediaPlayer");
  setDescription("MediaPlayer");
  setIcon(QIcon(":/icons/icon.png"));
  setType("常规");
}

Plugin_MediaPlayer::~Plugin_MediaPlayer()
{
}

QWidget* Plugin_MediaPlayer::createInstance(QWidget* parent,Qt::WindowFlags flags) const
{
  QWidget* result = nullptr;

  if(MediaPlayer* widget_instance = new MediaPlayer(parent,flags))
  {
    result = widget_instance;
  }

  return result;
}

extern "C"
{
  MediaPlayer_API Plugin_MediaPlayer* getPlugin()
  {
    static Plugin_MediaPlayer plugin_instance;
    return &plugin_instance;
  }
}
