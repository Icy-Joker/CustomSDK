#include "MagicToolBox.h"
#include "ui_MagicToolBox.h"

#include "MagicBox.h"
#include "MagicTool.h"

#include <BasicSupport/PluginManager.h>
#include <BasicSupport/CommonTypes.h>
#include <BasicUIFramework/CustomControls/CustomWindowTitleBar.h>

#include <QMenu>
#include <QFileInfo>
#include <QDir>
#include <QLayout>

#include <algorithm>
#include <regex>

#ifdef WIN32
# define REGEX_PLUGIN_PATH "\\S+-vc" _CRT_VER_NAME "-" _PLATFORM _DEBUG_FLAG "\.dll"
#else
# define REGEX_PLUGIN_PATH "lib\\S+" "\.so" 		//"lib\\S+" _CRT_VER_NAME "-" _PLATFORM _DEBUG_FLAG "\.so"
#endif

MagicToolBox::MagicToolBox(QWidget* parent,Qt::WindowFlags flags) :
	QToolBox(parent,flags),
	ui(new Ui::MagicToolBox())
{
  ui->setupUi(this);

  if(QLayout* default_layout = this->layout())
  {
    default_layout->setMenuBar(new CustomWindowTitleBar(this));
  }

	if (QSystemTrayIcon::isSystemTrayAvailable())
	{
    trayIcon = new QSystemTrayIcon(QIcon(":/resource/images/heart.png"), this);
		if (trayIcon)
		{
      connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(slot_trayIcon_activated(QSystemTrayIcon::ActivationReason)));
      //托盘图标描述
			trayIcon->setToolTip(QString::fromLocal8Bit("工具箱"));
			//托盘图标菜单
			trayIcon->setContextMenu(new QMenu(this));
			//显示托盘图标
			trayIcon->show();
		}
	}
	else
	{//不支持系统托盘
		
	}

  QDir plugins_directory(QString("%1/../plugins/MagicTools").arg(QDir::currentPath()));
	QFileInfoList file_info_list= plugins_directory.entryInfoList(QDir::Filter::Files);
	for (auto it_file_info_list= file_info_list.begin();it_file_info_list!= file_info_list.end();++it_file_info_list)
	{
		QFileInfo file_info = *it_file_info_list;
		QString file_path = file_info.absoluteFilePath();
		loadPlugin(file_path);
	}

}

