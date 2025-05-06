#include "stdafx.h"

#include "MagicToolBox.h"
#include "ui_MagicToolBox.h"

#include "MagicTool.h"
#include "MagicBox.h"

#include <BasicFramework/DynamicLibrary.h>

#include <pugixml.hpp>

#include <boost/filesystem.hpp>

#include <QLabel>
#include <QStandardItem>
#include <QFileInfo>
#include <QDir>
#include <QMenu>
#include <QToolButton>
#include <QMessageBox>
#include <QCloseEvent>

typedef MagicTool* (* Function_getPlugin)();

MagicToolBox::MagicToolBox(QWidget* parent,Qt::WindowFlags flags):
  QMainWindow(parent,flags),
  ui(new Ui::MagicToolBox())
{
  ui->setupUi(this);

  ui->listView_MagicBox->setModel(new QStandardItemModel(this));

  connect(ui->listView_MagicBox->selectionModel(),SIGNAL(currentRowChanged(const QModelIndex&, const QModelIndex&)),this,SLOT(slot_listView_currentRowChanged(const QModelIndex&, const QModelIndex&)));

  doLoadPlugin();
  doCreateSystemTray();
}

MagicToolBox::~MagicToolBox()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

MagicBox* MagicToolBox::findBoxByName(const QString& name)
{
  MagicBox* result = nullptr;

  int count = ui->stackedWidget->count();

  for(int i = 0;i < count;++i)
  {
    if(MagicBox* magic_box = qobject_cast<MagicBox*>(ui->stackedWidget->widget(i)))
    {
      if(magic_box->getName() == name)
      {
        result = magic_box;
        break;
      }
    }
  }

  return result;
}

MagicBox* MagicToolBox::createBoxByName(const QString& name)
{
  MagicBox* result = nullptr;

  auto* model = qobject_cast<QStandardItemModel*>(ui->listView_MagicBox->model());
  if(model)
  {
    auto items = model->findItems(name,Qt::MatchExactly,0);
    if(items.empty())
    {
      model->appendRow(new QStandardItem(name));

      auto* magic_box = new MagicBox(this);
      {
        magic_box->setName(name);

        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->addWidget(magic_box));

        result = magic_box;
      }
    }
  }

  return result;
}

