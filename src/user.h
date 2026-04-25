#pragma once
#include <string>
class User {
private:
  std::string username;
  std::string password;
  bool loggedIn;

protected:
  std::string role;

public:
  User(std::string name, std::string pass);
  void login(std::string name, std::string pass);
  void logout();
  std::string getRole() const;
  std::string getUsername() const;
};
