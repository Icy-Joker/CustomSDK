#pragma once

#ifndef __CUSTOMITEMMODEL_H__
# define __CUSTOMITEMMODEL_H__

#include <QStandardItemModel>

class AbstractDefinition;

class CustomItemModel : public QStandardItemModel
{
  Q_OBJECT
public:
  explicit CustomItemModel(QObject*);
  ~CustomItemModel() override;
public:
  [[nodiscard]] QVariant data(const QModelIndex&,int role) const override;
  bool setData(const QModelIndex&,const QVariant&,int role) override;
  [[nodiscard]] Qt::ItemFlags flags(const QModelIndex&) const override;
};

#define ITEM_USER_DATA_ROLE Qt::ItemDataRole::UserRole
#define ITEM_TREE_NODE_TYPE_ROLE ITEM_USER_DATA_ROLE + 1

enum TREE_NODE_TYPE
{
  UNKNOWN,
  FILEDEFINITION,
  PACKAGE,
  ENUMERATEDDATATYPE,
  STRUCTUREDDATATYPE,
};

Q_DECLARE_METATYPE(boost::shared_ptr<AbstractDefinition>)

Q_DECLARE_METATYPE(TREE_NODE_TYPE)

#endif //!__CUSTOMITEMMODEL_H__
