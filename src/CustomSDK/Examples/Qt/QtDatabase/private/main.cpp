#include "stdafx.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCoreApplication>

#include <iostream>

int main(int argc,char* argv[])
{
  int result = 0;

  QCoreApplication app(argc,argv);

  QSqlDatabase sqlite_database = QSqlDatabase::addDatabase("QSQLITE");
  sqlite_database.setDatabaseName("test.db");
  if(sqlite_database.open())
  {
    {
      QSqlQuery sqlite_query(sqlite_database);
      sqlite_query.exec("drop table if exists AAA");
    }
    {
      QSqlQuery sqlite_query(sqlite_database);
      sqlite_query.exec("create table if not exists AAA(id INTEGER PRIMARY KEY,name TEXT,age INTEGER)");
    }
    {
      int id = 0;
      QString name = "Icy-Joker";
      int age = 18;
      QSqlQuery sqlite_query(sqlite_database);
      sqlite_query.prepare("insert into AAA(id,name,age) values(:id,:name,:age)");
      sqlite_query.bindValue(":id",id);
      sqlite_query.bindValue(":name",name);
      sqlite_query.bindValue(":age",age);
      if(sqlite_query.exec())
      {
        std::cout << "inserted " << sqlite_query.numRowsAffected() << "rows" << std::endl;
      }
    }
    {
      int id = 0;
      QString name = "Whisper";
      int age = 27;
      QSqlQuery sqlite_query(sqlite_database);
      sqlite_query.prepare("update AAA set name = :name,age = :age where id = :id");
      sqlite_query.bindValue(":id",id);
      sqlite_query.bindValue(":name",name);
      sqlite_query.bindValue(":age",age);
      if(sqlite_query.exec())
      {
        std::cout << "updated " << sqlite_query.numRowsAffected() << " rows" << std::endl;
      }
    }
    {
      QSqlQuery sqlite_query(sqlite_database);
      if(sqlite_query.exec("select * from AAA"))
      {
        while(sqlite_query.next())
        {
          int id = sqlite_query.value("id").toInt();
          QString name = sqlite_query.value("name").toString();
          int age = sqlite_query.value("age").toInt();

          std::cout << qPrintable(QString("id:%1,name:%2,age:%3").arg(id).arg(name).arg(age)) << std::endl;
        }
      }
    }
    {
      QSqlQuery sqlite_query(sqlite_database);
      if(sqlite_query.exec("delete from AAA"))
      {
        std::cout << "delete " << sqlite_query.numRowsAffected() << " rows" << std::endl;
      }
    }
    sqlite_database.close();
  }

  app.exec();

  return result;
}