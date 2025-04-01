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
class EnumerationType;
class StructureType;
class Package;

class VisualDefinitionTool : public QWidget
{
  Q_OBJECT
public:
  explicit VisualDefinitionTool(QWidget* parent = nullptr);
  ~VisualDefinitionTool() override;
private:
  QStandardItem* appendFileDefinition(QStandardItem*,const boost::shared_ptr<IDLFileDefinition>& current_file_definition_shared_ptr = nullptr);
  QStandardItem* appendEnumerationType(QStandardItem*,const boost::shared_ptr<EnumerationType>& current_enumerated_data_type_shared_ptr = nullptr);
  QStandardItem* appendStructureType(QStandardItem*,const boost::shared_ptr<StructureType>& current_structured_data_type_shared_ptr = nullptr);
  QStandardItem* appendPackage(QStandardItem*,const boost::shared_ptr<Package>& current_package_shared_ptr = nullptr);

  void appendFileDefinition();
  void appendEnumerationType();
  void appendStructureType();
  void appendPackage();
private:
  void previewDefinition();
  void saveDefinition();
  void saveDefinitionAs();

  void showEmptyPage();
  void showIDLFileDefinitionInformation(const boost::shared_ptr<IDLFileDefinition>&);
  void showEnumerationTypeInformation(const boost::shared_ptr<EnumerationType>&);
  void showStructureTypeInformation(const boost::shared_ptr<StructureType>&);
  void showPackageInformation(const boost::shared_ptr<Package>&);
private slots:
  void on_treeView_DefinitionParseTree_customContextMenuRequested(const QPoint&);
  void on_treeView_DefinitionParseTree_clicked(const QModelIndex&);
private slots:
  void slot_parseTree_currentRowChanged(const QModelIndex&,const QModelIndex&);
  void slot_customAction_triggered();
private:
  Ui::VisualDefinitionTool* ui;
};

#endif //!__DEFINITIONTOOL_H__
