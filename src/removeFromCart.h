#pragma once
#include "inventory.h"
#include <iostream>
class RemoveFromCart {
  Inventory inv;
  Inventory cart;

public:
  void execute(unsigned id, unsigned quantity) {
    if (cart.getProduct(id)->getQuantity() >= quantity) {
      cart.removeStock(id, quantity);
    } else
      std::cout << "Err: quantity more than quantity";
  }
};
