#pragma once
#include "structs.h"
#include <string>
class User {
private:
  UserLogin data;

protected:
  std::string role;

public:
  User(std::string name, std::string pass);
  User(UserLogin userdata);
  bool checkPassword(std::string pass);
  std::string getRole() const;
  std::string getUsername() const;
};
