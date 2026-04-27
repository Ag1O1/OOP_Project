#pragma once
#include "Product.h"
#include "inventory.h"
#include "structs.h"
#include "user.h"
#include <string>
#include <vector>

class UI {
public:
  int MainMenu();

  User LoginMenu();

  void PrintMessage(const std::string &msg);

  void DisplayInventory(const Inventory &inventory);

  void DisplayCart(const std::vector<Product> &cart);

  NewProductDetails GetProductInput();

  void PrintReceipt(const std::vector<Product> &receiptData);
};
