#include "user.h"
#include "structs.h"
using std::string;

User::User(std::string name, std::string pass) {
  UserLogin data;
  data.username = name;
  data.password = pass;
  role = "customer";
}
User::User(UserLogin user_data) {
  data = user_data;
  role = "customer";
}

bool User::checkPassword(std::string pass) { return (pass == data.password); }
string User::getRole() const { return role; }
string User::getUsername() const { return data.username; }
