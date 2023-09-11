#include "stdafx.h"
#include "BasicUIFramework.h"

#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QFile>

namespace BasicUIFramework
{
  bool initialize(int& argc,char* argv[])
  {
    bool result = false;

    if(!qApp)
    {
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
# ifdef _WIN32
      QTextCodec::setCodecForCStrings(QTextCodec::codecForName("system"));
      QTextCodec::setCodecForLocale(QTextCodec::codecForName("system"));
      QTextCodec::setCodecForTr(QTextCodec::codecForName("system"));
# else
      QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB18030"));
      QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
      QTextCodec::setCodecForTr(QTextCodec::codecForName("GB18030"));
# endif
#else
      //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
      QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
#endif
      if(new QApplication(argc,argv))
      {
        result = true;
      }
    }

    return result;
  }

  int exec()
  {
    int ret =0;

    if(qApp)
    {
      //样式
      QFile file(":/resource/stylesheet/default_style.qss");
      file.open(QIODevice::OpenModeFlag::ReadOnly | QIODevice::OpenModeFlag::Text);
      if (file.isOpen())
      {
        QString qss = QString::fromUtf8(file.readAll());
        qApp->setStyleSheet(qss);
        file.close();
      }

      //翻译
      QTranslator translator;
      if (translator.load(":/resource/translations/qt_zh_CN.qm"))
      {
        qApp->installTranslator(&translator);
      }

      ret = qApp->exec();

      delete qApp;
    }

    return ret;
  }
}

extern "C"
{
	BasicUIFramework_API void InitializeBasicUIFramework()
	{
	}
}
