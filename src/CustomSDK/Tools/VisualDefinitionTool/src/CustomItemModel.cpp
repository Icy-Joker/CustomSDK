#include "CustomItemModel.h"

#include "AbstractNamespace.h"

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
      if(auto current_namespace_shared_ptr = QStandardItemModel::data(index,ITEM_USER_DATA_ROLE).value<boost::shared_ptr<AbstractDefinition>>())
      {
        value = QString::fromUtf8(current_namespace_shared_ptr->getName());
      }
      else
      {
        value = QString::fromUtf8("未知名称");
      }
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
