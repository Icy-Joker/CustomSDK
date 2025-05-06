#include "stdafx.h"

#include "MagicBox.h"
#include <MagicTool.h>

#include <BasicUIFramework/FlowLayout.h>

#include <QToolButton>

Q_DECLARE_METATYPE(MagicTool*)

MagicBox::MagicBox(QWidget* parent)
{
  if(FlowLayout* flow_layout = new FlowLayout(this))
  {
    this->setLayout(flow_layout);
  }
}

MagicBox::~MagicBox()
{
}

void MagicBox::setName(const QString& name)
{
  this->name = name;
}

const QString& MagicBox::getName() const
{
  return this->name;
}

void MagicBox::registerMagicTool(MagicTool* magic_tool)
{
  if(magic_tool)
  {
    if(QLayout* layout = (this->layout()))
    {
      if(QToolButton* tool_button = new QToolButton(this))
      {
        tool_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tool_button->setIcon(magic_tool->getIcon().isNull() ? QIcon(":/icons/icon.png") : magic_tool->getIcon());
        tool_button->setText(QString::fromUtf8(magic_tool->getName()));
        tool_button->setToolTip(QString::fromUtf8(magic_tool->getDescription()));
        tool_button->setWhatsThis(QString::fromUtf8(magic_tool->getDescription()));

        if(QAction* action_create_magic_tool = new QAction(magic_tool->getIcon(),QString::fromUtf8(magic_tool->getName()),tool_button))
        {
          connect(action_create_magic_tool,SIGNAL(triggered()),this,SLOT(slot_action_CreateMagicTool_triggered()));

          action_create_magic_tool->setData(QVariant::fromValue(magic_tool));

          tool_button->setDefaultAction(action_create_magic_tool);
        }

        layout->addWidget(tool_button);
      }
    }
  }
}

void MagicBox::slot_action_CreateMagicTool_triggered()
{
  if(QAction* action_create_magic_tool = qobject_cast<QAction*>(sender()))
  {
    if(MagicTool* magic_tool = action_create_magic_tool->data().value<MagicTool*>())
    {
      if(QWidget* tool_widget = magic_tool->createInstance(this,Qt::Tool))
      {
        tool_widget->setWindowTitle((QString::fromUtf8(magic_tool->getName())));
        tool_widget->setWindowIconText(((QString::fromUtf8(magic_tool->getName()))));
        tool_widget->setWindowIcon((magic_tool->getIcon()));
        tool_widget->setAttribute(Qt::WA_DeleteOnClose);
        tool_widget->show();
      }
    }
  }
}
