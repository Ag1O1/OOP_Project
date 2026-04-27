#include "admin.h"
#include "loadFromFile.h"
#include "saveToFile.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

Admin::Admin(std::string name, std::string pass) : User(name, pass) {
  role = "admin";
}
Admin::Admin(UserLogin user_data) : User(user_data) { role = "admin"; }
