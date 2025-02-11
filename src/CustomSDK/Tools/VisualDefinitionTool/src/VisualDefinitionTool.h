#pragma once

#ifndef __DEFINITIONTOOL_H__
#define __DEFINITIONTOOL_H__

#include <QWidget>
#include <QStandardItem>

namespace Ui
{
  class VisualDefinitionTool;
}

class IDLFileDefinition;
class EnumeratedDataType;
class StructuredDataType;
class Package;

class VisualDefinitionTool : public QWidget
{
  Q_OBJECT
public:
  explicit VisualDefinitionTool(QWidget* parent = nullptr);
  ~VisualDefinitionTool() override;
private:
  QStandardItem* appendFileDefinition(QStandardItem*);
  QStandardItem* appendEnumeratedDataType(QStandardItem*);
  QStandardItem* appendStructuredDataType(QStandardItem*);
  QStandardItem* appendPackage(QStandardItem*);

  void appendFileDefinition();
  void appendEnumeratedDataType();
  void appendStructuredDataType();
  void appendPackage();
private:
  void previewDefinition();

  void showEmptyPage();
  void showIDLFileDefinitionInformation(boost::shared_ptr<IDLFileDefinition>);
  void showEnumeratedDataTypeInformation(boost::shared_ptr<EnumeratedDataType>);
  void showStructuredDataTypeInformation(boost::shared_ptr<StructuredDataType>);
  void showPackageInformation(boost::shared_ptr<Package>);
private slots:
  void on_treeView_DefinitionParseTree_customContextMenuRequested(const QPoint&);
private slots:
  void slot_parseTree_currentRowChanged(const QModelIndex&,const QModelIndex&);
  void slot_customAction_triggered();
private:
  Ui::VisualDefinitionTool* ui;
};

#endif //!__DEFINITIONTOOL_H__
