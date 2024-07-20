#pragma once

#ifndef UNIVERSALFACTORY_H
# define UNIVERSALFACTORY_H


#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
#include <stdexcept>

#include <BasicSupport/Singleton.h>

template<typename PRODUCT_TYPE,typename ... CREATOR_PARAMETERS>
class UniversalFactory : public Singleton<UniversalFactory<PRODUCT_TYPE,CREATOR_PARAMETERS ...>>
{
public:
  void registerType(const std::string& product_type_name,std::function<std::shared_ptr<PRODUCT_TYPE>(CREATOR_PARAMETERS ...)>&& product_creator)
  {
    this->product_creators[product_type_name] = product_creator;
  }

  std::shared_ptr<PRODUCT_TYPE> createProduct(const std::string& product_type_name,CREATOR_PARAMETERS ... parameters)
  {
    std::shared_ptr<PRODUCT_TYPE> result = nullptr;
    {
      auto it_found = this->product_creators.find(product_type_name);
      if(it_found != this->product_creators.end())
      {
        result = it_found->second(parameters ...);
      }
      else
      {
        throw std::runtime_error("The requested type '" + product_type_name + "' has not been registered.");
      }
    }
    return result;
  }
private:
  std::unordered_map<std::string,std::function<std::shared_ptr<PRODUCT_TYPE>(CREATOR_PARAMETERS ...)>> product_creators;
private:
  friend class Singleton<UniversalFactory<PRODUCT_TYPE,CREATOR_PARAMETERS ...>>;
};

#endif//!UNIVERSALFACTORY_H
