#pragma once

#ifndef __STRUCTUREDDATATYPEINFORMATION_H__
#define __STRUCTUREDDATATYPEINFORMATION_H__

#include <QWidget>
#include <QStandardItemModel>

class StructureType;

namespace Ui
{
  class StructureTypeInformation;
}

class StructureTypeInformation : public QWidget
{
  Q_OBJECT
public:
  explicit StructureTypeInformation(QWidget* parent = nullptr);
  ~StructureTypeInformation();
public:
  void showStructureTypeInformation(const boost::shared_ptr<StructureType>& structure_type_shared_ptr = nullptr);
private:
  void showName() const;
  void showCompleteName() const;
  void showParentStructureType() const;
  void showMemberElementInformation() const;
private slots:
  void on_lineEdit_StructureTypeName_textChanged(const QString&) const;
private:
  Ui::StructureTypeInformation* ui;
  boost::weak_ptr<StructureType> structured_data_type_weak_ptr;
};

#endif //!__STRUCTUREDDATATYPEINFORMATION_H__
