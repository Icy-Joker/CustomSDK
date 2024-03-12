#include "stdafx.h"

#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>

#include <string>
#include <iostream>
#include <fstream>

int main(int argc,char* argv[])
{
  int result = 0;

  try
  {
    soci::session sqlite_session(soci::sqlite3,"information.db");
    //soci::session sqlite_session(soci::sqlite3,":memory:");
    if(sqlite_session.is_connected())
    {
      //移除表
      {
        std::string sql_drop_table = "drop table if exists ID_LOCATION";
        sqlite_session << sql_drop_table;
      }
      //创建表
      {
        std::string sql_create_table = "create table if not exists ID_LOCATION(administrative_code TEXT PRIMARY KEY,province TEXT,city TEXT,county TEXT,area_code TEXT)";
        sqlite_session << sql_create_table;
      }
      //新增数据
      {
        std::string sql_do_insert = "insert into ID_LOCATION(administrative_code,province,city,county,area_code) values(:administrative_code,:province,:city,:county,:area_code)";
        std::ifstream in_stream;
        in_stream.open("ID_Location.txt",std::ios::binary);
        if(in_stream.is_open())
        {
          std::string single_line;
          while(std::getline(in_stream,single_line))
          {
            std::vector<std::string> tokens;
            std::istringstream iss(single_line);
            std::string token;
            while(std::getline(iss,token,' '))
            {
              tokens.push_back(token);
            }

            if(tokens.size() == 5)
            {
              std::string administrative_code = tokens[0];
              std::string province = tokens[1];
              std::string city = tokens[2];
              std::string county = tokens[3];
              std::string area_code = tokens[4];

              sqlite_session << sql_do_insert,soci::use(administrative_code),soci::use(province),soci::use(city),soci::use(county),soci::use(area_code);
            }
            else
            {
              std::cerr << "error" << std::endl;
            }
          }
          in_stream.close();
        }
      }
      //修改数据
      /*{
        int id = 0;
        std::string name = "Whisper";
        int age = 27;
        std::string sql_do_update = "update ID_LOCATION set name = :name,age = :age where id = :id";
        sqlite_session << sql_do_update,soci::use(name),soci::use(age),soci::use(id);
      }*/
      //查询数据
      {
        std::string sql_do_query = "select * from ID_LOCATION";
        soci::rowset<soci::row> row_set = (sqlite_session.prepare << sql_do_query);
        std::for_each(row_set.begin(),row_set.end(),[&](const soci::row& single_row)
        {
          std::string administrative_code = single_row.get<std::string>("administrative_code");
          std::string province = single_row.get<std::string>("province");
          std::string city = single_row.get<std::string>("city");
          std::string county = single_row.get<std::string>("county");
          std::string area_code = single_row.get<std::string>("area_code");

          std::cout << "administrative_code:" << administrative_code << " province:" << province << " city:" << city << " county:" << county << " area_code:" << area_code << std::endl;
        });
      }
      //删除数据
      /*{
        std::string sql_do_delete = "delete from ID_LOCATION where id = :id";
        sqlite_session << sql_do_delete;
      }*/
      //关闭数据库
      sqlite_session.close();
    }
  }
  catch(const soci::soci_error& error)
  {
    std::cout << error.what() << std::endl;
  }

  return result;
}
