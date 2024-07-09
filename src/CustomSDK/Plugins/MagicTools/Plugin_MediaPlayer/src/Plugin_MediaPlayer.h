#pragma once

#ifndef __PLUGIN_MEDIAPLAYER_H__
# define __PLUGIN_MEDIAPLAYER_H__

#include <MagicToolBox/MagicTool.h>

#include <QWidget>

class Plugin_MediaPlayer : public MagicTool
{
public:
  Plugin_MediaPlayer();
  ~Plugin_MediaPlayer() override;
public:
  QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const override;
};

#endif // !__PLUGIN_MEDIAPLAYER_H__
