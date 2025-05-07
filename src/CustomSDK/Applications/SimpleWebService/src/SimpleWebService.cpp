#include "stdafx.h"

#include "SimpleWebService.h"

#include <httplib.h>

SimpleWebService::SimpleWebService()
{
}

SimpleWebService::~SimpleWebService()
{
}

void defaultHandler(const httplib::Request& req,httplib::Response& res)
{
  std::string result = "";
  try
  {
    result += "METHOD:" + req.method + "\n";
    result += "PATH:" + req.path + "\n";
    result += "\n";
    if(!req.headers.empty())
    {
      std::for_each(req.headers.begin(),req.headers.end(),[&result](const httplib::Headers::value_type& item)
      {
        result += item.first + ":" + item.second + "\n";
      });
      result += "\n";
    }
    if(!req.params.empty())
    {
      std::for_each(req.params.begin(),req.params.end(),[&result](const httplib::Params::value_type& item)
      {
        result += item.first + ":" + item.second + "\n";
      });
    }

    res.set_content(result,"text/plain");
  }
  catch(const std::exception& e)
  {
    res.status = 500;// 返回 HTTP 500 错误
    result += "Internal Server Error";
    res.set_content(result,"text/plain");
  }
};

bool SimpleWebService::start()
{
  bool result = false;

  if(httplib::Server* http_server = new httplib::Server())
  {
    //http_server->Get(".*",defaultHandler);
    //http_server->Post(".*",defaultHandler);
    //http_server->Put(".*",defaultHandler);
    //http_server->Patch(".*",defaultHandler);
    //http_server->Delete(".*",defaultHandler);
    //http_server->Options(".*",defaultHandler);

    result = http_server->listen("0.0.0.0",80);
  }

  return result;
}

bool SimpleWebService::stop()
{
  bool result = false;

  return result;
}

void SimpleWebService::doRegister()
{
}

void SimpleWebService::doDeregisterService()
{
}
