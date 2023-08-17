#pragma once

#include <BasicUIFramework/UIPlugin.h>
#include <BasicSupport/PluginManager.h>

#include <QIcon>

class MagicTool : public UIPlugin
{
public:
  virtual ~MagicTool(){};
public:
	virtual const QIcon getIcon() const = 0;
	virtual const char* getName() const = 0;
	virtual const char* getDescription() const = 0;
	virtual QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const = 0;
	virtual const char* getType() const = 0;
};

#define MagicToolManager PluginManager<MagicTool>::instance()
