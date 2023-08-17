#pragma once

#ifndef __CUSTOMITEMMODEL_H__
# define __CUSTOMITEMMODEL_H__

#include <QStandardItemModel>

class CustomItemModel : public QStandardItemModel
{
  Q_OBJECT
public:
  explicit CustomItemModel(QObject*);
  ~CustomItemModel();
public:
  QVariant data(const QModelIndex&,int role=Qt::ItemDataRole::DisplayRole) const override;
  bool setData(const QModelIndex&,const QVariant&,int role=Qt::ItemDataRole::EditRole) override;
  Qt::ItemFlags flags(const QModelIndex&) const override;
};

#endif //!__CUSTOMITEMMODEL_H__
