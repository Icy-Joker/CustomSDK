#pragma once

#ifndef __ENUMERATEDDATATYPEINFORMATION_H__
#define __ENUMERATEDDATATYPEINFORMATION_H__

#include <QWidget>
#include <QStandardItemModel>

class EnumeratedDataType;

namespace Ui
{
  class EnumeratedDataTypeInformation;
}

class EnumeratedDataTypeInformation : public QWidget
{
  Q_OBJECT
public:
  explicit EnumeratedDataTypeInformation(QWidget* parent= nullptr);
  ~EnumeratedDataTypeInformation();
public:
  void showEnumeratedDataTypeInformation(const boost::shared_ptr<EnumeratedDataType>&);
private:
  void initializeUI();
  void initializeFunction();
private slots:
  void on_lineEdit_EnumeratedDataTypeName_textChanged(const QString&);
private:
  Ui::EnumeratedDataTypeInformation* ui;  
  boost::weak_ptr<EnumeratedDataType> enumerated_data_type_weak_ptr;
};

#endif //!__ENUMERATEDDATATYPEINFORMATION_H__
