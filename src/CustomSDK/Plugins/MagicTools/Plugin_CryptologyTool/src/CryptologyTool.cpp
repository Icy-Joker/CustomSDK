#include "stdafx.h"

#include "CryptologyTool/CryptologyTool.h"

#include <iostream>

#include "ui_CryptologyTool.h"

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/rand.h>

CryptologyTool::CryptologyTool(QWidget* parent /*= nullptr*/,Qt::WindowFlags flags /*= Qt::WindowFlags()*/) :
  QMainWindow(parent,flags),
  ui(new Ui::CryptologyTool())
{
  ui->setupUi(this);
}

CryptologyTool::~CryptologyTool()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

std::string doEncryption(const std::string plain_text,const std::string key,unsigned char* iv)
{
  std::string result = "";

  int len;
  int ciphertext_len;
  std::array<unsigned char,1024> cipher_text= {'0'};

  if(const EVP_CIPHER* cipher = EVP_get_cipherbyname("aes-256-cbc"))
  {
    if(EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new())
    {
      // 初始化加密操作
      if(EVP_EncryptInit_ex(ctx,cipher, NULL,reinterpret_cast<unsigned char*>((char*)key.c_str()),iv))
      {
        // 提供待加密数据
        if(EVP_EncryptUpdate(ctx,cipher_text.data(),&len,reinterpret_cast<unsigned char*>((char*)plain_text.c_str()),(int)plain_text.length()))
        {
          ciphertext_len = len;

          // 结束加密过程
          if(EVP_EncryptFinal_ex(ctx,&cipher_text[len],&len))
          {
            ciphertext_len += len;
            cipher_text[ciphertext_len] = '\0';

            result = std::string((char*)cipher_text.data(),ciphertext_len);
          }
        }
      }

      EVP_CIPHER_CTX_free(ctx);
    }
  }

  return result;
}

void CryptologyTool::on_pushButton_Encryption_clicked()
{
  qDebug() << "Encryption";

  QString plain_text = ui->lineEdit_PlainText->text();
  QString encryption_key = ui->lineEdit_EncryptionKey->text();

  unsigned char iv[16];// 128-bit IV for AES

  qDebug() << doEncryption(plain_text.toStdString(),encryption_key.toStdString(),iv).c_str();
}

void CryptologyTool::on_pushButton_Decryption_clicked()
{
  qDebug() << "Decryption";

  QString cipher_text = ui->lineEdit_Ciphertext->text();
  QString decryption_key = ui->lineEdit_DecryptionKey->text();

  EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
  if(EVP_DecryptInit_ex(ctx,EVP_enc_null(), NULL,reinterpret_cast<const unsigned char*>(cipher_text.toStdString().c_str()),reinterpret_cast<const unsigned char*>(decryption_key.toStdString().c_str())))
  {
    int len;
    unsigned char plain_text[1024] = {'0'};
    if(EVP_DecryptUpdate(ctx,reinterpret_cast<unsigned char*>(&plain_text),&len,reinterpret_cast<const unsigned char*>(cipher_text.toStdString().c_str()),cipher_text.length()))
    {
      if(EVP_DecryptFinal_ex(ctx,&plain_text[len],&len))
      {
        qDebug() << "Decryption Successful:" << QByteArray(reinterpret_cast<char*>(plain_text),len).toHex();;
      }
    }
  }
  EVP_CIPHER_CTX_free(ctx);
}
