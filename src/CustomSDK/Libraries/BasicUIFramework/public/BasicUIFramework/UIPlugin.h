#pragma once

#include <BasicSupport/AbstractPlugin.h>

#include <QWidget>

class BasicUIFramework_API UIPlugin : public AbstractPlugin
{
public:
  virtual ~UIPlugin(){};
public:
	virtual const QIcon getIcon() const = 0;
	virtual const char* getName() const = 0;
	virtual const char* getDescription() const = 0;
	virtual QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const = 0;
};
