#include "stdafx.h"

#include "BinaryViewer/BinaryViewer.h"
#include "ui_BinaryViewer.h"

#include "CustomTableModel.h"
#include "FileHandler.h"

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <QStandardItem>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

BinaryViewer::BinaryViewer(QWidget* parent,Qt::WindowFlags flags) :
  QMainWindow(parent,flags),
  ui(new Ui::BinaryViewer())
{
  ui->setupUi(this);

  ui->menuBar->setNativeMenuBar(false);

  if(CustomTableModel* model = new CustomTableModel(this))
  {
    ui->tableView->setModel(model);
  }
  ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

BinaryViewer::~BinaryViewer()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void BinaryViewer::on_action_Open_triggered()
{
  qDebug() << "BinaryViewer::on_action_Open_triggered()";

  const QString& file_path = QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("All Files (*)"));
  if(!file_path.isEmpty())
  {
    // 创建文件映射对象
    boost::interprocess::file_mapping file_mapping(file_path.toStdString().c_str(),boost::interprocess::read_only);
    // 创建映射区域（整个文件）
    boost::interprocess::mapped_region mapped_region(file_mapping,boost::interprocess::read_only);
    // 获取文件的起始地址和大小
    const char* fileData = static_cast<const char*>(mapped_region.get_address());
    std::size_t fileSize = mapped_region.get_size();
    if(CustomTableModel* model = static_cast<CustomTableModel*>(ui->tableView->model()))
    {
      QList<QStandardItem*> items;
      for(std::size_t pos = 0;pos < fileSize;pos++)
      {
        items.append(new QStandardItem(QString("%1 ").arg(static_cast<unsigned char>(fileData[pos]),2,16,QChar('0')).toUpper()));
        if((items.size() == 16) || (pos == fileSize - 1))
        {
          model->appendRow(items);
          items.clear();
        }
      }
    }

    // QFile file(file_path);
    // if(file.open(QIODevice::ReadOnly))
    // {
    //   QTextStream text_stream(&file);
    //
    //   QByteArray byte_array = text_stream.readAll().toUtf8();
    //   if(CustomTableModel* model = static_cast<CustomTableModel*>(ui->tableView->model()))
    //   {
    //     QList<QStandardItem*> items;
    //     model->blockSignals(true);
    //     for(std::size_t char_index = 0;char_index < byte_array.size();++char_index)
    //     {
    //       items.append(new QStandardItem(QString("%1 ").arg(static_cast<unsigned char>(byte_array[char_index]),2,16,QChar('0')).toUpper()));
    //       if((items.size() == 16) || (char_index == byte_array.size() - 1))
    //       {
    //         model->appendRow(items);
    //         items.clear();
    //       }
    //     }
    //     model->blockSignals(false);
    //
    //     emit model->layoutChanged();
    //   }

    // QString ascii_string = "";
    // for(std::size_t char_index = 0;char_index < byte_array.size();++char_index)
    // {
    //   if(byte_array[char_index] >= 32 && byte_array[char_index] <= 126)
    //   {
    //     ascii_string.append(byte_array[char_index]);
    //   }
    //   else
    //   {
    //     ascii_string.append('.');
    //   }
    //   if((char_index >= 15) && ((char_index) % 15 == 0))
    //   {
    //     qDebug() << ascii_string.toStdString().c_str();
    //
    //     ascii_string.clear();
    //   }
    // }
  }
}
