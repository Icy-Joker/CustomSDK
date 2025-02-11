#pragma once

#ifndef IDLFILEDEFINITIONINFORMATION_H
# define IDLFILEDEFINITIONINFORMATION_H

#include <QWidget>

class IDLFileDefinition;

namespace Ui
{
  class IDLFileDefinitionInformation;
}

class IDLFileDefinitionInformation : public QWidget
{
  Q_OBJECT
public:
  explicit IDLFileDefinitionInformation(QWidget* parent = nullptr);
  ~IDLFileDefinitionInformation() override;
public:
  void showIDLFileDefinitionInformation(const boost::shared_ptr<IDLFileDefinition>&);
private:
  Ui::IDLFileDefinitionInformation* ui{};
  boost::weak_ptr<IDLFileDefinition> enumerated_data_type_weak_ptr;
};

#endif // !IDLFILEDEFINITIONINFORMATION_H
