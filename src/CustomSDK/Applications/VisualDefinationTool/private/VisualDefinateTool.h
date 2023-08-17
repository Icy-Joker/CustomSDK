#pragma once

#ifndef __DEFINATETOOL_H__
#define __DEFINATETOOL_H__

#include <QWidget>
#include <QStandardItem>

namespace Ui
{
  class VisualDefinateTool;
}

class EnumeratedDataType;
class StructuredDataType;
class Package;

class VisualDefinateTool : public QWidget
{
  Q_OBJECT
public:
  explicit VisualDefinateTool(QWidget* parent=nullptr);
  ~VisualDefinateTool();
public:
private:
  void initializeUI();
  void initializeFunction();
private:
  QStandardItem* appendEnumeratedDataType(QStandardItem*);
  QStandardItem* appendStructuredDataType(QStandardItem*);
  QStandardItem* appendPackage(QStandardItem*);

  void appendEnumeratedDataType();
  void appendStructuredDataType();
  void appendPackage();
private:
  void previewDefination();

  void showEmptyPage();
  void showEnumeratedDataTypeInformation(boost::shared_ptr<EnumeratedDataType>);
  void showStructuredDataTypeInformation(boost::shared_ptr<StructuredDataType>);
  void showPackageInformation(boost::shared_ptr<Package>);
private slots:
  void on_treeView_DefinationParseTree_customContextMenuRequested(const QPoint&);
private slots:
  void slot_parseTree_currentRowChanged(const QModelIndex&,const QModelIndex&);
  void slot_customAction_triggered();
private:
  Ui::VisualDefinateTool* ui;
};

#endif //!__DEFINATETOOL_H__
