#include "stdafx.h"

#include <qrencode/qrencode.h>

#include <iostream>

int main(int argc,char* argv[])
{
  std::string message_context="Hello,World!";

  if(argc==2)
  {
    message_context = argv[1];

    if(QRcode *qrcode = QRcode_encodeString(message_context.c_str(), 0, QR_ECLEVEL_L, QR_MODE_8, 1))
    {
      // 打印 QR 码数据
      for(int y = 0; y < qrcode->width; y++)
      {
        for(int x = 0; x < qrcode->width; x++) 
        {
          if(qrcode->data[ y * qrcode->width + x] & 0x01) 
          {
            std::cout << "◽️";
          }
          else
          {
            std::cout << "◾️";
          }
        }
        std::cout << std::endl;
      }
      QRcode_free(qrcode);
    }
  }
  return 0;
}
