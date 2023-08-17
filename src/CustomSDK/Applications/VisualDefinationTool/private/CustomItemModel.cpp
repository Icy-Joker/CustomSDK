#include "CustomItemModel.h"

CustomItemModel::CustomItemModel(QObject* parent):
  QStandardItemModel(parent)
{
}

CustomItemModel::~CustomItemModel()
{
}

QVariant CustomItemModel::data(const QModelIndex& index,int role) const
{
  QVariant value;

  switch(role)
  {
    case Qt::ItemDataRole::DisplayRole:
    {
      value = QString::fromLocal8Bit("数据");
      break;
    }
    default:
    {
      value = QStandardItemModel::data(index,role);
      break;
    }
  }

  return value;
}

bool CustomItemModel::setData(const QModelIndex& index,const QVariant& value,int role)
{
  bool result = false;

  result = QStandardItemModel::setData(index,value,role);

  return result;
}

Qt::ItemFlags CustomItemModel::flags(const QModelIndex& index) const
{
  Qt::ItemFlags flags;

  flags = QStandardItemModel::flags(index);

  return flags;
}
