#include "stdafx.h"

#include "DatabaseVisualizationTool/DatabaseVisualizationTool.h"
#include "ui_DatabaseVisualizationTool.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QFile>

DatabaseVisualizationTool::DatabaseVisualizationTool(QWidget* parent /*= nullptr*/,Qt::WindowFlags flags /*= Qt::WindowFlags()*/):
  QMainWindow(parent,flags),
  ui(new Ui::DatabaseVisualizationTool())
{
  ui->setupUi(this);

  QFile database_file(":/data/information.sql");
  if(database_file.exists())
  {
    if(database_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QTextStream in_stream(&database_file);

      if(!QSqlDatabase::database(QSqlDatabase::defaultConnection).isOpen())
      {
        QSqlDatabase sqlite_database = QSqlDatabase::addDatabase("QSQLITE");
        if(sqlite_database.isValid())
        {
          if(!sqlite_database.isOpen() && sqlite_database.open())
          {
            QString sql_statement;
            while(in_stream.readLineInto(&sql_statement))
            {
              QSqlQuery sqlite_query;
              if(!sqlite_query.exec(sql_statement))
              {
                qDebug("%s",qPrintable(QString("error while executing \"%1\"").arg(sql_statement)));
              }
            }
          }
        }
      }

      database_file.close();
    }
  }

  if(QSqlTableModel* model = new QSqlTableModel(this))
  {
    model->setTable("ID_LOCATION");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);// 设置编辑策略
    model->select();

    ui->tableView->setModel(model);
  }
}

DatabaseVisualizationTool::~DatabaseVisualizationTool()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}
