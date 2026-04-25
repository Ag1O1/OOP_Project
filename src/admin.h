#include "Product.h"
#include <vector>

class Admin {
private:
  std::vector<Product> inventory;

public:
  void loadFromFile();

  void saveToFile();

  void addProduct();

  void deleteProduct();

  void showProducts();

  std::vector<Product> getProducts();
};
