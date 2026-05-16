#include "user.h"
#include "structs.h"
#include <iostream>
using std::string;

User::User(std::string name, std::string pass) {
  data.username = name;
  data.password = pass;
  role = "customer";
  std::cout << "User initialized: " << name << " | " << role << std::endl;
}
User::User(UserLogin user_data) {
  data = user_data;
  role = "customer";
}

bool User::checkPassword(std::string pass) {
  std::cout << "checking password..." << (pass == data.password) << std::endl;
  return (pass == data.password);
}
string User::getRole() const { return role; }
string User::getUsername() const { return data.username; }
string User::getPassword() const { return data.password; }
