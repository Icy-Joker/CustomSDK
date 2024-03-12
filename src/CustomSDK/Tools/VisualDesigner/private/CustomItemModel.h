#pragma once

#ifndef __CUSTOMITEMMODEL_H__
# define __CUSTOMITEMMODEL_H__

#include <QStandardItemModel>

class CustomItemModel : public QStandardItemModel
{
Q_OBJECT
public:
  explicit CustomItemModel(QObject* parent = nullptr);
  ~CustomItemModel();
public:
  QVariant headerData(int section,Qt::Orientation orientation,int role = Qt::DisplayRole) const override;
  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index,int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex& index,const QVariant& value,int role = Qt::EditRole) override;
protected:
  Qt::ItemFlags flags(const QModelIndex& index) const override;
};

#endif // !__CUSTOMITEMMODEL_H__
