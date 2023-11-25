#include "stdafx.h"

#include "MagicBox.h"
#include "MagicTool.h"

#include <BasicUIFramework/Flowlayout.h>

#include <QVBoxLayout>
#include <QToolButton>
#include <QAction>

#include <algorithm>
#include <functional>

MagicBox::MagicBox(const QString& name,QWidget* parent,Qt::WindowFlags flags)
	:QWidget(parent,flags),
	magic_box_name(name)
{
	initializeUI();
}

MagicBox::~MagicBox()
{
}

const QString& MagicBox::getName()
{
	return std::cref(magic_box_name);
}

MagicTool* MagicBox::findToolByName(const QString & magic_tool_name)
{
	MagicTool* result = nullptr;
	auto it_found_vector_magic_tools = std::find_if(std::begin(vector_magic_tools), std::end(vector_magic_tools), [&magic_tool_name](MagicTool* magic_tool_existed)
	{
		return magic_tool_name==QString::fromLocal8Bit(magic_tool_existed->getName());
	});
	if (it_found_vector_magic_tools!= std::end(vector_magic_tools))
	{
		result =*it_found_vector_magic_tools;
	}
	return result;
}

const std::vector<MagicTool*>& MagicBox::getAllMagicTools()
{
	return std::cref(vector_magic_tools);
}

void MagicBox::appendTool(MagicTool * magic_tool)
{
	if (magic_tool)
	{
		vector_magic_tools.push_back(magic_tool);
		if (QLayout* layout = this->layout())
		{
			QToolButton* toolButton = new QToolButton(this);
			toolButton->setIcon(magic_tool->getIcon());
			toolButton->setToolTip(QString::fromLocal8Bit(magic_tool->getDescription()));
			toolButton->setText(QString::fromLocal8Bit(magic_tool->getName()));
			layout->addWidget(toolButton);

			connect(toolButton, SIGNAL(clicked()), this, SLOT(slot_plugin_clicked()));
		}
	}
}

void MagicBox::initializeUI()
{
	FlowLayout* layout = new FlowLayout(this);
	this->setLayout(layout);
}

void MagicBox::slot_plugin_clicked()
{
	QString magic_tool_name;

	if(QToolButton* toolButton=dynamic_cast<QToolButton*>(sender()))
	{
		magic_tool_name = toolButton->text();
	}
	else if(QAction* action= dynamic_cast<QAction*>(sender()))
	{
		magic_tool_name = action->text();
	}
	if (MagicTool* magic_tool = findToolByName(magic_tool_name))
	{
		emit signal_magicTool_requested(magic_tool);
	}
}
