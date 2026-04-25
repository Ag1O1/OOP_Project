#include "Product.h"
#include <vector>
class Inventory {
private:
  std::vector<Product> stock;

public:
  std::vector<Product>::iterator begin();
  std::vector<Product>::iterator end();

  std::vector<Product>::const_iterator begin() const;
  std::vector<Product>::const_iterator end() const;

  void addProduct(Product prod);

  void removeProduct(int id);

  void addStock(unsigned id, unsigned amount);

  void removeStock(unsigned id, unsigned amount);

  Product *getProduct(unsigned id);

  const std::vector<Product> &getAllStock() const;

  bool checkLowStock(int id, int threshold);
};
