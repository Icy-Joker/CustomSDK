#include "stdafx.h"

#include "MediaPlayer/MediaPlayer.h"
#include "ui_MediaPlayer.h"

#include <QAudioOutput>
#include <QFileDialog>
#include <QMouseEvent>

MediaPlayer::MediaPlayer(QWidget* parent /*= nullptr*/,Qt::WindowFlags flags /*= Qt::WindowFlags()*/):
  QMainWindow(parent,flags),
  media_player(new QMediaPlayer(this)),
  ui(new Ui::MediaPlayer())
{
  ui->setupUi(this);

  ui->menubar->setNativeMenuBar(false);

  media_player->setVideoOutput(ui->videoWidget);
  media_player->setAudioOutput(new QAudioOutput(this));

  connect(media_player,&QMediaPlayer::errorOccurred,this,[this](QMediaPlayer::Error error,const QString& error_string)
  {
    qDebug() << "Error:" << error << error_string;
  });
  connect(media_player,&QMediaPlayer::mediaStatusChanged,this,[this](QMediaPlayer::MediaStatus status)
  {
    switch(status)
    {
      case QMediaPlayer::MediaStatus::LoadedMedia:
      {
        ui->horizontalSlider_Progress->setValue(0);
        break;
      }
      case QMediaPlayer::MediaStatus::EndOfMedia:
      {
        ui->horizontalSlider_Progress->setValue(0);
        break;
      }
      default:
      {
        break;
      }
    }
  });
  connect(media_player,&QMediaPlayer::durationChanged,this,[this](qint64 duration)
  {
    ui->horizontalSlider_Progress->setMaximum(duration);
  });
  connect(media_player,&QMediaPlayer::bufferProgressChanged,this,[this](float progress)
  {
    qDebug() << "Buffer Progress:" << progress;
  });
  connect(media_player,&QMediaPlayer::positionChanged,this,[this](qint64 position)
  {
    ui->horizontalSlider_Progress->setValue(position);
  });
  connect(media_player,&QMediaPlayer::playingChanged,this,[this](bool playing)
  {
    qDebug() << "Playing:" << playing;
  });

  connect(ui->horizontalSlider_Progress,&QSlider::sliderPressed,this,[this]()
  {
    media_player->pause();
  });
  connect(ui->horizontalSlider_Progress,&QSlider::sliderMoved,this,[this](int value)
  {
    media_player->setPosition(value);
  });
  connect(ui->horizontalSlider_Progress,&QSlider::sliderReleased,this,[this]()
  {
    media_player->play();
  });

  ui->videoWidget->installEventFilter(this);
}

MediaPlayer::~MediaPlayer()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

bool MediaPlayer::eventFilter(QObject* obj,QEvent* event)
{
  bool result = false;

  if(obj == ui->videoWidget)
  {
    QMouseEvent* mouse_event = (QMouseEvent*)(event);
    switch(event->type())
    {
      case QEvent::MouseButtonRelease:
      {
        if(mouse_event->button() == Qt::LeftButton)
        {
          if(media_player->isPlaying())
          {
            media_player->pause();
          }
          else
          {
            media_player->play();
          }
        }
        break;
      }
      default:
      {
        break;
      }
    }
  }

  return result;
}

void MediaPlayer::on_action_Load_triggered()
{
  QString file_name = QFileDialog::getOpenFileName(this,"Open Media",".","Media Files (*.mp4 *.avi *.mp3 *.wav)");
  if(!file_name.isEmpty())
  {
    media_player->setSource(QUrl::fromLocalFile(file_name));
    media_player->play();
  }
}
