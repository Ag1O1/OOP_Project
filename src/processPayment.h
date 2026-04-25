#include "inventory.h"
#include <iostream>
#include <vector>
class ProcessPayment {
  Inventory cart;

public:
  unsigned calc(unsigned paymentAmount) {
    std::vector<Product> items = cart.getAllStock();
    unsigned amount = 0;
    unsigned change = 0;
    for (int i = 0; i < items.size(); i++) {
      amount += items[i].getPrice() * items[i].getQuantity();
    }
    if (paymentAmount >= amount) {
      change = paymentAmount - amount;
    } else
      std::cout << "Insufficient funds";
    return change;
  }
};
