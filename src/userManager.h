#pragma once
#include "admin.h"
#include "user.h"
#include <string>
#include <vector>

class UserManager {
private:
  std::vector<User *> users;
  User *currentUser;

  void loadFromFile();
  void saveToFile() const;

public:
  UserManager();
  ~UserManager();

  bool registerUser(const std::string &username, const std::string &password,
                    const std::string &role);
  User *login(const std::string &username, const std::string &password);
  User *getCurrentUser() const;
  void logout();
};
