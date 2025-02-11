#pragma once

#ifndef __STRUCTUREDDATATYPEINFORMATION_H__
#define __STRUCTUREDDATATYPEINFORMATION_H__

#include <QWidget>
#include <QStandardItemModel>

class StructuredDataType;

namespace Ui
{
  class StructuredDataTypeInformation;
}

class StructuredDataTypeInformation : public QWidget
{
  Q_OBJECT
public:
  explicit StructuredDataTypeInformation(QWidget* parent= nullptr);
  ~StructuredDataTypeInformation();
public:
  void showStructuredDataTypeInformation(const boost::shared_ptr<StructuredDataType>&);
private slots:
  void on_lineEdit_StructuredDataTypeName_textChanged(const QString&);
private:
  Ui::StructuredDataTypeInformation* ui;  
  boost::weak_ptr<StructuredDataType> structured_data_type_weak_ptr; 
};

#endif //!__STRUCTUREDDATATYPEINFORMATION_H__
