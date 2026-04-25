#pragma once
#include "Product.h"
#include <string>
#include <vector>

struct UserLogin {
  std::string username;
  std::string password;
  std::string userType;
  std::vector<Product> cart;
};

struct NewProductDetails {
  std::string name;
  double price;
  int quantity;
};
