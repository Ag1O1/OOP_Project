#include "inventory.h"
#include "Product.h"
#include <vector>
using namespace std;
void Inventory::addProduct(Product prod) { stock.push_back(prod); }

std::vector<Product>::iterator Inventory::begin() { return stock.begin(); }
std::vector<Product>::iterator Inventory::end() { return stock.end(); }

std::vector<Product>::const_iterator Inventory::begin() const {
  return stock.begin();
}
std::vector<Product>::const_iterator Inventory::end() const {
  return stock.end();
}

void Inventory::removeProduct(int id) {
  for (int i = 0; i < stock.size(); i++) {
    if (stock[i].getId() == id) {
      stock.erase(stock.begin() + i);
      break;
    }
  }
}

void Inventory::addStock(unsigned id, unsigned amount) {
  for (int i = 0; i < stock.size(); i++) {
    if (stock[i].getId() == id) {
      stock[i].setQuantity(stock[i].getQuantity() + amount);
      break;
    }
  }
}

void Inventory::removeStock(unsigned id, unsigned amount) {
  for (int i = 0; i < stock.size(); i++) {
    if (stock[i].getId() == id) {
      if (stock[i].getQuantity() < amount) {
        // break loop if the amount is more than what's in stock.
        // the behaviour could be changed later to empty out the stock of the
        // item instead if needed.
        break;
      }
      stock[i].setQuantity(stock[i].getQuantity() - amount);
      break;
    }
  }
}

// This function returns a pointer
// nullptr means the product wasn't found
// nullptr can later on be used to display an error if the product isn't
// found
Product *Inventory::getProduct(unsigned id) {
  for (int i = 0; i < stock.size(); i++) {

    if (stock[i].getId() == id) {
      return &stock[i];
    }
  }
  return nullptr;
}

const vector<Product> &Inventory::getAllStock() const { return stock; }

// True means low stock
// The function checks the stock of a product in the stock by id
bool Inventory::checkLowStock(int id, int threshold) {
  Product *p = getProduct(id);
  if (p == nullptr) {
    return true;
  }
  if (p->getQuantity() <= threshold) {
    return true;
  }
  return false;
}
