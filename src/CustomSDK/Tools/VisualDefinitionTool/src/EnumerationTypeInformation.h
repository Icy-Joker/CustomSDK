#pragma once

#ifndef __ENUMERATEDDATATYPEINFORMATION_H__
#define __ENUMERATEDDATATYPEINFORMATION_H__

#include <QWidget>
#include <QStandardItemModel>

struct EnumerationMember;
class EnumerationType;

namespace Ui
{
  class EnumerationTypeInformation;
}

class EnumerationTypeInformation : public QWidget
{
  Q_OBJECT
public:
  explicit EnumerationTypeInformation(QWidget* parent = nullptr);
  ~EnumerationTypeInformation() override;
public:
  void showEnumerationTypeInformation(const boost::shared_ptr<EnumerationType>&);
private:
  void showName() const;
  void showCompleteName() const;
  void showMemberElementInformation() const;
  void showEnumerationTypeInformation() const;
private:
  void appendEnumerationMember() const;
  void moveEnumerationMemberUp() const;
  void moveEnumerationMemberDown() const;
  void removeEnumerationMember() const;
private:
  void appendEnumerationMember(const boost::shared_ptr<EnumerationMember>&) const;
private slots:
  void on_lineEdit_EnumerationTypeName_textChanged(const QString&) const;
  void on_tableView_EnumerationMembers_customContextMenuRequested(const QPoint&) const;
  void on_pushButton_Reset_clicked() const;
  void on_pushButton_Apply_clicked() const;
private slots:
  void slot_customAction_triggered() const;
private:
  Ui::EnumerationTypeInformation* ui;
  boost::weak_ptr<EnumerationType> enumerated_data_type_weak_ptr;
};

#endif //!__ENUMERATEDDATATYPEINFORMATION_H__
