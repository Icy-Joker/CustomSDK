#include "stdafx.h"

#include "CustomItemModel.h"
#include "DataTypeDefinitions.h"

CustomItemModel::CustomItemModel(QObject* parent /*= nullptr*/):
    QStandardItemModel(parent)
{
}

CustomItemModel::~CustomItemModel()
{
}

QVariant CustomItemModel::headerData(int section,Qt::Orientation orientation,int role /*= Qt::DisplayRole*/) const
{
  return QStandardItemModel::headerData(section,orientation,role);
}

int CustomItemModel::rowCount(const QModelIndex& parent /*= QModelIndex()*/) const
{
  return QStandardItemModel::rowCount(parent);
}

int CustomItemModel::columnCount(const QModelIndex& parent /*= QModelIndex()*/) const
{
  return QStandardItemModel::columnCount(parent);
}

QVariant CustomItemModel::data(const QModelIndex& index,int role /*= Qt::DisplayRole*/) const
{
  QVariant variant_result = QStandardItemModel::data(index,role);

  switch(role)
  {
    case Qt::DisplayRole:
    {
      QVariant variant_user_role = QStandardItemModel::data(index,Qt::UserRole);
      if(variant_result.isValid())
      {
        if(boost::shared_ptr<NamespaceDefinition> namespace_definition_ptr = boost::dynamic_pointer_cast<NamespaceDefinition>(variant_user_role.value<boost::weak_ptr<NamespaceDefinition>>().lock()))
        {
          variant_result = QVariant::fromValue<QString>(QString::fromStdString(namespace_definition_ptr->getName()));
        }
      }
      break;
    }
    default:
    {
      break;
    }
  }
  return variant_result;
}

bool CustomItemModel::setData(const QModelIndex& index,const QVariant& value,int role /*= Qt::EditRole*/)
{
  return QStandardItemModel::setData(index,value,role);
}

Qt::ItemFlags CustomItemModel::flags(const QModelIndex& index) const
{
  return QStandardItemModel::flags(index);
}
