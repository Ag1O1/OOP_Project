#include "inventory.h"
class AddToCart {
  Inventory inv;
  Inventory cart;

public:
  void execute(unsigned id, unsigned quantity) {
    if (inv.getProduct(id)->getQuantity() >= quantity) {
      cart.addProduct(*inv.getProduct(id));
      cart.addStock(id, quantity);
    }
  }
};
