#include "stdafx.h"

#include "CustomTableModel.h"

CustomTableModel::CustomTableModel(QObject* parent):
  QStandardItemModel(parent)
{
}

CustomTableModel::~CustomTableModel()
{
}

QVariant CustomTableModel::headerData(int section,Qt::Orientation orientation,int role) const
{
  QVariant result;

  if(orientation == Qt::Orientation::Vertical && role == Qt::DisplayRole)
  {
    result = QString("%1").arg(16 * section,8,16,QChar('0')).toUpper();
  }
  else if(orientation == Qt::Orientation::Horizontal && role == Qt::DisplayRole)
  {
    result = QString("+%1").arg(static_cast<unsigned char>(section),0,16,QChar('0')).toUpper();
  }
  else
  {
    result = QStandardItemModel::headerData(section, orientation, role);
  }

  return result;
}

int CustomTableModel::rowCount(const QModelIndex& parent) const
{
  return QStandardItemModel::rowCount(parent);
}

int CustomTableModel::columnCount(const QModelIndex& parent) const
{
  return QStandardItemModel::columnCount(parent);
}

QVariant CustomTableModel::data(const QModelIndex& index,int role) const
{
  return QStandardItemModel::data(index,role);
}
