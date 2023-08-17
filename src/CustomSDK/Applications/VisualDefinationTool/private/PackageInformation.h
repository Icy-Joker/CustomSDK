#pragma once

#ifndef __PACKAGEINFORMATION_H__
#define __PACKAGEINFORMATION_H__

#include <QWidget>

class Package;

namespace Ui
{
  class PackageInformation;
}

class PackageInformation : public QWidget
{
  Q_OBJECT
public:
  explicit PackageInformation(QWidget* parent= nullptr);
  ~PackageInformation();
public:
  void showPackageInformation(boost::shared_ptr<Package>);
private:
  void initializeUI();
  void initializeFunction();
private slots:
  void on_lineEdit_PackageName_textChanged(const QString&);
private:
  Ui::PackageInformation* ui;  
  boost::weak_ptr<Package> package_weak_ptr;
};

#endif //!__PACKAGEINFORMATION_H__