MagicTool* MagicToolBox::doLoadPlugin(const QString& plugin_path)
{
  MagicTool* result = nullptr;

#ifdef _POSIX_VERSION
  if(HMODULE handle_module = dlopen(plugin_path.toStdString().c_str(),RTLD_LAZY))
  {
    Function_getPlugin getPlugin = (Function_getPlugin)(FARPROC)dlsym(handle_module,"getPlugin");
#else
  if(HMODULE handle_module = LoadLibraryA(plugin_path.toStdString().c_str()))
  {
    Function_getPlugin getPlugin = (Function_getPlugin)(FARPROC)GetProcAddress(handle_module,"getPlugin");
#endif
    if(getPlugin)
    {
      if(MagicTool* magic_tool = getPlugin())
      {
        result = magic_tool;
      }
    }
  }
  else
  {
#ifdef _POSIX_VERSION
    qDebug() << dlerror();
#else
    qDebug() << GetLastError();
#endif
  }

  return result;
}

QMenu* MagicToolBox::doCreateSystemTrayMenu()
{
  QMenu* result = nullptr;

  if(QMenu* menu = new QMenu(this))
  {
    int count = ui->stackedWidget->count();
    for(std::size_t index_widget_group = 0;index_widget_group < count;++index_widget_group)
    {
      if(MagicBox* magic_box = qobject_cast<MagicBox*>(ui->stackedWidget->widget(index_widget_group)))
      {
        const QString& magic_box_name = magic_box->getName();
        //QIcon magic_box_icon = ui->toolBox->itemIcon(index_widget_group);

        if(QMenu* menu_group = new QMenu(menu))
        {
          QList<QAction*> magic_tool_actions;

          if(QLayout* layout_magic_box = magic_box->layout())
          {
            for(std::size_t index_tool_button = 0;index_tool_button < layout_magic_box->count();++index_tool_button)
            {
              if(auto* tool_button = qobject_cast<QToolButton*>(layout_magic_box->itemAt(index_tool_button)->widget()))
              {
                if(QAction* action_create_magic_tool = tool_button->defaultAction())
                {
                  magic_tool_actions << action_create_magic_tool;
                }
              }
            }
          }
          menu_group->addActions(magic_tool_actions);

          menu_group->setTitle(magic_box_name);
          // menu_group->setIcon(magic_box_icon);

          menu->addMenu(menu_group);
        }
      }
    }

    menu->addSeparator();

    if(QAction* action_Quit = new QAction(QString::fromUtf8("退出"),menu))
    {
      action_Quit->setObjectName("action_Quit");
      connect(action_Quit, SIGNAL(triggered()),qApp, SLOT(quit()));
      menu->addAction(action_Quit);
    }

    result = menu;
  }

  return result;
}

QSystemTrayIcon* MagicToolBox::doCreateSystemTray(QIcon icon)
{
  QSystemTrayIcon* system_tray_icon = nullptr;

  if(QSystemTrayIcon::isSystemTrayAvailable())
  {
    if((system_tray_icon = new QSystemTrayIcon(icon,this)))
    {
      connect(system_tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(slot_trayIcon_activated(QSystemTrayIcon::ActivationReason)));
    }
    else
    {
      qDebug() << "create system tray failed";
    }

    this->setWindowFlags(Qt::WindowType::Tool);
  }
  else
  {
    qDebug() << "No system tray available";
  }

  return system_tray_icon;
}

void MagicToolBox::registerMagicTool(MagicTool* magic_tool)
{
  MagicBox* magic_box = findBoxByName(magic_tool->getType());
  if(!magic_box)
  {
    magic_box = createBoxByName(magic_tool->getType());
  }
  if(magic_box)
  {
    magic_box->registerMagicTool(magic_tool);
  }
}

void MagicToolBox::doLoadPlugin()
{
  pugi::xml_document xml_document;
  if(xml_document.load_file("../etc/MagicToolBox.xml",pugi::parse_default | pugi::parse_declaration | pugi::parse_comments | pugi::encoding_utf8))
  {
    if(pugi::xml_node xml_node_magic_tool_box = xml_document.select_node("Root/MagicToolBox").node())
    {
      if(!xml_node_magic_tool_box.attribute("enable_auto_load").as_bool())
      {
        /*
         * 按配置加载插件
         */
        pugi::xpath_node_set xpath_node_set_magic_box = xml_node_magic_tool_box.select_nodes("MagicBox");
        std::for_each(xpath_node_set_magic_box.begin(),xpath_node_set_magic_box.end(),[this](pugi::xpath_node xpath_node_magic_box)
        {
          if(pugi::xml_node xml_node_magic_box = xpath_node_magic_box.node())
          {
            const std::string magic_box_name = xml_node_magic_box.attribute("name").as_string();

            pugi::xpath_node_set xpath_node_set_magic_tool = xml_node_magic_box.select_nodes("MagicTool");
            std::for_each(xpath_node_set_magic_tool.begin(),xpath_node_set_magic_tool.end(),[this,magic_box_name](pugi::xpath_node xpath_node_magic_tool)
            {
              if(pugi::xml_node xml_node_magic_tool = xpath_node_magic_tool.node())
              {
                const std::string magic_tool_identifier = xml_node_magic_tool.attribute("identifier").as_string();
                const std::string magic_tool_name = xml_node_magic_tool.attribute("name").as_string();
                const std::string magic_tool_location = xml_node_magic_tool.attribute("location").as_string();

                const std::string magic_tool_file_path = std::string(MODULE_LIBRARY_PREFIX) + magic_tool_identifier + std::string(MODULE_LIBRARY_SUFFIX MODULE_LIBRARY_EXTENSION);

                if(MagicTool* magic_tool = doLoadPlugin(QString::fromStdString(boost::filesystem::absolute(boost::filesystem::path(magic_tool_location).append(magic_tool_file_path)).string())))
                {
                  magic_tool->setName(QString::fromStdString(magic_tool_name).toUtf8().toStdString());
                  magic_tool->setType(QString::fromStdString(magic_box_name).toUtf8().toStdString());
                  registerMagicTool(magic_tool);
                }
              };
            });
          }
        });
      }
      else
      {
        /*
         * 自动加载插件
         */
        QDir plugins_directory(QString("%1/../plugins/MagicTools").arg(QDir::currentPath()));
        QFileInfoList file_info_list = plugins_directory.entryInfoList(QDir::Filter::Files);
        for(auto it_file_info_list = file_info_list.begin();it_file_info_list != file_info_list.end();++it_file_info_list)
        {
          QFileInfo file_info = *it_file_info_list;
          QString file_path = file_info.absoluteFilePath();

          if(MagicTool* magic_tool = doLoadPlugin(file_path))
          {
            registerMagicTool(magic_tool);
          }
        }
      }
    }
  }
}

void MagicToolBox::doCreateSystemTray()
{
  if(QSystemTrayIcon* system_tray_icon = doCreateSystemTray(QIcon(":/icons/icon.png")))
  {
    if(QMenu* menu = doCreateSystemTrayMenu())
    {
      system_tray_icon->setContextMenu(menu);
    }
    system_tray_icon->setVisible(true);

    system_tray_icon->showMessage(QString::fromUtf8(""),QString::fromUtf8("百宝箱已启动"),QSystemTrayIcon::MessageIcon::NoIcon,5000);
  }
}

void MagicToolBox::closeEvent(QCloseEvent* event)
{
  QMessageBox::StandardButton button = QMessageBox::question(this,"","是否确定退出");
  if(button != QMessageBox::StandardButton::Yes)
  {
    event->ignore();
  }
  else
  {
    event->accept();
  }
}

void MagicToolBox::slot_listView_currentRowChanged(const QModelIndex& index_current,const QModelIndex& index_previous)
{
  if(index_current.isValid())
  {
    QString magic_box_name = index_current.data(Qt::DisplayRole).toString();
    if(MagicBox* magic_box = MagicToolBox::findBoxByName(magic_box_name))
    {
      ui->stackedWidget->setCurrentWidget(magic_box);
    }
  }
}

void MagicToolBox::slot_trayIcon_activated(QSystemTrayIcon::ActivationReason reason)
{
  if(QSystemTrayIcon* system_tray_icon = qobject_cast<QSystemTrayIcon*>(sender()))
  {
    switch(reason)
    {
      case QSystemTrayIcon::Unknown:
      {
        qDebug() << "Unknown";
        break;
      }
      case QSystemTrayIcon::Context:
      {
        qDebug() << "Context";
        break;
      }
      case QSystemTrayIcon::DoubleClick:
      {
        this->setVisible(this->isHidden());
        break;
      }
      case QSystemTrayIcon::Trigger:
      {
        qDebug() << "Trigger";
        break;
      }
      case QSystemTrayIcon::MiddleClick:
      {
        qDebug() << "MiddleClick";
        break;
      }
      default:
      {
        qDebug() << "Default";
        break;
      }
    }
  }
}
