#include "stdafx.h"
#include "PackageInformation.h"
#include "ui_PackageInformation.h"

#include "Package.h"
#include "EnumeratedDataType.h"
#include "StructuredDataType.h"

Q_DECLARE_METATYPE(boost::weak_ptr<Package>)
Q_DECLARE_METATYPE(boost::weak_ptr<EnumeratedDataType>)
Q_DECLARE_METATYPE(boost::weak_ptr<StructuredDataType>)

PackageInformation::PackageInformation(QWidget* parent):
  QWidget(parent),
  ui(new Ui::PackageInformation())
{
  initializeUI();
  initializeFunction();
}

PackageInformation::~PackageInformation()
{
  if(ui)
  {
    delete ui;
    ui=nullptr;
  }
}

void PackageInformation::showPackageInformation(boost::shared_ptr<Package> package_shared_ptr)
{
  if(package_shared_ptr)
  {
    this->package_weak_ptr=package_shared_ptr;
    //获取数据
    const QString& current_package_name = QString::fromStdString(package_shared_ptr->getPackageName());
    //const std::vector<boost::weak_ptr<EnumeratedDataType>> vector_enumerated_data_type=package_shared_ptr->collectEnumeratedDataType();
    const std::vector<boost::weak_ptr<EnumeratedDataType>> vector_enumerated_data_type=package_shared_ptr->getAvailableEnumeratedDataType();
    //const std::vector<boost::weak_ptr<StructuredDataType>> vector_structured_data_type=package_shared_ptr->collectStructuredDataType();
    const std::vector<boost::weak_ptr<StructuredDataType>> vector_structured_data_type=package_shared_ptr->getAvailableStructuredDataType();
    {//显示
      ui->lineEdit_PackageName->setText(current_package_name);

      if(vector_enumerated_data_type.size())
      {
        ui->comboBox_DataTypeDefination->addItem(QString::fromStdString("枚举"));

        std::for_each(vector_enumerated_data_type.begin(),vector_enumerated_data_type.end(),[&](const boost::weak_ptr<EnumeratedDataType> enumerated_data_type_weak_ptr)
        {
          if(boost::shared_ptr<EnumeratedDataType> enumerated_data_type_shared_ptr = enumerated_data_type_weak_ptr.lock())
          {
            ui->comboBox_DataTypeDefination->addItem(QString::fromStdString(enumerated_data_type_shared_ptr->getEnumeratedDataTypeCompleteName()),QVariant::fromValue<boost::weak_ptr<EnumeratedDataType>>(enumerated_data_type_shared_ptr));
          }
        });
      }

      if(vector_structured_data_type.size())
      {
        ui->comboBox_DataTypeDefination->addItem(QString::fromStdString("结构体"));

        std::for_each(vector_structured_data_type.begin(),vector_structured_data_type.end(),[&](const boost::weak_ptr<StructuredDataType> structured_data_type_weak_ptr)
        {
          if(boost::shared_ptr<StructuredDataType> structured_data_type_shared_ptr = structured_data_type_weak_ptr.lock())
          {
            ui->comboBox_DataTypeDefination->addItem(QString::fromStdString(structured_data_type_shared_ptr->getStructuredDataTypeCompleteName()),QVariant::fromValue<boost::weak_ptr<StructuredDataType>>(structured_data_type_shared_ptr));
          }
        });
      }
    }
  }
}

void PackageInformation::initializeUI()
{
  ui->setupUi(this);
}

void PackageInformation::initializeFunction()
{

}

void PackageInformation::on_lineEdit_PackageName_textChanged(const QString& current_package_name)
{
  if(boost::shared_ptr<Package> package_shared_ptr = this->package_weak_ptr.lock())
  {
    const QString& parent_package_complete_name = QString::fromStdString(package_shared_ptr->getParentPackageCompleteName());
    const QString& current_package_name= ui->lineEdit_PackageName->text();

    const QString& current_package_complete_name=parent_package_complete_name.isEmpty()?current_package_name:QString("%1::%2").arg(parent_package_complete_name).arg(current_package_name); 


    ui->lineEdit_PackageCompleteName->setText(current_package_complete_name);
  }
}
