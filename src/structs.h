#pragma once
#include "Product.h"
#include <string>
#include <vector>

struct UserLogin {
  std::string username;
  std::string password;
};

struct NewProductDetails {
  std::string name;
  double price;
  int quantity;
};
