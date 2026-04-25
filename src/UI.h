#pragma once
#include "Product.h"
#include "structs.h"
#include <string>
#include <vector>

class UI {
public:
  int MainMenu();

  UserLogin LoginMenu();

  void PrintMessage(const std::string &msg);

  void DisplayInventory(const std::vector<Product> &inventory);

  void DisplayCart(const std::vector<Product> &cart);

  NewProductDetails GetProductInput();

  void PrintReceipt(const std::vector<Product> &receiptData);
};
