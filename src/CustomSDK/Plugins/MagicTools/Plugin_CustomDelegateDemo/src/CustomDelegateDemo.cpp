#include "stdafx.h"

#include "CustomDelegateDemo/CustomDelegateDemo.h"
#include "ui_CustomDelegateDemo.h"

#include "ComboBoxDelegate.h"
#include "PasswordDelegate.h"
#include "ColorDelegate.h"
#include "DateTimeDelegate.h"
#include "SliderDelegate.h"
#include "DoubleSpinBoxDelegate.h"
#include "ButtonDelegate.h"
#include "ProgressBarDelegate.h"

#include <QStandardItemModel>

CustomDelegateDemo::CustomDelegateDemo(QWidget* parent /*= nullptr*/,Qt::WindowFlags flags /*= Qt::WindowFlags()*/):
  QMainWindow(parent,flags),
  ui(new Ui::CustomDelegateDemo())
{
  ui->setupUi(this);

  if(QStandardItemModel* model = new QStandardItemModel(this))
  {
    model->setHorizontalHeaderLabels(
      QStringList()
      << QString::fromUtf8("用户名")// 0
      << QString::fromUtf8("密码框")// 0
      << QString::fromUtf8("用户类别")// 0
      << QString::fromUtf8("上次登录日期")// 0
      << QString::fromUtf8("所属标识")// 0
      << QString::fromUtf8("数值(滑块)")// 0
      << QString::fromUtf8("数值(输入框)")// 0
      << QString::fromUtf8("成就完成进度")// 0
      << QString::fromUtf8("操作")
      << QString::fromUtf8("状态")
    );

    ui->tableView->setModel(model);
    ui->tableView->setItemDelegateForColumn(1,new PasswordDelegate(this));
    ui->tableView->setItemDelegateForColumn(2,new ComboBoxDelegate(this));
    ui->tableView->setItemDelegateForColumn(3,new DateTimeDelegate(this));
    ui->tableView->setItemDelegateForColumn(4,new ColorDelegate(this));
    ui->tableView->setItemDelegateForColumn(5,new SliderDelegate(this));
    ui->tableView->setItemDelegateForColumn(6,new DoubleSpinBoxDelegate(this));
    ui->tableView->setItemDelegateForColumn(7,new ProgressBarDelegate(this));
    ui->tableView->setItemDelegateForColumn(8,new ButtonDelegate(this));

    ui->tableView->setMouseTracking(true);

    //测试
    {
      for(std::size_t i = 0;i <= 100;++i)
      {
        QColor color(255,0,0,i * 255.0 / 100.0);

        model->appendRow(QList<QStandardItem*>()
          << new QStandardItem("张三")
          << new QStandardItem("password")
          << new QStandardItem("")
          << new QStandardItem("2018-01-01 12:00:00")
          << new QStandardItem(color.name(QColor::HexArgb).toUpper())
          << new QStandardItem(QString::number(i))
          << new QStandardItem(QString::number(i))
          << new QStandardItem(QString::number(i))
          << new QStandardItem("")
          << new QStandardItem("正常")
        );
      }
    }
  }
}

CustomDelegateDemo::~CustomDelegateDemo()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}
