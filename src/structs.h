#pragma once
#include <string>

struct UserLogin {
  std::string username;
  std::string password;
  std::string userType;
};

struct NewProductDetails {
  std::string name;
  double price;
  int quantity;
};
