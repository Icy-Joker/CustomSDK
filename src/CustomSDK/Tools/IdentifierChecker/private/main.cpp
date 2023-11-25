#include "stdafx.h"

#include <iostream>

int main(int argc, char* argv[])
{
  std::array<int,17> array_weight = {7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
  std::array<int,11> array_mapping = {1,0,10,9,8,7,6,5,4,3,2};

  if(argc >= 2)
  {
    std::string identifier_number = argv[1];

    if(identifier_number.length() == 18)
    {
      int total_value = 0;
      for(int i = 0; i < 17; i++)
      {
        int value = identifier_number[i] - '0';
        int weight = array_weight[i];
        long temp_value = value * weight;
        std::cout << value << " * " << weight << " = " << std::to_string(temp_value) << std::endl;
        total_value += temp_value;
      }

      int effective_check_code = array_mapping[total_value%11];
      int current_check_code = (identifier_number[17] == 'x' || identifier_number[17] == 'X') ? 10 : (identifier_number[17] - '0');

      std::cout << "total_value:" << total_value << "\teffective_check_code:" << effective_check_code << "\t current_check_code:" << current_check_code << std::endl;
      std::cout << "CheckStatus:"<< (effective_check_code == current_check_code ? "success!" : "failure!") << std::endl;
    }
  }

  return 0;
}