MagicToolBox::~MagicToolBox()
{
	if (trayIcon)
	{
		trayIcon->hide();
	}

  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void MagicToolBox::toggleStatus()
{
	if (QWidget* widget_top_level = this->topLevelWidget())
	{
		widget_top_level->isVisible() ? widget_top_level->hide() : widget_top_level->show();
	}
}

void MagicToolBox::loadPlugin(const QString & plugin_path)
{
	if (plugin_path.size())
	{
		QFileInfo file_info(plugin_path);
		QString file_name = file_info.fileName();

		std::regex regex_plugin_path(REGEX_PLUGIN_PATH);
		if (std::regex_match(file_name.toStdString(), regex_plugin_path))
		{
			if (MagicTool* magic_tool = MagicToolManager->loadPlugin(plugin_path.toStdString().c_str()))
			{
				const QString magic_box_name = QString::fromUtf8(magic_tool->getType());
				const QString magic_tool_name = QString::fromLocal8Bit(magic_tool->getName());


				if (findToolByName(magic_box_name, magic_tool_name) == nullptr)
				{
					MagicBox* magic_box = findBoxByName(magic_box_name);
					if (magic_box == nullptr)
					{
						magic_box = new MagicBox(magic_box_name,this);
						connect(magic_box, SIGNAL(signal_magicTool_requested(MagicTool*)), this, SLOT(slot_magicTool_requested(MagicTool*)));
						addItem(magic_box, magic_box_name);
						vector_magic_boxes.push_back(magic_box);
					}
					magic_box->appendTool(magic_tool);
				}
			}
		}
	}
}

MagicBox * MagicToolBox::findBoxByName(const QString & magic_box_name)
{
	MagicBox * result = nullptr;
	auto it_found_vector_boxes = std::find_if(std::begin(vector_magic_boxes), std::end(vector_magic_boxes), [&magic_box_name](MagicBox* magic_box_existed)
	{
		return magic_box_name== magic_box_existed->getName();
	});
	if (it_found_vector_boxes != vector_magic_boxes.end())
	{
		if (MagicBox* magic_box = *it_found_vector_boxes)
		{
			result= magic_box;
		}
	}
	return result;
}

MagicTool* MagicToolBox::findToolByName(const QString & magic_box_name, const QString & magic_tool_name)
{
	MagicTool* result = nullptr;
	if (MagicBox* magic_box = findBoxByName(magic_box_name))
	{
		result= magic_box->findToolByName(magic_tool_name);
	}
	return result;
}

void MagicToolBox::slot_action_triggered()
{
	if (QAction* action=(QAction*)sender())
	{
		if (action->objectName() == "action_toggleStatus")
		{
			toggleStatus();
		}
		else if (action->objectName() == "action_Quit")
		{
			qApp->exit(0);
		}
	}
}

void MagicToolBox::slot_magicTool_requested(MagicTool* magic_tool)
{
	if (magic_tool)
	{
    if (QWidget * widget = magic_tool->createInstance(nullptr,Qt::WindowFlags(Qt::WindowType::Tool | Qt::WindowType::MSWindowsFixedSizeDialogHint)))
    {
      widget->setAttribute(Qt::WA_DeleteOnClose,true);

      widget->show();
    }
	}
}

void MagicToolBox::slot_trayIcon_activated(QSystemTrayIcon::ActivationReason reason)
{
	if (trayIcon)
	{
		switch (reason)
		{
			case QSystemTrayIcon::Unknown:
				break;
			case QSystemTrayIcon::Context:
			{
				if (QMenu* menu = trayIcon->contextMenu())
				{
					menu->clear();

					if (QAction* action_toggleStatus = new QAction(menu))
					{
						action_toggleStatus->setObjectName("action_toggleStatus");
						action_toggleStatus->setText(this->isVisible() ? QString::fromLocal8Bit("隐藏主界面") : QString::fromLocal8Bit("显示主界面"));
						connect(action_toggleStatus, SIGNAL(triggered()), this, SLOT(slot_action_triggered()));
						menu->addAction(action_toggleStatus);
					}

					menu->addSeparator();

					for (auto it_vector_magic_boxes= vector_magic_boxes.begin();it_vector_magic_boxes!= vector_magic_boxes.end();++it_vector_magic_boxes)
					{
						if (MagicBox* magic_box = *it_vector_magic_boxes)
						{
							if (QMenu* menu_box = new QMenu(menu))
							{
								QList<QAction*> list_action_magic_tools;

								const QString& magic_box_name = magic_box->getName();
								const std::vector<MagicTool*>& vector_magic_tools = magic_box->getAllMagicTools();
								for (auto it_vector_magic_tools = vector_magic_tools.begin(); it_vector_magic_tools != vector_magic_tools.end(); ++it_vector_magic_tools)
								{
									if (MagicTool* magic_tool = *it_vector_magic_tools)
									{
										QAction* action_magic_tool = new QAction(menu_box);
										action_magic_tool->setText(QString::fromLocal8Bit(magic_tool->getName()));
										action_magic_tool->setIcon(magic_tool->getIcon());
										action_magic_tool->setToolTip(QString::fromLocal8Bit(magic_tool->getDescription()));
										connect(action_magic_tool, SIGNAL(triggered()), magic_box, SLOT(slot_plugin_clicked()));

										list_action_magic_tools << action_magic_tool;
									}
								}

								menu_box->setTitle(magic_box_name);
								menu_box->addActions(list_action_magic_tools);

								menu->addMenu(menu_box);
							}
						}
					}

					menu->addSeparator();

					QAction* action_Quit = new QAction(QString::fromLocal8Bit("退出"), menu);
					action_Quit->setObjectName("action_Quit");
					connect(action_Quit, SIGNAL(triggered()), this, SLOT(slot_action_triggered()));
					menu->addAction(action_Quit);

					menu->exec();
				}
				break;
			}
			case QSystemTrayIcon::DoubleClick:
			{
				toggleStatus();
				break;
			}
			case QSystemTrayIcon::Trigger:
				break;
			case QSystemTrayIcon::MiddleClick:
				break;
			default:
				break;
		}
	}
}
