#include "Product.h"
#include <vector>
class Inventory {
private:
  std::vector<Product> stock;

public:
  void addProduct(Product prod);

  void removeProduct(int id);

  void addStock(unsigned id, unsigned amount);

  void removeStock(unsigned id, unsigned amount);

  Product *getProduct(unsigned id);

  const std::vector<Product> &getAllStock() const;

  bool checkLowStock(int id, int threshold);
};
