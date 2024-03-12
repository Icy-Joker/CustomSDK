#include "stdafx.h"

#include <qrencode/qrencode.h>

#include <boost/program_options.hpp>

#include <iostream>

int main(int argc,char* argv[])
{
  int result = 0;

  boost::program_options::options_description description_global("Allowed options");
  description_global.add_options()
                        ("help,h","打印此帮助信息")
                        ("message,m",boost::program_options::value<std::string>()->default_value("Hello World"),"要编码的字符串")
                        ("output,o","输出文件名");
  boost::program_options::variables_map map_variables;
  try
  {
    boost::program_options::store(boost::program_options::command_line_parser(argc,argv).options(description_global).run(),map_variables);
    boost::program_options::notify(map_variables);

    if(!map_variables.count("help"))
    {
      const std::string message = map_variables["message"].as<std::string>();

      QRcode* qr_code = QRcode_encodeString("Hello World",0,QRecLevel::QR_ECLEVEL_H,QR_MODE_8,1);
      int qr_code_width = qr_code->width;

      for(std::size_t i = 0;i < qr_code_width;++i)
      {
        for(std::size_t j = 0;j < qr_code_width;++j)
        {
          std::cout << (qr_code->data[j * qr_code_width + i] & 0x01) ? "◾" : "◽";
        }
        std::cout << std::endl;
      }
    }
    else
    {
      description_global.print(std::cout);
    }
  }
  catch(boost::program_options::error& error)
  {
    std::cout << error.what() << std::endl;
  }
  catch(...)
  {
    description_global.print(std::cout);
  }

  return  result;
}