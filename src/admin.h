#pragma once
#include "Product.h"
#include "user.h"
#include <string.h>
#include <vector>

class Admin : public User {
private:
public:
  Admin(std::string name, std::string pass);
  Admin(UserLogin user_data);
};
