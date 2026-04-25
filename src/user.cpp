#include "user.h"
#include <iostream>
using std::string;

User::User(std::string name, std::string pass) {
  username = name;
  password = pass;
  loggedIn = false;
}
void User::login(std::string name, std::string pass) {
  bool condition = (name == username && pass == password);
  loggedIn = condition;
  std::cout << (condition ? "Successfully logged in as " + username
                          : "Failed to log in ");
}
void User::logout() { loggedIn = false; }
string User::getRole() const { return role; }
string User::getUsername() const { return username; }
