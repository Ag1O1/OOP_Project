#pragma once
#include "Product.h"
#include "inventory.h"
#include <iostream>
#include <vector>
class AddToCart {
public:
  static void execute(int id, int quantity, Inventory &inv,
                      std::vector<Product> &cart) {
    Product *product = inv.getProduct(id);

    if (product != nullptr && product->getQuantity() >= quantity) {
      Product toAdd = *product;
      toAdd.setQuantity(quantity);
      cart.push_back(toAdd);

      inv.removeStock(id, quantity);
    }
  }
};
