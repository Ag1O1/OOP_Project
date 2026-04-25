#pragma once
#include "Product.h"
#include "inventory.h"
#include <vector>
class AddToCart {
public:
  static void execute(int id, int quantity, Inventory &inv,
                      std::vector<Product> &cart) {
    Product *product = inv.getProduct(id);

    if (product != nullptr && product->getQuantity() >= quantity) {
      cart.push_back(*product);

      inv.removeStock(id, quantity);
    }
  }
};
