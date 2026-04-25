#pragma once
#include "Product.h"
#include <vector>
class Cashier {
private:
  std::vector<Product> cart;

public:
  void startTransaction();

  void addToCart(std::vector<Product> products);

  void finalizePayment();
};
